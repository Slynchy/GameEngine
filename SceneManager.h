#pragma once

#include <vector>
#include <engine/Entity.h>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/Mesh.h>
#include <engine/Graphics.h>
#include <engine/Camera.h>

namespace GameEngine {

	class SceneManager {
		private:
			Graphics* m_graphics;

			GameEngine::Camera* camera;

			std::vector<std::shared_ptr<Entity>> m_sceneGraph;

		protected:
		public:
			SceneManager(Graphics* _graphicsPtr) {
				m_graphics = _graphicsPtr;
				camera = new GameEngine::Camera();
				this->AddToScene(camera);
			}

			GameEngine::Camera* getCamera() {
				return this->camera;
			}

			unsigned int AddToScene(Entity* _ent) {
				m_sceneGraph.push_back(std::shared_ptr<Entity>(_ent));
				return m_sceneGraph.size();
			}

			void Update() {
				auto projection = this->camera->projectionMatrix;
				auto view = this->camera->viewMatrix;

				for (std::shared_ptr<Entity> ent : m_sceneGraph) {
					ent->Update(projection, view);
				}
			}

			~SceneManager() {

			}
	};

}