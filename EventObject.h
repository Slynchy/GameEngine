#pragma once

#include <SDL2/SDL_events.h>

namespace GameEngine {
	class EventObject {
		private:
			int(*m_function)(SDL_Event* _event);
		protected:
		public:
			EventObject(int(*_function)(SDL_Event* _event)) {
				m_function = _function;
			}

			void Call(SDL_Event* _event) {
				m_function(_event);
			}

			~EventObject() {
				m_function = nullptr;
			}
	};
}