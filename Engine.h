/// \file		Engine.h
/// \author		Sam Lynch
/// \brief		Header file for game engine
/// \version	0.0.0
/// \date		October 2018
/// \details	The header file for declaring the engine and its components.
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
			GameEngine::Graphics*			m_graphics;
			GameEngine::Events*				m_events;
			GameEngine::SceneManager*		m_sceneManager;
			GameEngine::InputManager*		m_inputManager;
			GameEngine::ResourceManager*	m_resourceManager;
			GameEngine::Audio*				m_audio;

		protected:
		public:
			Engine() {

			}

			enum ErrorCodes {
				SDL_FAILED_TO_INIT = -1
			};

			GameEngine::ResourceManager* GetResourceManager() {
				return this->m_resourceManager;
			}

			int Init() {
				if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
				{
					return GameEngine::Engine::ErrorCodes::SDL_FAILED_TO_INIT;
				}

				m_events = new GameEngine::Events();

				m_inputManager = new GameEngine::InputManager();

				m_resourceManager = new GameEngine::ResourceManager();

				m_audio = new GameEngine::Audio();

				m_graphics = new GameEngine::Graphics();
				int graphicsErrorCode;
				if ((graphicsErrorCode = m_graphics->Init()) < 0) {
					return graphicsErrorCode;
				} else {
					if (SDL_CaptureMouse(SDL_TRUE) != 0) {
						printf("SDL_CaptureMouse failed: %s\n", SDL_GetError());
					};
					if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0) {
						printf("SDL_SetRelativeMouseMode failed: %s\n", SDL_GetError());
					}
				}

				m_sceneManager = new GameEngine::SceneManager(m_graphics);

				return 0;
			}

			void Render() {
				m_graphics->PreRender();
				m_sceneManager->Render();
				m_graphics->PostRender();
			}

			void Update(float delta) {
				m_events->Update();
				//m_inputManager->Update();
				//m_graphics->PreRender();

				m_sceneManager->Update(delta);
				//m_graphics->SetMatrix(&(*testEntity), dynamic_cast<Mesh*>(testEntity->GetComponent("Mesh").get())->GetModel());
				//testEntity->Update();

				//m_graphics->PostRender();
			}

			GameEngine::InputManager* GetInputManager() {
				return m_inputManager;
			}

			GameEngine::SceneManager* GetSceneManager() {
				return m_sceneManager;
			}

			GameEngine::Events* GetEvents() {
				return m_events;
			}

			GameEngine::Graphics* GetGraphics() {
				return m_graphics;
			}

			~Engine() {
				delete m_graphics;
				delete m_events;
				delete m_sceneManager;
				delete m_inputManager;
				delete m_resourceManager;
				delete m_audio;
			}
	};

}