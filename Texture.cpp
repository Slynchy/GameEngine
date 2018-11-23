#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include <stb_image.h>

using namespace GameEngine;

Texture::Texture(std::string _path) {
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);

	m_loaded = true;
}