#pragma once

#include <typeindex>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <memory>

namespace GameEngine {

	/// Entity baseclass; think of it as GameObject from Unity
	class Entity {
		private:

			/// Mapping for components to type indices
			std::map<std::type_index, void*> m_components;

			/// The children of this entity
			/// @bug This should be handled by the Transform component.
			std::vector<std::shared_ptr<Entity>> m_children;

			/// The parent entity (if not root)
			std::weak_ptr<Entity> m_parent;

		protected:
		public:
			Entity();
			~Entity();

			/// Gets the parent entity or nullptr if non-existent
			std::weak_ptr<Entity> getParent();

			/// Sets the parent entity to the specified pointer
			void setParent(std::shared_ptr<Entity> _par);

			/// Adds a child to this entity (used in calculating relative positions)
			void AddChild(std::shared_ptr<Entity> _child);

			/// Removes the specified child from this entity
			void RemoveChild(std::shared_ptr<Entity> _child);

			/// Renders the entity using meshrenderers if it can find it
			/// @todo This does not consider 2D objects
			void Render(glm::mat4 projection, glm::mat4 view, glm::vec3 offset);

			/// Updates the entity, children, and components using the delta time
			virtual void Update(float delta);

			// The following two functions were previously in Entity.cpp but due to linking errors, they're 
			// actually defined here.

				/// Adds the specified component to this entity and initializes
				template <class t>
				void AddComponent(t* _comp) {
					m_components.insert(std::make_pair<std::type_index, void*>(typeid(t), (void*)_comp));

					auto temp = static_cast<Component*>(_comp);
					temp->SetParent(this);
					temp->Init();
				};

				/// Gets the specified component from this object if it exists, otherwise returns nullptr.
				template <class t>
				t* GetComponent() {
					std::type_index typeName = typeid(t);
					for (auto it = this->m_components.begin(); it != this->m_components.end(); it++)
					{
						if (it->first == typeName) {
							return static_cast<t*>(it->second);
						}
					}
					return nullptr;
				};
	};
}