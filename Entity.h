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

		protected:
		public:
			Entity() {
				this->AddComponent(new Transform());
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

			void Update(glm::mat4 projection, glm::mat4 view) {
				std::map<std::type_index, void*>::iterator it;

				for (it = m_components.begin(); it != m_components.end(); it++)
				{
					static_cast<Component*>(it->second)->Update(projection, view);
				}
			}

			~Entity() {
				m_components.clear();
			}
	};
}