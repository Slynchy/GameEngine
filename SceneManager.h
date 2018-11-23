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

			/// Pointer to graphics handler of engine
			/// @detail Passed in via constructor; shouldn't change
			Graphics* m_graphics;

			/// Active camera to use
			GameEngine::Camera* active_camera;

			/// Active scene
			/// @bug does nothing
			/// @todo remove scene graph from scenemanager and get from Scene
			GameEngine::Scene* active_scene;

			/// Basic scene graph
			std::vector<std::shared_ptr<Entity>> m_sceneGraph;

		protected:
		public:
			SceneManager(Graphics* _graphicsPtr);

			/// Gets the active camera
			GameEngine::Camera* getCamera();

			/// Add an object to scene
			/// @param[in] _ent Pointer to entity to add
			/// @returns size of scene graph
			/// @bug Makes shared ptr but probably not doing correctly
			/// @bug No remove from scene? See Scene.h
			unsigned int AddToScene(Entity* _ent);

			/// Render all objects in scene
			void Render();

			/// Update all objects in scene against delta time
			/// @param[in] delta The delta time
			void Update(float delta);

			~SceneManager();
	};

}