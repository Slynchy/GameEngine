#pragma once

#include <glm/glm.hpp>
#include <engine/Transform.h>
#include <engine/Entity.h>
#include <iostream>

namespace GameEngine {

	/// Camera entity class; every scene needs at least one
	class Camera : public Entity {
		private:

			/// Pointer to transform component that is automagically added to all Entitys
			Transform* transform;

			/// Pointer to a position vector of an object to lookat
			glm::vec3* lookAtTarget = nullptr;

		protected:
		public:
			/// The projection matrix of the camera
			glm::mat4 projectionMatrix;

			/// The view matrix of the camera
			glm::mat4 viewMatrix; 

			/// The front vector
			glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

			/// The up vector
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

			// Rotations
			float pitch = 0.0f;
			float yaw = 0.0f;
			float roll = 0.0f;

			Camera();

			/// Locks the camera view to look at the target until told to stop
			/// @deprecated
			void lockToTarget(Entity* target);

			/// Locks the camera view to look at the target until told to stop
			void lockToTarget(glm::vec3* _ptr);

			/// Stops the camera looking at a target
			void clearLockToTarget();

			/// Sets the position of the camera
			void setPosition(glm::vec3 _pos);

			/// Gets the cameras view matrix
			/// @deprecated ? The view matrix is public now?
			glm::mat4 GetViewMatrix();

			/// Rotates the camera direction from Euler angles
			/// @bug Currently ignores roll
			/// @param[in] _pitch The pitch to rotate by
			/// @param[in] _yaw The yaw to rotate by
			/// @param[in] _roll The roll to rotate by
			void Rotate(float _pitch, float _yaw, float _roll);

			/// Moves the camera by the offset specified
			/// @param[in] pos glm::vec3 for the position offset
			/// @param[in] _delta The delta time as a floating-point 
			/// @param[in] _speed The speed of movement
			void Move(glm::vec3 pos, float _delta = 0.1f, float _speed = 1.0f);

			/// Moves the camera by the offset specified
			/// @param[in] _x, _y, _z Amount to offset by
			/// @param[in] _delta The delta time as a floating-point 
			/// @param[in] _speed The speed of movement
			void Move(float _x, float _y, float _z, float _delta = 0.1f, float _speed = 1.0f);

			/// Moves the camera forward at a certain speed
			/// @bug Doesn't take into account delta time
			/// @param[in] _speed The speed/amount of movement
			void MoveForward(float _speed = 1.0f);

			/// Moves the camera to the right at a certain speed
			/// @bug Doesn't take into account delta time
			/// @param[in] _speed The speed/amount of movement
			void MoveRight(float _speed = 1.0f);

			/// Updates the view matrix of the camera based on position and direction (or target)
			void UpdateViewMatrix();
	};

}