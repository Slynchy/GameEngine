#pragma once
#include <glm/glm.hpp>
namespace GameEngine {
	class Entity;

	/// Lightweight base class for components for entities
	class Component {
		private:
			Entity* m_parent;

		protected:
		public:
			Component() {
				m_parent = nullptr;
			}
			
			/// Get the parent of this component
			/// @returns The parent Entity object (if exists), else nullptr
			Entity* GetParent() {
				return m_parent;
			}
			
			/// Sets the parent of the component
			/// @param[in] _parent The parent entity pointer
			/// @returns True if successful, false if not
			/// @bug Only returns true.
			bool SetParent(Entity* _parent) {
				m_parent = _parent;
				return true;
			}

			virtual void Update(float delta) {};
			virtual void Init() {};
			virtual void Destroy() {};

			~Component() {
				m_parent = nullptr;
			}
	};
}