
#include "Graphics.h"

int GameEngine::Graphics::Init(
	const char* title,
	int screenPosX,
	int screenPosY,
	int resolutionX,
	int resolutionY
) {
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
	glDepthFunc(GL_LEQUAL);

	return 0;
}

void GameEngine::Graphics::PreRender() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	ClearToGray();
}

/// @deprecated Not really sure why it's commented-out tbh...
void GameEngine::Graphics::SetMatrix(Entity* _ent, const glm::mat4 &model)
{
	// glm::mat4 mvp = camera->projectionMatrix * camera->viewMatrix * model;
	// _ent->GetComponent<Mesh>()->SetMatrix(mvp);
}

void GameEngine::Graphics::PostRender() {
	SwapBuffer();
}