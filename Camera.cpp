
#include "Camera.h"

GameEngine::Camera::Camera(int resolutionX, int resolutionY)
{
	this->transform = this->GetComponent<Transform>();


	// TODO: make parameterisable 
	this->projectionMatrix = glm::perspective(
		45.0f,
		(float)resolutionX / (float)resolutionY,
		0.1f,
		5000.0f
	);

	this->UpdateViewMatrix();
}

void GameEngine::Camera::lockToTarget(Entity* target) {
	this->lookAtTarget = target->GetComponent<Transform>()->getPositionPtr();
	this->UpdateViewMatrix();
}

void GameEngine::Camera::lockToTarget(glm::vec3* target) {
	this->lookAtTarget = target;
	this->UpdateViewMatrix();
}

void GameEngine::Camera::clearLockToTarget() {
	this->lookAtTarget = nullptr;
}

void GameEngine::Camera::setPosition(glm::vec3 _pos) {
	this->transform->setPosition(_pos);
	this->UpdateViewMatrix();
}

glm::mat4 GameEngine::Camera::GetViewMatrix()
{
	return viewMatrix;
}

void GameEngine::Camera::Rotate(float _pitch, float _yaw, float _roll) {

	pitch += _pitch * 0.05f;
	yaw += _yaw * 0.05f;

	glm::vec3 _front;
	_front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	_front.y = sin(glm::radians(pitch));
	_front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = glm::normalize(_front);

	this->UpdateViewMatrix();
}

void GameEngine::Camera::Move(glm::vec3 pos, float _delta, float _speed) {
	this->Move(pos.x, pos.y, pos.z, _delta, _speed);
}

void GameEngine::Camera::Move(float _x, float _y, float _z, float _delta, float _speed) {

	this->MoveForward(_z);
	this->MoveRight(_x);

	this->transform->setPosition(this->transform->getPosition() + glm::vec3(0, _y, 0));

	this->UpdateViewMatrix();
}

void GameEngine::Camera::MoveForward(float _speed) {
	glm::vec3 newPos = this->transform->getPosition() + (this->front * _speed);

	this->transform->setPosition(newPos);

	this->UpdateViewMatrix();
}

void GameEngine::Camera::MoveRight(float _speed) {
	auto right = glm::cross(glm::normalize(front), glm::normalize(up));

	auto test = this->transform->getPosition() + (right * _speed);

	this->transform->setPosition(test);

	this->UpdateViewMatrix();
}

void GameEngine::Camera::UpdateViewMatrix() {
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
}