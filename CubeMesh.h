#pragma once

#include <engine/Mesh.h>
#include <vector>

namespace GameEngine {
	
	class CubeMesh : public Mesh {

	private:

		const std::vector<GLfloat> g_cube_uv_buffer_data = {
			0.000059f, 0.000004f,
			0.000103f, 0.336048f,
			0.335973f, 0.335903f,
			1.000023f, 0.000013f,
			0.667979f, 0.335851f,
			0.999958f, 0.336064f,
			0.667979f, 0.335851f,
			0.336024f, 0.671877f,
			0.667969f, 0.671889f,
			1.000023f, 0.000013f,
			0.668104f, 0.000013f,
			0.667979f, 0.335851f,
			0.000059f, 0.000004f,
			0.335973f, 0.335903f,
			0.336098f, 0.000071f,
			0.667979f, 0.335851f,
			0.335973f, 0.335903f,
			0.336024f, 0.671877f,
			1.000004f, 0.671847f,
			0.999958f, 0.336064f,
			0.667979f, 0.335851f,
			0.668104f, 0.000013f,
			0.335973f, 0.335903f,
			0.667979f, 0.335851f,
			0.335973f, 0.335903f,
			0.668104f, 0.000013f,
			0.336098f, 0.000071f,
			0.000103f, 0.336048f,
			0.000004f, 0.671870f,
			0.336024f, 0.671877f,
			0.000103f, 0.336048f,
			0.336024f, 0.671877f,
			0.335973f, 0.335903f,
			0.667969f, 0.671889f,
			1.000004f, 0.671847f,
			0.667979f, 0.335851f
		};

		const std::vector<GLfloat> g_cube_vertex_buffer_data = {
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				 1.0f, 1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				 1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				 1.0f,-1.0f,-1.0f,
				 1.0f, 1.0f,-1.0f,
				 1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				 1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				 1.0f,-1.0f, 1.0f,
				 1.0f, 1.0f, 1.0f,
				 1.0f,-1.0f,-1.0f,
				 1.0f, 1.0f,-1.0f,
				 1.0f,-1.0f,-1.0f,
				 1.0f, 1.0f, 1.0f,
				 1.0f,-1.0f, 1.0f,
				 1.0f, 1.0f, 1.0f,
				 1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				 1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				 1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				 1.0f,-1.0f, 1.0f
		};

	protected:
	public:

		CubeMesh() {
			Mesh::Mesh();
			this->Init(g_cube_vertex_buffer_data, g_cube_uv_buffer_data);
		}

		~CubeMesh() {

		}

	};

}