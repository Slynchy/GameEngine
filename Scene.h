#pragma once

#include <vector>

namespace GameEngine {

	class Camera;
	class Entity;

	class Scene
	{
	protected:

		/// Basic scene graph using vectors
		/// @todo Refactor into format that support spatial partitioning easier
		std::vector<GameEngine::Entity*> m_sceneGraph;

		/// Current camera in scene
		GameEngine::Camera* camera;

	public:
		Scene();
		~Scene();

		/// Intended to be overriden
		virtual void Update();

		/// Clears the current scene of all objects and destroys them (sans camera)
		void ClearScene();

		/// Gets the current camera in the scene
		Camera* getCamera();

		/// Adds an object to the scene
		/// @param[in] _ent Pointer to entity to add to scene
		/// @returns Number of objects in scene (whatever it was + 1)
		/// @bug No remove function? We can only add?
		size_t Add(Entity* _ent);
	};

}
