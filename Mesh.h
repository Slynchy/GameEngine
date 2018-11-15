#pragma once

#include <GL/glew.h>
#include "VertexArrayObject.h"

namespace GameEngine {

	class Mesh
	{
		private:
			VertexArrayObject VAO;
			GLuint colorbuffer;
			GLuint uvBuffer;
		protected:
		public:
			Mesh() {};
			~Mesh() {};


	};

}