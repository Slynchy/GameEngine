#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

namespace GameEngine
{

	class VertexBufferObject
	{

	private:
		GLuint id;
		int components;
		std::vector<GLfloat> data;
		bool dirty;

	public:
		VertexBufferObject();
		void add(glm::vec3 value);
		void add(glm::vec4 value);
		int getComponents();
		int getDataSize();
		GLuint getId();

	};

}