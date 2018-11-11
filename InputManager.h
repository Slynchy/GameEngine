#pragma once

#include <SDL2/SDL.h>
#include <engine/Events.h>
#include <engine/EventObject.h>
#include <engine/Component.h>

namespace GameEngine
{
	class InputManager
	{
	public:
		enum BUTTONS
		{
			UP,
			DOWN,
			LEFT,
			RIGHT,
			SPACE,
			ESC,
			NUM_OF_BUTTONS
		};
	private:
		const Uint8* SDL_KEYBOARDSTATE;
		uint8_t keys[NUM_OF_BUTTONS - 1] = { false };

		bool m_queueUpdate;

		int lastMouseX = 0;
		int lastMouseY = 0;
		int currMouseX = 0;
		int currMouseY = 0;
	protected:
	public:

		int mouseDeltaX = 0;
		int mouseDeltaY = 0;

		InputManager()
		{
			m_queueUpdate = false;
			SDL_KEYBOARDSTATE = NULL;
		}
		~InputManager()
		{
			m_queueUpdate = false;
			SDL_KEYBOARDSTATE = NULL;
		}

		uint8_t KeyDown(BUTTONS _key)
		{
			return keys[_key];
		}

		void QueueUpdate(bool _bool)
		{
			m_queueUpdate = _bool;
		}

		void Update()
		{
			if (m_queueUpdate == false) return;
			else m_queueUpdate = false;

			SDL_GetMouseState(&currMouseX, &currMouseY);
			mouseDeltaX = lastMouseX - currMouseX;
			mouseDeltaY = lastMouseY - currMouseY;
			lastMouseX = currMouseX;
			lastMouseY = currMouseY;

			SDL_KEYBOARDSTATE = SDL_GetKeyboardState(NULL);

			if (SDL_KEYBOARDSTATE[SDL_SCANCODE_SPACE])
			{
				keys[SPACE] = true;
			}
			else
			{
				keys[SPACE] = false;
			}

			if (SDL_KEYBOARDSTATE[SDL_SCANCODE_W])
			{
				keys[UP] = true;
			}
			else
			{
				keys[UP] = false;
			}

			if (SDL_KEYBOARDSTATE[SDL_SCANCODE_A])
			{
				keys[LEFT] = true;
			}
			else
			{
				keys[LEFT] = false;
			}

			if (SDL_KEYBOARDSTATE[SDL_SCANCODE_ESCAPE])
			{
				keys[ESC] = true;
			}
			else
			{
				keys[ESC] = false;
			}

			if (SDL_KEYBOARDSTATE[SDL_SCANCODE_S])
			{
				keys[DOWN] = true;
			}
			else
			{
				keys[DOWN] = false;
			}

			if (SDL_KEYBOARDSTATE[SDL_SCANCODE_D])
			{
				keys[RIGHT] = true;
			}
			else
			{
				keys[RIGHT] = false;
			}
		}
	};
}