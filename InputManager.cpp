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

	keys[SPACE] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_SPACE];
	keys[UP] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_W];
	keys[LEFT] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_A];
	keys[DOWN] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_S];
	keys[RIGHT] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_D];
	keys[ESC] = (bool)SDL_KEYBOARDSTATE[SDL_SCANCODE_ESCAPE];
}

uint8_t GameEngine::InputManager::KeyDown(BUTTONS _key)
{
	return keys[_key];
}

void GameEngine::InputManager::QueueUpdate(bool _bool)
{
	m_queueUpdate = _bool;
}

void GameEngine::InputManager::Update()
{
	if (m_queueUpdate == false) return;
	else m_queueUpdate = false;

	UpdateMouse();
	UpdateKeyboard();
}