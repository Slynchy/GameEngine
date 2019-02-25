#include "SceneManager.h"

GameEngine::SceneManager::SceneManager(Graphics* _graphicsPtr) {
	m_graphics = _graphicsPtr;
	active_scene = new GameEngine::Scene(m_graphics);
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

unsigned int GameEngine::SceneManager::AddToScene(std::shared_ptr<Entity> _ent) {
	m_sceneGraph.push_back(_ent);
	return m_sceneGraph.size();
}

void GameEngine::SceneManager::Render() {
	this->active_camera->UpdateViewMatrix();
	this->m_graphics->UpdatePPShaders();
	auto projection = this->active_camera->projectionMatrix;
	auto view = this->active_camera->viewMatrix;

	for (std::shared_ptr<Entity> ent : m_sceneGraph) {
		ent->Render(projection, view, glm::vec3(0.0f));
	}
}

unsigned int GameEngine::SceneManager::RemoveFromScene(std::shared_ptr<Entity> _ent) {
	for (size_t i = 0; i < this->m_sceneGraph.size(); i++) {
		auto curr = this->m_sceneGraph.at(i);

		if (curr == _ent) {
			this->m_sceneGraph.erase(this->m_sceneGraph.begin() + i);
			return i;
		}
	}
}

void GameEngine::SceneManager::Update(float delta) {
	for (std::shared_ptr<Entity> ent : m_sceneGraph) {
		ent->Update(delta);
	}
}

GameEngine::SceneManager::~SceneManager() {

}