

#include <engine/Mesh.h>
#include <engine/Entity.h>
#include <engine/Transform.h>

/*std::vector<GLfloat> GameEngine::Mesh::ReadFile(const char* file)
{
	// Open file
	std::ifstream t(file);

	std::vector<GLfloat> result;
	std::cout << "Reading : " << file << std::endl;

	while (t.good())
	{
		std::string str;
		t >> str;

		GLfloat f = std::atof(str.c_str());

		result.push_back(f);
	}

	return result;
}

void GameEngine::Mesh::ResetMatrix()
{
	model = glm::mat4(1.0f);
}

void GameEngine::Mesh::Translate(const glm::vec3 &axis)
{
	model *= glm::translate(axis);
}

// Cleanup all the things we bound and allocated
void GameEngine::Mesh::CleanUp()
{
	glDisableVertexAttribArray(0);

	glDeleteBuffers(2, vbo);

	glDeleteVertexArrays(1, vao);
}

// This is where we setup the model like we saw in the first part
bool GameEngine::Mesh::SetupBufferObjects()
{
	positions = ReadFile("positions.txt");
	colors = ReadFile("colors.txt");

	// Generate and assign two Vertex Buffer Objects to our handle
	glGenBuffers(2, vbo);

	// Generate and assign a Vertex Array Object to our handle
	glGenVertexArrays(1, vao);

	// Bind our Vertex Array Object as the current used object
	glBindVertexArray(vao[0]);

	// Colors
	// =======================
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	// Copy the vertex data from diamond to our buffer
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);

	// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
	glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// Positions
	// ===================
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// Copy the vertex data from diamond to our buffer
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), &positions[0], GL_STATIC_DRAW);

	// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable our attributes within the current VAO
	glEnableVertexAttribArray(positionAttributeIndex);
	glEnableVertexAttribArray(colorAttributeIndex);

	// Set up shader 
	// ===================
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(vao[0]);

	return true;
}

void GameEngine::Mesh::SetShader(Shader* _shader)
{
	shader = _shader;
}

void GameEngine::Mesh::Update() {
	Render();
}

glm::mat4 GameEngine::Mesh::GetModel()
{
	return model;
}

void GameEngine::Mesh::SetMatrix(glm::mat4 mvp)
{
	shader->UseProgram();
	shader->SetMatrix(mvp);
}

void GameEngine::Mesh::Render() {
	shader->UseProgram();
	glDrawArrays(GL_TRIANGLES, 0, positions.size() / 3);

	return;
}

void GameEngine::Mesh::Init() {
	this->m_transform = this->GetParent()->GetComponent<Transform>();
} */