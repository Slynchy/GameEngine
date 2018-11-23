#pragma once

/* 
	This class was taken from my last engine which was used when submitting my AI Programming assignment
	in second year. As this wasn't the main focus of the assignment, it should be fine to use here...
*/

#include <SDL2/SDL.h>
#include <engine/Events.h>
#include <engine/EventObject.h>
#include <engine/Component.h>

namespace GameEngine
{
	/// Class for handling input from keyboard + mouse
	class InputManager
	{
	public:

		/// Enumerator of possible buttons to press
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
		/// The current state of the keyboard
		const Uint8* SDL_KEYBOARDSTATE;

		/// Boolean mapping of keys
		uint8_t keys[NUM_OF_BUTTONS - 1] = { false };

		/// If true, update keyboard state
		bool m_queueUpdate;

		// Mouse last + curr positions
		int lastMouseX = 0;
		int lastMouseY = 0;
		int currMouseX = 0;
		int currMouseY = 0;

		void UpdateMouse();
		void UpdateKeyboard();
	protected:
	public:

		// Mouse deltas; public because easier to access
		/// @bug Doesn't need to be public
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

		/// Check if key is down against enumerator
		/// @param[in] _key Enum value for which key to check.
		uint8_t KeyDown(BUTTONS _key);

		/// Queues or cancels an update to input
		/// @param[in] _bool If true, update input, else don't.
		void QueueUpdate(bool _bool);

		/// On-tick function; if queued to update, will update input
		void Update();
	};
}