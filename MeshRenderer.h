#pragma once

#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <engine/Component.h>
#include <engine/Transform.h>
#include <engine/Mesh.h>

namespace GameEngine {
	class MeshRenderer : public GameEngine::Component {
	private:
		/// ID of shader assigned to this MeshRenderer
		GLuint shaderID;

		/// ID of texture assigned to this MeshRenderer
		GLuint textureID;

		/// ID of texture uniform in the shader assigned to this MeshRenderer
		GLuint textureUniID;

		/// Model matrix for this meshrenderer
		glm::mat4 modelMat;

		/// ID for model matrix uniform in shader assigned to this MeshRenderer
		GLuint matID;

		/// Vector of meshes to be rendered by this MeshRenderer
		std::vector<Mesh> m_meshes;

		/// Draws the mesh(es) to the GPU using the proj/view matrices supplied
		///
		/// @private
		/// @param[in]	projection	The projection matrix to use
		/// @param[in]	view		The view matrix supplied from the camera
		/// @param[in]	offset		The position offset to draw at (usually additive of all parents positions)
		void Draw(glm::mat4 projection, glm::mat4 view, glm::vec3 offset);

	public:
		MeshRenderer(GLuint shaderID, GLuint texID = 0);

		/// Initializes the MeshRenderer with data from an OBJ
		/// @bug Despite knowing what textures to use, still needs user to manually supply it
		/// @param[in]	_filepath	The path to the obj file
		void InitFromOBJ(std::string _filepath);

		/// Adds a mesh to the MeshRenderer
		/// @param[in]	mesh	The mesh to add
		void AddMesh(Mesh mesh) { m_meshes.push_back(mesh); }

		/// Destroys this component
		/// @bug FIX THIS, BREAKS IF NOT A POINTER
		/// @todo FIX THIS, BREAKS IF NOT A POINTER
		void Destroy() { }

		/// Gets the model-view-projection matrix for this MeshRenderer
		/// @param[in]	projection	The projection matrix to use
		/// @param[in]	view		The view matrix supplied from the camera
		/// @param[in]	offset		The position offset to draw at (usually additive of all parents positions)
		glm::mat4 getMVP(glm::mat4 projection, glm::mat4 view, glm::vec3 offset);

		/// Draws the mesh(es) to the GPU using the proj/view matrices supplied
		///
		/// @private
		/// @param[in]	projection	The projection matrix to use
		/// @param[in]	view		The view matrix supplied from the camera
		/// @param[in]	offset		The position offset to draw at (usually additive of all parents positions)
		void Render(glm::mat4 projection, glm::mat4 view, glm::vec3 offset = glm::vec3(0.0f)) { Draw(projection, view, offset); }

		/// @deprecated
		void Update(float delta) {};
	};
}