#pragma once

#include <glm/glm.hpp>
#include <engine/Transform.h>
#include <engine/Entity.h>
#include <iostream>

namespace GameEngine {

	class Camera : public Entity {
		private:
			Transform* transform;

			glm::vec3* lookAtTarget = nullptr;

		protected:
		public:
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix; 
			glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

			float pitch = 0.0f;
			float yaw = 0.0f;
			float roll = 0.0f;

			void lockToTarget(Entity* target) {
				this->lookAtTarget = target->GetComponent<Transform>()->getPositionPtr();
				this->UpdateViewMatrix();
			}

			void clearLockToTarget() {
				this->lookAtTarget = nullptr;
			}

			void setPosition(glm::vec3 _pos) {
				this->transform->setPosition(_pos);
				this->UpdateViewMatrix();
			}

			Camera()
			{
				this->transform = this->GetComponent<Transform>();
				//this->transform->setPosition(glm::vec3(0, 3, 3));

				this->projectionMatrix = glm::perspective(45.0f, (float)1280 / (float)720, 0.1f, 100.0f);

				this->UpdateViewMatrix();
			}

			glm::mat4 GetViewMatrix()
			{
				return viewMatrix;
			}

			void Rotate(float _pitch, float _yaw, float _roll) {

				pitch += _pitch * 0.05f;
				yaw += _yaw * 0.05f;

				glm::vec3 _front;
				_front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
				_front.y = sin(glm::radians(pitch));
				_front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
				front = glm::normalize(_front);

				this->UpdateViewMatrix();
			}

			void Move(glm::vec3 pos, float _delta = 0.1f, float _speed = 1.0f) {
				this->Move(pos.x, pos.y, pos.z, _delta, _speed);
			}

			void Move(float _x, float _y, float _z, float _delta = 0.1f, float _speed = 1.0f) {

				this->MoveForward(_z);
				this->MoveRight(_x);
				
				this->transform->setPosition(this->transform->getPosition() + glm::vec3(0, _y, 0));

				this->UpdateViewMatrix();
			}

			void MoveForward(float _speed = 1.0f) {
				auto test = this->transform->getPosition() + (this->front * _speed);

				this->transform->setPosition(test);

				this->UpdateViewMatrix();
			}

			void MoveRight(float _speed = 1.0f) {
				auto right = glm::cross(glm::normalize(front), glm::normalize(up));

				auto test = this->transform->getPosition() + (right * _speed);

				this->transform->setPosition(test);

				this->UpdateViewMatrix();
			}

			void UpdateViewMatrix() {

				if (this->lookAtTarget == nullptr) {
					this->viewMatrix = glm::lookAt(
						this->transform->getPosition(),
						(this->transform->getPosition() + this->front),
						this->up
					);
				}
				else {
					this->viewMatrix = glm::lookAt(
						this->transform->getPosition(),
						*this->lookAtTarget,
						this->up
					);
				}

				/*this->viewMatrix =
					glm::translate(this->transform->getPosition()) *
					glm::rotate(1.0f, glm::vec3(pitch, yaw, roll)) *
					glm::scale(glm::vec3(1.0f));*/
			}
	};

}