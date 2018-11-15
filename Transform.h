#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <engine/Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

namespace GameEngine {
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

			glm::mat4 getTranslationMatrix() {
				return glm::translate(glm::mat4(1.0f), this->m_position);
			}

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

			glm::mat4 getScaleMatrix() {
				return glm::scale(this->m_scale);
			}

			glm::vec3 setPosition(glm::vec3 _pos) {
				return this->m_position = _pos;
			}

			glm::vec3 getPosition() {
				return this->m_position;
			}

			glm::vec3* getPositionPtr() {
				return &this->m_position;
			}

			float x() {
				return m_position.x;
			}

			float x(float _x) {
				return m_position.x = _x;
			}

			float y() {
				return m_position.y;
			}

			float y(float _y) {
				return m_position.y = _y;
			}

			float z() {
				return m_position.z;
			}

			float z(float _z) {
				return m_position.z = _z;
			}

			glm::vec3 position() {
				return m_position;
			}

			void Rotate(glm::vec3 amount, float delta, float speed = 10.0f)
			{
				m_angles += (amount * speed * delta);
			}

			void Calculate()
			{
			}

			void Move(glm::vec3 Amount, float Delta, float Speed = 10.f)
			{
				this->m_position += Amount * Delta;
			}
	};
}