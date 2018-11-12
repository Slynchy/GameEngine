#pragma once

#include <vector>
#include <engine/Entity.h>
#include <engine/Camera.h>

namespace GameEngine {

	class Scene
	{
	protected:
		std::vector<GameEngine::Entity*> m_sceneGraph;
		GameEngine::Camera* camera;

	public:
		Scene() {
			camera = new GameEngine::Camera();
		};

		Camera* getCamera() {
			return this->camera;
		}

		virtual void Update() {};

		size_t Add(Entity* _ent) {
			m_sceneGraph.push_back(_ent);
			return m_sceneGraph.size();
		}

		~Scene() {
			for (Entity* ent : m_sceneGraph) {
				delete ent;
			}
			m_sceneGraph.empty();
		};
	};

}
