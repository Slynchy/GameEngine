#pragma once

#include <engine/Resource.h>
#include <vector>
#include <string>

namespace GameEngine {

	class Mesh;

	class Model : public Resource {

	public:
		std::vector<Mesh*> m_meshes;

		Model(std::string filepath);

	};

}