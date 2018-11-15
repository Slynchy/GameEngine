#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>

namespace GameEngine
{

	class VertexBufferObject;

	class VertexArrayObject
	{
		GLuint id;
		bool dirty;
		std::vector<std::shared_ptr<VertexBufferObject> > buffers;

	public:
		VertexArrayObject();
		void setBuffer(std::string attribute, std::weak_ptr<VertexBufferObject> buffer);
		int getVertexCount();
		GLuint getId();

	};

}