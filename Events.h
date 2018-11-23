#pragma once

#include <SDL2/SDL.h>
#include <engine/EventObject.h>
#include <map>
#include <functional>

namespace GameEngine {

	/// Simple class for event management via bound EventObjects to SDL Events
	/// @deprecated Only used for SDL_Quit
	/// @detail Won't move code contents to CPP since minimal code and includes
	class Events {
		private:
			SDL_Event m_events;
			std::multimap<int, EventObject*> m_eventMap;

		protected:
		public:
			Events() {

			}

			void Init() {}

			SDL_Event* getEvents() {
				return &this->m_events;
			}

			void Update() {
				// Iterate through the buffer of SDL events and handle them accordingly
				while (SDL_PollEvent(&m_events))
				{
					auto keys = m_eventMap.equal_range(m_events.type);

					for (std::multimap<int, EventObject*>::iterator it = keys.first; it != keys.second; ++it) {
						it->second->Call(&m_events);
					}
				}
			}

			void RegisterEvent(int _eventType, EventObject* _event) {
				m_eventMap.insert(std::pair<int, EventObject*>(_eventType, _event));
				return;
			}

			void UnregisterEvent(EventObject* _event) {
				for (std::multimap<int, EventObject*>::iterator it = m_eventMap.begin(); it != m_eventMap.end(); ++it) {
					if (it->second == _event) {
						//delete it->second;
						m_eventMap.erase(it);
					};
				}
				return;
			}

			~Events() {

			}
	};
}