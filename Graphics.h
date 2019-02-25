#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <engine/Mesh.h>
#include <engine/Entity.h>
#include <engine/Camera.h>
#include <engine/Shader.h>
#include <engine/ResourceManager.h>
#include <engine/PostProcessShader.h>

namespace GameEngine {

	/// Graphics handler class for the engine
	/// @todo Would be nice if this class could also wrap GL functions (but this is out of scope)
	class Graphics {
		private:

			/// SDL Window pointer
			SDL_Window*		m_window		= nullptr;

			/// SDL OpenGL binding context pointer
			SDL_GLContext	m_context		= nullptr;
			
			/// Resolution of renderer in X
			GLint m_resolutionX;

			/// Resolution of renderer in Y
			GLint m_resolutionY;

			/// Map of PP effects
			std::vector<PostProcessShader*> m_postProcessingFX;
			std::vector<std::string> m_postProcessingFX_IDs;

			/// Framebuffer ID
			GLuint m_framebuffer;

			/// Render target texture (for PPFX shaders)
			GLuint m_renderedTexture;

			/// depth render buffer (for PPFX shaders)
			GLuint m_depthRenderBuffer;

			/// VBO for a basic quad used in rendering PPFX
			GLuint m_quad_vertexbuffer;

			/// VAO for a basic quad used in rendering PPFX
			GLuint m_quad_VertexArrayID;

			/// Texture ID used in main passthrough PPFX shader
			GLuint m_texID;

			/// Vertex array ID
			GLuint m_VertexArrayID;

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
				int resolutionY = 512,
				GameEngine::ResourceManager* resMan = nullptr
			);

			/// @deprecated Not really sure why it's commented-out tbh...
			void SetMatrix(Entity* _ent, const glm::mat4 &model);

			/// Function called before rendering scene
			void PreRender();

			/// Function called after rendering scene
			void PostRender();

			/// Sets the SDL_Window title
			void SetWindowTitle(const char* _title) {
				SDL_SetWindowTitle(this->m_window, _title);
			}

			/// Returns the X dimension of renderer resolution
			int getResX() {
				return (int)m_resolutionX;
			}

			/// Returns the Y dimension of renderer resolution
			int getResY() {
				return (int)m_resolutionY;
			}

			/// Registers a post-process shader to be used at the end of a frame
			void RegisterPostProcessingShader(PostProcessShader* _shader) {
				m_postProcessingFX.push_back(_shader);
				m_postProcessingFX_IDs.push_back(_shader->UID);
			};

			/// Unregisters a post-process shader used at the end of a frame
			void UnregisterPostProcessingShader(PostProcessShader* _shader) {
				for (size_t i = 0; i < (m_postProcessingFX.size()); i++) {
					if (_shader->UID == m_postProcessingFX.at(i)->UID) {
						m_postProcessingFX.erase(m_postProcessingFX.begin() + i);
						m_postProcessingFX_IDs.erase(m_postProcessingFX_IDs.begin() + i);
						return;
					}
				}
			};

			/// Unregisters a post-process shader used at the end of a frame
			void UnregisterPostProcessingShader(std::string UID) {
				for (size_t i = 0; i < (m_postProcessingFX.size()); i++) {
					if (UID == m_postProcessingFX.at(i)->UID) {
						m_postProcessingFX.erase(m_postProcessingFX.begin() + i);
						m_postProcessingFX_IDs.erase(m_postProcessingFX_IDs.begin() + i);
						return;
					}
				}
			};

			/// Iterates over PPFX shaders and updates them
			void UpdatePPShaders() {
				for (size_t i = 0; i < m_postProcessingFX.size(); i++) {
					m_postProcessingFX.at(i)->Update();
				}
			}
	};
}