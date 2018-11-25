#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include <tiny_obj_loader.h>
#include <engine/Mesh.h>

GameEngine::Model::Model(std::string filepath) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	std::string warn;

	filepath = "assets/models/" + filepath;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str())) {
		printf("Something went wrong when loading OBJ file %s \n", filepath.c_str());
		if (!err.empty()) {
			printf(err.c_str());
		}
		return;
	}

	// todo: replace with proper logging
	if (!err.empty()) {
		printf(err.c_str());
		// should be a warning; we already check retval from LoadObj
	}

	for (size_t s = 0; s < shapes.size(); s++) {
		size_t index_offset = 0;

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = shapes[s].mesh.num_face_vertices[f];
			std::vector<tinyobj::real_t> vert;
			std::vector<tinyobj::real_t> uv;

			for (size_t v = 0; v < fv; v++) {

				tinyobj::index_t ind = shapes[s].mesh.indices[index_offset + v];

				vert.push_back(attrib.vertices[3 * ind.vertex_index + 0]);
				vert.push_back(attrib.vertices[3 * ind.vertex_index + 1]);
				vert.push_back(attrib.vertices[3 * ind.vertex_index + 2]);

				uv.push_back(attrib.texcoords[2 * ind.texcoord_index + 0]);
				uv.push_back(attrib.texcoords[2 * ind.texcoord_index + 1]);

				// normals
					//tinyobj::real_t nx = attrib.normals[3 * ind.normal_index + 0];
					//tinyobj::real_t ny = attrib.normals[3 * ind.normal_index + 1];
					//tinyobj::real_t nz = attrib.normals[3 * ind.normal_index + 2];

				// colors 
					// tinyobj::real_t r = attrib.colors[3*ind.vertex_index+0];
					// tinyobj::real_t g = attrib.colors[3*ind.vertex_index+1];
					// tinyobj::real_t b = attrib.colors[3*ind.vertex_index+2];
			}
			index_offset += fv;
			Mesh* mesh = new Mesh();
			mesh->Init(vert, uv);
			this->m_meshes.push_back(mesh);
		}
	}
}