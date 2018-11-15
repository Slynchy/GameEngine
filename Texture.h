#pragma once

#include <engine/Resource.h>
#include <GL/glew.h>
#include <string>

namespace GameEngine {


	class Texture : public Resource {
	private:
		GLuint tex_2d;

		/// @deprecated
		bool m_loaded = false;

	public:
		Texture(std::string _path);

		GLuint getTexID() {
			return this->tex_2d;
		}

		~Texture() {
			m_loaded = false;
		}
	};

}