#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <engine/Mesh.h>
#include <engine/Entity.h>
#include <engine/Camera.h>

namespace GameEngine {

	/// Graphics handler class for the engine
	/// @todo Would be nice if this class could also wrap GL functions (but this is out of scope)
	class Graphics {
		private:

			/// SDL Window pointer
			SDL_Window*		m_window		= nullptr;

			/// SDL OpenGL binding context pointer
			SDL_GLContext	m_context		= nullptr;

			/// Swaps buffer to screen using SDL
			void SwapBuffer() {
				SDL_GL_SwapWindow(m_window);
			}

			/// Clears screen buffer to grey
			void ClearToGray() {
				glClearColor(0.5, 0.5, 0.5, 1.0);
				glClear(GL_COLOR_BUFFER_BIT);
			}
		protected:
		public:

			/// Error codes to return during initialization
			enum ErrorCodes {
				SDL_WINDOW_FAILED_TO_INIT = -1,
				ALL_OKAY = 0
			};

			Graphics() {}
			~Graphics() {}
			
			/// Initializes the graphics engine via SDL
			/// @param[in] title Name of the window
			/// @param[in] screenPosX,screenPosY Position of the window on the user's screen
			/// @param[in] resolutionX,resolutionY The resolution to render at (be sure to update projection matrix of camera)
			/// @bug Doesn't support fullscreen
			int Init(
				const char* title = "GameEngine",
				int screenPosX = SDL_WINDOWPOS_CENTERED,
				int screenPosY = SDL_WINDOWPOS_CENTERED,
				int resolutionX = 512,
				int resolutionY = 512
			);

			/// @deprecated Not really sure why it's commented-out tbh...
			void SetMatrix(Entity* _ent, const glm::mat4 &model);

			/// Function called before rendering scene
			void PreRender();

			/// Function called after rendering scene
			void PostRender();
	};
}