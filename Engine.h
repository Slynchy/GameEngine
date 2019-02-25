/// \file		Engine.h
/// \author		Sam Lynch
/// \brief		Header file for game engine
/// \version	0.0.0
/// \date		October 2018
/// \details	The header file for declaring the engine and its components. The doxygen formatting will- to your surprise- mostly not use JavaDoc (JSDoc) standards.

#pragma once

#include <SDL2/SDL.h>
#include <engine/Graphics.h>
#include <engine/Events.h>

#include <engine/Entity.h>
#include <engine/Mesh.h>
#include <engine/SceneManager.h>
#include <engine/InputManager.h>
#include <engine/ResourceManager.h>
#include <engine/Audio.h>

namespace GameEngine {

	class Engine {
		private:
			/// Engine component for handling graphics/rendering
			GameEngine::Graphics*			m_graphics;

			/// Engine component for handling (SDL) events
			GameEngine::Events*				m_events;

			/// Engine component for keeping track of scenes and objects
			GameEngine::SceneManager*		m_sceneManager;

			/// Engine component for managing input (via SDL)
			GameEngine::InputManager*		m_inputManager;

			/// Engine component for handling loading/fetching resources
			GameEngine::ResourceManager*	m_resourceManager;

			/// Engine component for handling audio
			GameEngine::Audio*				m_audio;

		protected:
		public:

			/// Enumerator for possible error codes when engine is initializing
			enum ErrorCodes {
				SDL_FAILED_TO_INIT = -1,
				ALL_OKAY = 0
			};

			GameEngine::InputManager*		GetInputManager()			{ return m_inputManager; }
			GameEngine::SceneManager*		GetSceneManager()			{ return m_sceneManager; }
			GameEngine::Events*				GetEvents()					{ return m_events; }
			GameEngine::Graphics*			GetGraphics()				{ return m_graphics; }
			GameEngine::ResourceManager*	GetResourceManager()		{ return this->m_resourceManager; }

			/// @param[in] autoInit If true, constructor will also initialize engine. Discouraged but possible.
			Engine(bool autoInit = false) {
				if (autoInit) {
					int err = Init();
					if (err) {
						printf("Error encountered when auto init'ing engine. Code: %i \n", err);
					}
				}
			}

			/// Initializes the engine, setting up the handlers needed and a basic scenegraph
			/// @param resolutionX The X dimension for the window/renderer. Optional.
			/// @param resolutionY The Y dimension for the window/renderer. Optional.
			/// @returns Non-zero error code if error encountered, zero if all-okay. See this->ErrorCodes
			int Init(int resolutionX = 512, int resolutionY = 512);

			void Render();

			void Update(float delta);

			~Engine();
	};

}