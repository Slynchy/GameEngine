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

			virtual void Update(float delta, glm::mat4 projection, glm::mat4 view, glm::vec3 offset = glm::vec3(0.0f)) {};
			virtual void Init() {};
			virtual void Destroy() {};

			~Component() {
				m_parent = nullptr;
			}
	};
}