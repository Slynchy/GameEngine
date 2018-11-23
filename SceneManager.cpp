#include "SceneManager.h"

GameEngine::SceneManager::SceneManager(Graphics* _graphicsPtr) {
	m_graphics = _graphicsPtr;
	active_scene = new GameEngine::Scene();
	active_camera = active_scene->getCamera();
	//this->AddToScene(camera);
}

GameEngine::Camera* GameEngine::SceneManager::getCamera() {
	return this->active_camera;
}

unsigned int GameEngine::SceneManager::AddToScene(Entity* _ent) {
	m_sceneGraph.push_back(std::shared_ptr<Entity>(_ent));
	return m_sceneGraph.size();
}

void GameEngine::SceneManager::Render() {
	this->active_camera->UpdateViewMatrix();
	auto projection = this->active_camera->projectionMatrix;
	auto view = this->active_camera->viewMatrix;

	for (std::shared_ptr<Entity> ent : m_sceneGraph) {
		ent->Render(projection, view, glm::vec3(0.0f));
	}
}

void GameEngine::SceneManager::Update(float delta) {
	for (std::shared_ptr<Entity> ent : m_sceneGraph) {
		ent->Update(delta);
	}
}

GameEngine::SceneManager::~SceneManager() {

}