
#include "Scene.h"
#include <engine/Camera.h>
#include <engine/Graphics.h>
#include <engine/Entity.h>

void GameEngine::Scene::Update() {};

GameEngine::Scene::Scene(GameEngine::Graphics* _graphics) {
	camera = new GameEngine::Camera(_graphics->getResX(), _graphics->getResY());
};

GameEngine::Scene::~Scene() {
	for (Entity* ent : m_sceneGraph) {
		delete ent;
	}
	m_sceneGraph.empty();
};

void GameEngine::Scene::ClearScene() {
	for (Entity* ent : m_sceneGraph) {
		delete ent;
	}
	m_sceneGraph.clear();
}

GameEngine::Camera* GameEngine::Scene::getCamera() {
	return this->camera;
}

size_t GameEngine::Scene::Add(Entity* _ent) {
	m_sceneGraph.push_back(_ent);
	return m_sceneGraph.size();
}