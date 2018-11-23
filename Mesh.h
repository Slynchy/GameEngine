#pragma once

#include <GL/glew.h>
#include <vector>

namespace GameEngine {

	/// Class for constructing/holding mesh-specific data 
	class Mesh
	{
		private:

		protected:
		public:

			// These are public because this class is a glorified struct
			
			/// The GL ID for the vertex array
			GLuint vertArrayID;
			
			/// The GL ID for the vertex buffer
			GLuint vertBuffer;

			/// The GL ID for the color buffer
			GLuint colorbuffer;

			/// The GL ID for the uv buffer
			GLuint uvBuffer;

			/// Initializes the mesh with the parameterised data
			/// @param[in] vertex_buffer_data The buffer data for the vertexes
			/// @param[in] uv_buffer_data The buffer data for the UV co-ords
			void Init(std::vector<GLfloat> vertex_buffer_data, std::vector<GLfloat> uv_buffer_data);

			Mesh();

			/// @bug does not cleanup GL data
			~Mesh() {
				
			};
	};

}