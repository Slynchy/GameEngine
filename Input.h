#pragma once

#include <engine/Component.h>

#include <SDL2/SDL_events.h>
#include <engine/Events.h>
#include <engine/Entity.h>
#include <engine/EventObject.h>

namespace GameEngine {

	class Input : public GameEngine::Component {
		private:
			//EventObject<Entity*>* _eventObj;
		protected:
		public:
			Input(Events* _event);

			~Input() {

			}
	};

}