#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <engine/Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

namespace GameEngine {

	/// Transform component for representing objects in 2D/3D
	class Transform : public GameEngine::Component {
		private:
			glm::vec3 m_position;
			glm::vec3 m_angles;
			glm::vec3 m_scale;

		protected:
		public:
			Transform(glm::vec3 _pos = glm::vec3(0, 0, 0)) {
				m_position = _pos;
				m_angles = glm::vec3(0, 0, 0);
				m_scale = glm::vec3(1, 1, 1);
			}

			/// Gets the translation matrix based on the position
			/// @returns Matrix4x4 for use in constructing model matrix
			glm::mat4 getTranslationMatrix() {
				return glm::translate(glm::mat4(1.0f), this->m_position);
			}

			/// Gets the rotation matrix based on the orientation
			/// @returns Matrix4x4 for use in constructing model matrix
			glm::mat4 getRotationMatrix() {
				auto one = glm::rotate(
					glm::mat4(1.0f), 
					glm::radians(m_angles.x), 
					glm::vec3(1, 0, 0)
				);
				auto two = glm::rotate(
					one,
					glm::radians(m_angles.y),
					glm::vec3(0, 1, 0)
				);
				auto three = glm::rotate(
					two,
					glm::radians(m_angles.z), 
					glm::vec3(0, 0, 1)
				);
				return (three);
			}

			/// Gets the scale matrix based on the scale
			/// @returns Matrix4x4 for use in constructing model matrix
			glm::mat4 getScaleMatrix() {
				return glm::scale(this->m_scale);
			}

			/// Sets the position of the transform
			glm::vec3 setPosition(glm::vec3 _pos) {
				return this->m_position = _pos;
			}

			/// Gets the position of the transform
			glm::vec3 getPosition() {
				return this->m_position;
			}

			/// Gets a pointer to the position 
			glm::vec3* getPositionPtr() {
				return &this->m_position;
			}

			/// Gets X position
			float x() {
				return m_position.x;
			}

			/// Sets X position
			float x(float _x) {
				return m_position.x = _x;
			}

			/// Gets Y position
			float y() {
				return m_position.y;
			}

			/// Sets Y position
			float y(float _y) {
				return m_position.y = _y;
			}

			/// Gets Z position
			float z() {
				return m_position.z;
			}

			/// Sets Z position
			float z(float _z) {
				return m_position.z = _z;
			}

			/// Gets position
			glm::vec3 position() {
				return this->getPosition();
			}

			/// Sets scale of the transform
			void setScale(float x, float y, float z) {
				this->m_scale = glm::vec3(x, y, z);
			}

			/// Rotates the transform
			/// @param[in] amount The amount to rotate by on each axis
			/// @param[in] delta Delta time 
			/// @param[in] speed Speed of rotation
			void Rotate(glm::vec3 amount, float delta, float speed = 10.0f)
			{
				m_angles += (amount * speed * delta);
			}

			/// @deprecated Unused?
			void Calculate(){}

			/// Translate the transform
			/// @param[in] amount The amount to translate by on each axis
			/// @param[in] delta Delta time 
			/// @param[in] speed Speed of translation
			/// @bug Does not consider speed
			void Move(glm::vec3 amount, float delta, float Speed = 10.f)
			{
				this->m_position += amount * delta;
			}
	};
}