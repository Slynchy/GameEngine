
#include "Engine.h"

GameEngine::Engine::~Engine() {
	delete m_graphics;
	delete m_events;
	delete m_sceneManager;
	delete m_inputManager;
	delete m_resourceManager;
	delete m_audio;
}

void GameEngine::Engine::Render() {
	m_graphics->PreRender();
	m_sceneManager->Render();
	m_graphics->PostRender();
}

void GameEngine::Engine::Update(float delta) {
	m_events->Update();
	//m_inputManager->Update();
	//m_graphics->PreRender();

	m_sceneManager->Update(delta);
	//m_graphics->SetMatrix(&(*testEntity), dynamic_cast<Mesh*>(testEntity->GetComponent("Mesh").get())->GetModel());
	//testEntity->Update();

	//m_graphics->PostRender();
}

int GameEngine::Engine::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return GameEngine::Engine::ErrorCodes::SDL_FAILED_TO_INIT;
	}

	m_events = new GameEngine::Events();

	m_inputManager = new GameEngine::InputManager();

	m_resourceManager = new GameEngine::ResourceManager();

	m_audio = new GameEngine::Audio();

	m_graphics = new GameEngine::Graphics();
	int graphicsErrorCode;
	if ((graphicsErrorCode = m_graphics->Init()) < 0) {
		return graphicsErrorCode;
	}
	else {
		if (SDL_CaptureMouse(SDL_TRUE) != 0) {
			printf("SDL_CaptureMouse failed: %s\n", SDL_GetError());
		};
		if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0) {
			printf("SDL_SetRelativeMouseMode failed: %s\n", SDL_GetError());
		}
	}

	m_sceneManager = new GameEngine::SceneManager(m_graphics);

	return 0;
}