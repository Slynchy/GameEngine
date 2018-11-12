#pragma once

#include <vector>
#include <engine/Entity.h>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/Mesh.h>
#include <engine/Graphics.h>
#include <engine/Scene.h>
#include <engine/Camera.h>

namespace GameEngine {

	class SceneManager {
		private:
			Graphics* m_graphics;

			GameEngine::Camera* active_camera;
			GameEngine::Scene* active_scene;

			std::vector<std::shared_ptr<Entity>> m_sceneGraph;

		protected:
		public:
			SceneManager(Graphics* _graphicsPtr) {
				m_graphics = _graphicsPtr;
				active_scene = new GameEngine::Scene();
				active_camera = active_scene->getCamera();
				//this->AddToScene(camera);
			}

			GameEngine::Camera* getCamera() {
				return this->active_camera;
			}

			unsigned int AddToScene(Entity* _ent) {
				m_sceneGraph.push_back(std::shared_ptr<Entity>(_ent));
				return m_sceneGraph.size();
			}

			void Update() {
				auto projection = this->active_camera->projectionMatrix;
				auto view = this->active_camera->viewMatrix;

				for (std::shared_ptr<Entity> ent : m_sceneGraph) {
					ent->Update(projection, view);
				}
			}

			~SceneManager() {

			}
	};

}