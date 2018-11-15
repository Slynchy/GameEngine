#include "VertexBufferObject.h"

namespace GameEngine
{

	VertexBufferObject::VertexBufferObject() : components(0), dirty(false)
	{
		glGenBuffers(1, &id);

		if (!id)
		{
			throw std::exception();
		}
	}

	void VertexBufferObject::add(glm::vec3 value)
	{
		if (!components)
		{
			components = 3;
		}

		if (components != 3)
		{
			throw std::exception();
		}

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);
		dirty = true;
	}

	void VertexBufferObject::add(glm::vec4 value)
	{
		if (!components)
		{
			components = 4;
		}

		if (components != 4)
		{
			throw std::exception();
		}

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);
		data.push_back(value.w);
		dirty = true;
	}

	int VertexBufferObject::getDataSize()
	{
		return data.size();
	}

	int VertexBufferObject::getComponents()
	{
		if (!components)
		{
			throw std::exception();
		}

		return components;
	}

	GLuint VertexBufferObject::getId()
	{
		if (dirty)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.at(0), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			dirty = false;
		}

		return id;
	}

}