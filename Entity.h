#pragma once

#include <vector>
#include <engine/Component.h>
#include <engine/Transform.h>
#include <memory>
#include <map>
#include <typeindex>

namespace GameEngine {
	class Entity {
		private:
			std::map<std::type_index, void*> m_components;

			std::vector<Entity*> m_children;

			Entity* m_parent = nullptr;

		protected:
		public:
			Entity() {
				this->AddComponent(new Transform());
			}

			Entity* getParent() {
				return this->m_parent;
			}

			void setParent(Entity* _par) {
				this->m_parent = _par;
			}

			void AddChild(Entity* _child) {
				if (_child->getParent() != nullptr) {
					_child->getParent()->RemoveChild(_child);
				}

				this->m_children.push_back(_child);
				_child->setParent(this);
			}

			void RemoveChild(Entity* _child) {
				for (size_t i = 0; i < this->m_children.size(); i++) {
					auto curr = this->m_children.at(i);

					if (curr == _child) {
						this->m_children.erase(this->m_children.begin() + i);
						return;
					}
				}
			}

			template <class t>
			void AddComponent(t* _comp) {
				m_components.insert(std::make_pair<std::type_index, void*>(typeid(t), (void*)_comp));
				
				auto temp = static_cast<Component*>(_comp);
				temp->SetParent(this);
				temp->Init();
			}

			template <class t>
			t* GetComponent(){
				std::type_index typeName = typeid(t);
				for (auto it = this->m_components.begin(); it != this->m_components.end(); it++)
				{
					if (it->first == typeName) {
						return static_cast<t*>(it->second);
					}
				}
			}

			virtual void Update(float delta, glm::mat4 projection, glm::mat4 view, glm::vec3 offset = glm::vec3(0.0f)) {
				std::map<std::type_index, void*>::iterator it;
				for (it = m_components.begin(); it != m_components.end(); it++)
				{
					static_cast<Component*>(it->second)->Update(delta, projection, view, offset);
				}

				for (size_t i = 0; i < this->m_children.size(); i++) {
					this->m_children.at(i)->Update(delta, projection, view, offset + this->GetComponent<Transform>()->getPosition());
				}
			}

			~Entity() {
				for (std::pair<std::type_index, void*> comp : m_components) {
					delete comp.second;
				}
				m_components.clear();
			}
	};
}