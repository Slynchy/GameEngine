#include "InputManager.h"

void GameEngine::InputManager::UpdateMouse() {
	SDL_GetMouseState(&currMouseX, &currMouseY);
	mouseDeltaX = lastMouseX - currMouseX;
	mouseDeltaY = lastMouseY - currMouseY;
	lastMouseX = currMouseX;
	lastMouseY = currMouseY;
}

void GameEngine::InputManager::UpdateKeyboard() {
	SDL_KEYBOARDSTATE = SDL_GetKeyboardState(NULL);

	keys[bSPACE] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_SPACE];
	keys[bUP] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_W];
	keys[bLEFT] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_A];
	keys[bDOWN] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_S];
	keys[bRIGHT] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_D];
	keys[bESC] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_ESCAPE];
		 
	for (unsigned int i = 0; i < BUTTONS::NUM_OF_BUTTONS; i++) {
		if (keys[(BUTTONS)i]) {
			if (keyStates[(BUTTONS)i] == KeyStates::UP) {
				keyStates[(BUTTONS)i] = KeyStates::DOWN;
			}
			else if (keyStates[(BUTTONS)i] == KeyStates::DOWN) {
				keyStates[(BUTTONS)i] = KeyStates::STILLDOWN;
			}
		}
		else {
			keyStates[(BUTTONS)i] = KeyStates::UP;
		}
	}
}

uint8_t GameEngine::InputManager::KeyDown(BUTTONS _key)
{
	return keys[_key];
}

void GameEngine::InputManager::QueueUpdate(bool _bool)
{
	m_queueUpdate = _bool;
}

GameEngine::InputManager::KeyStates GameEngine::InputManager::KeyState(BUTTONS _key)
{
	return keyStates[_key];
}

void GameEngine::InputManager::Update()
{
	if (m_queueUpdate == false) return;
	else m_queueUpdate = false;

	UpdateMouse();
	UpdateKeyboard();
}