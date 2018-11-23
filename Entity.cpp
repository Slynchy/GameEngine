
#include "Entity.h"
#include <engine/MeshRenderer.h>
#include <engine/Component.h>
#include <engine/Transform.h>
#include <memory>

GameEngine::Entity::Entity() {
	this->AddComponent(new Transform());
}

GameEngine::Entity* GameEngine::Entity::getParent() {
	return this->m_parent;
}

void GameEngine::Entity::setParent(Entity* _par) {
	this->m_parent = _par;
}

void GameEngine::Entity::AddChild(Entity* _child) {
	if (_child->getParent() != nullptr) {
		_child->getParent()->RemoveChild(_child);
	}

	this->m_children.push_back(_child);
	_child->setParent(this);
}

void GameEngine::Entity::RemoveChild(Entity* _child) {
	for (size_t i = 0; i < this->m_children.size(); i++) {
		auto curr = this->m_children.at(i);

		if (curr == _child) {
			this->m_children.erase(this->m_children.begin() + i);
			return;
		}
	}
}

void GameEngine::Entity::Render(glm::mat4 projection, glm::mat4 view, glm::vec3 offset) {
	std::map<std::type_index, void*>::iterator it;
	for (it = m_components.begin(); it != m_components.end(); it++)
	{
		if (it->first == typeid(MeshRenderer)) {
			static_cast<MeshRenderer*>(it->second)->Render(projection, view, offset);
			break;
		}
	}

	for (size_t i = 0; i < this->m_children.size(); i++) {
		this->m_children.at(i)->Render(projection, view, offset + this->GetComponent<Transform>()->getPosition());
	}
}

void GameEngine::Entity::Update(float delta) {
	std::map<std::type_index, void*>::iterator it;
	for (it = m_components.begin(); it != m_components.end(); it++)
	{
		static_cast<Component*>(it->second)->Update(delta);
	}

	for (size_t i = 0; i < this->m_children.size(); i++) {
		this->m_children.at(i)->Update(delta);
	}
}

GameEngine::Entity::~Entity() {
	for (std::pair<std::type_index, void*> comp : m_components) {
		static_cast<Component*>(comp.second)->Destroy();
	}
	m_components.clear();
}