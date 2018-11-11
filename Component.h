#pragma once
#include <glm/glm.hpp>
namespace GameEngine {
	class Entity;

	class Component {
		private:
			Entity* m_parent;

		protected:
		public:
			Component() {

			}

			Entity* GetParent() {
				return m_parent;
			}

			bool SetParent(Entity* _parent) {
				m_parent = _parent;
				return true;
			}

			virtual void Update(glm::mat4 projection, glm::mat4 view) {};
			virtual void Init() {};

			~Component() {
				m_parent = nullptr;
			}
	};
}