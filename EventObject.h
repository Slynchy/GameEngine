#pragma once

#include <SDL2/SDL_events.h>

namespace GameEngine {

	/// Very simple class for binding functions to SDL events
	/// @deprecated Not entirely but is only used for SDL_Quit event 
	class EventObject {
		private:
			/// @detail Function pointer to function that takes SDL_Event as param and returns int
			int(*m_function)(SDL_Event* _event);
		protected:
		public:
			EventObject(int(*_function)(SDL_Event* _event)) {
				m_function = _function;
			}

			/// Call the bound function with the SDL_Event object ptr
			void Call(SDL_Event* _event) {
				m_function(_event);
			}

			~EventObject() {
				m_function = nullptr;
			}
	};
}