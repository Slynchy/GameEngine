
#include "Graphics.h"

static const GLfloat g_quad_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f,  1.0f, 0.0f,
};

int GameEngine::Graphics::Init(
	const char* title,
	int screenPosX,
	int screenPosY,
	int resolutionX,
	int resolutionY,
	GameEngine::ResourceManager* resMan
) {
	m_resolutionX = resolutionX;
	m_resolutionY = resolutionY;

	m_window = SDL_CreateWindow(
		title,
		screenPosX,
		screenPosY,
		resolutionX,
		resolutionY,
		SDL_WINDOW_OPENGL
	);

	if (m_window == nullptr) {
		return GameEngine::Graphics::ErrorCodes::SDL_WINDOW_FAILED_TO_INIT;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Set to 3.2
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	m_context = SDL_GL_CreateContext(m_window);

	glewExperimental = GL_TRUE;
	auto returnNum = glewInit();
	if (returnNum != GLEW_OK) {
		std::cout << glewGetErrorString(returnNum) << "\n";
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);

	//////////////////////////////////////
	///// BEGIN FRAMEBUFFER/PPFX CODE ////
	//////////////////////////////////////

	resMan->LoadShaders("FRAMEBUFFER", "fxaa.vert.glsl", "ColorScreenSpace.glsl"); 
	this->RegisterPostProcessingShader(new PostProcessShader(resMan->GetShader("FRAMEBUFFER")));

	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	m_framebuffer = 0;
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	glGenTextures(1, &m_renderedTexture);

	glBindTexture(GL_TEXTURE_2D, m_renderedTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolutionX, resolutionY, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// fix the filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenRenderbuffers(1, &m_depthRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, resolutionX, resolutionY);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderedTexture, 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Framebuffer failed to init properly");

	glGenBuffers(1, &m_quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	auto programID = m_postProcessingFX.at(0)->getProgramID();

	m_texID = glGetUniformLocation(programID, "u_colorTexture");

	glBindVertexArray(0);

	//////////////////////////////////////
	///// END FRAMEBUFFER/PPFX CODE //////
	//////////////////////////////////////

	return 0;
}

void GameEngine::Graphics::PreRender() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glViewport(0, 0, m_resolutionX, m_resolutionY); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

/// @deprecated Not really sure why it's commented-out tbh...
void GameEngine::Graphics::SetMatrix(Entity* _ent, const glm::mat4 &model)
{
	// glm::mat4 mvp = camera->projectionMatrix * camera->viewMatrix * model;
	// _ent->GetComponent<Mesh>()->SetMatrix(mvp);
}

/// anonymous draw function to declutter PostRender. 
/// Not sure if anonymous functions are even a thing in C++...
/// #JavascriptThings
void _DRAW(GLuint m_VertexArrayID, GLuint m_quad_vertexbuffer, GLuint m_renderedTexture, GLuint program) {
	glBindTexture(GL_TEXTURE_2D, m_renderedTexture);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(program);

	glBindVertexArray(m_VertexArrayID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_quad_vertexbuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0 
	);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// cleanup
	glUseProgram(0);
	glEnable(GL_DEPTH_TEST);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameEngine::Graphics::PostRender() {

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glViewport(0, 0, m_resolutionX, m_resolutionY); 

	std::vector<PostProcessShader*> shadersToRun;

	for (size_t i = 0; i < (m_postProcessingFX.size()); i++) {
		auto curr = m_postProcessingFX.at(i);
		if (!curr->isEnabled()) continue;
		else {
			shadersToRun.push_back(curr);
		}
	}

	if (shadersToRun.size() > 1) {
		for (size_t i = 0; i < (shadersToRun.size() - 1); i++) {
			auto curr = shadersToRun.at(i);
			_DRAW(m_VertexArrayID, m_quad_vertexbuffer, m_renderedTexture, curr->getProgramID());
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (shadersToRun.size() > 1) {
		_DRAW(m_VertexArrayID, m_quad_vertexbuffer, m_renderedTexture, shadersToRun.at(shadersToRun.size() - 1)->getProgramID());
	} else {
		_DRAW(m_VertexArrayID, m_quad_vertexbuffer, m_renderedTexture, m_postProcessingFX.at(0)->getProgramID());
	}

	SwapBuffer();
}