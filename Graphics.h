#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <engine/Mesh.h>
#include <engine/Entity.h>
#include <engine/Camera.h>

namespace GameEngine {
	class Graphics {
		private:
			SDL_Window*		m_window		= nullptr;
			SDL_GLContext	m_context		= nullptr;

			void SwapBuffer() {
				SDL_GL_SwapWindow(m_window);
			}

			void ClearToGray() {
				glClearColor(0.5, 0.5, 0.5, 1.0);
				glClear(GL_COLOR_BUFFER_BIT);
			}
		protected:
		public:
			enum ErrorCodes {
				SDL_WINDOW_FAILED_TO_INIT = -1
			};

			Graphics() {
			}
			
			int Init() {
				m_window = SDL_CreateWindow(
					"My Game",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					640,
					480,
					SDL_WINDOW_OPENGL
				);

				if (m_window == nullptr) {
					return GameEngine::Graphics::ErrorCodes::SDL_WINDOW_FAILED_TO_INIT;
				}

				// Set our OpenGL version.
				// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

				// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

				// Turn on double buffering with a 24bit Z buffer.
				// You may need to change this to 16 or 32 for your system
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				m_context = SDL_GL_CreateContext(m_window);

				glewExperimental = GL_TRUE; 
				auto returnNum = glewInit();
				if (returnNum != GLEW_OK) {
					std::cout << glewGetErrorString(returnNum) << "\n";
				}

				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);

				return 0;
			}

			void PreRender() {
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
				ClearToGray();
			}

			void SetMatrix(Entity* _ent, const glm::mat4 &model)
			{
//				glm::mat4 mvp = camera->projectionMatrix * camera->viewMatrix * model;
//				_ent->GetComponent<Mesh>()->SetMatrix(mvp);
			}

			void PostRender() {
				SwapBuffer();
			}

			~Graphics() {

			}
	};
}