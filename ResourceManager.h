#pragma once

#include <GL/GL.h>
#include <GL/glew.h>
#include <string>
#include <map>
#include <vector>
#include <stb_image.h>

namespace GameEngine {
	
	class Resource {
	public:
		Resource() {

		}

		~Resource() {

		}
	};

	class Texture : public Resource {
	private:
		GLuint tex_2d;

		/// @deprecated
		bool m_loaded = false;

	public:
		Texture(std::string _path) {
			// todo: implement properly

			int w, h, comp;
			unsigned char* image = stbi_load(_path.c_str(), &w, &h, &comp, STBI_rgb);
			if (image == nullptr) {
				printf("Failed to load %s\n", _path.c_str());
			}

			glGenTextures(1, &tex_2d);
			glBindTexture(GL_TEXTURE_2D, tex_2d);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(image);

			m_loaded = true;
		}

		GLuint getTexID() {
			return this->tex_2d;
		}

		~Texture() {
			m_loaded = false;
		}
	};

	class ResourceManager
	{
	private:
		std::map<std::string, Texture*> m_loadedTextures;

	public:
		ResourceManager() {

		};

		void UnloadTexture(std::string _id) {
			// TODO: implement
		}

		std::string LoadTexture(std::string _path) {
			Texture* temp = new Texture(_path);
			this->m_loadedTextures.insert(std::pair<std::string, Texture*>(_path, temp));
			return _path;
		}

		Texture* GetTexture(std::string _id) {
			if (m_loadedTextures.find(_id) == m_loadedTextures.end()) {
				return nullptr;
			}
			else {
				return m_loadedTextures.at(_id);
			}
		}

		~ResourceManager() {

		};
	};

}
