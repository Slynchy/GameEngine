#pragma once

#include <GL/glew.h>
#include <map>
#include <vector>
#include <string>
#include <engine/Sound.h>
#include <engine/Texture.h>
#include <engine/Model.h>

namespace GameEngine {

	class ResourceManager
	{
	private:
		/// Map of strings/IDs to loaded Textures
		std::map<std::string, Model*> m_loadedModels;

		/// Map of strings/IDs to loaded Textures
		std::map<std::string, std::shared_ptr<Texture>> m_loadedTextures;

		/// Map of strings/IDs to loaded shaders
		/// @todo: wrap shader uint as object
		std::map<std::string, GLuint> m_loadedShaders;

		/// Map of strings/IDs to loaded audio buffers
		std::map<std::string, std::shared_ptr<Sound>> m_loadedAudio;

	public:
		ResourceManager() {

		};

		~ResourceManager() {

		};

		/// Unloads a texture from openGL memory
		/// @bug Doesn't do anything
		/// @todo Implement
		void UnloadTexture(std::string _id) {}

		/// Loads and compiles a shader to the ID specified
		/// @detail Use GetShader(_id) to get the shader later
		/// @param[in] _id The key to store the shader under
		/// @param[in] vertex_file_path The path to the vert shader
		/// @param[in] fragment_file_path The path to the frag shader
		/// @returns A boolean; true if loaded successfully, false if not
		bool LoadShaders(const char* _id, const char * vertex_file_path, const char * fragment_file_path);

		/// Gets the shader under the ID if loaded
		/// @param[in] _id The key the shader is stored under
		/// @returns GLuint index to the shader in OGL memory, or 0 if not loaded
		GLuint GetShader(std::string _id);

		/// Loads a texture for use in OpenGL
		/// @detail Use GetTexture(_id) to get the texture later
		/// @param[in] _path The path to the texture
		/// @returns The ID it loaded into or an empty string if failed to load
		/// @bug Only works with BMP?
		std::string LoadTexture(std::string _path);

		/// Loads a mdl for use in MeshRenderer
		/// @detail Use GetTexture(_id) to get the mdl later
		/// @param[in] _path The path to the mdl
		/// @returns The ID it loaded into or an empty string if failed to load
		/// @bug Only works with OBJ?
		std::string LoadOBJ(std::string _path);

		/// Gets the model under the ID if loaded
		/// @param[in] _id The key the Model is stored under
		/// @returns The obj ptr, or nullptr if not loaded
		Model* GetOBJ(std::string _id);

		/// Gets the Texture under the ID if loaded
		/// @param[in] _id The key the Texture is stored under
		/// @returns The texture ptr, or nullptr if not loaded
		std::shared_ptr<Texture> GetTexture(std::string _id);

		/// Loads audio for use in engine
		/// @detail Use GetSound(_id) to get the sound later
		/// @param[in] path The path to the audio file
		/// @returns The ID it loaded into or an empty string if failed to load
		/// @bug Only works with WAV?
		std::string LoadSound(const char* path);

		/// Gets the Texture under the ID if loaded
		/// @param[in] _id The key the Texture is stored under
		/// @returns The texture ptr, or nullptr if not loaded
		std::shared_ptr<Sound> GetSound(std::string _id);
	};

}
