#include "Game.h"

const int windowWidth = 1024;
const int windowHeight = 768;
const int frameLimit = 16;

Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mTicksCount(0)
{
}

Game::~Game() {

}

bool Game::Initialize() {
	bool sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (!sdlResult)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)",
		windowWidth,
		windowHeight,
		0
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}


	mRenderer = SDL_CreateRenderer(
		mWindow,
		nullptr
	);
	SDL_SetRenderVSync(mRenderer, 1);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// Initialize variables related to the game loop here

	return true;
}

void Game::RunLoop() {
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	SDL_Quit();
}

void Game::ProcessInput() {
	SDL_Event event;
	// While there area stilll events in the queue
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// Handle different event types here
		case SDL_EVENT_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const bool* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	// TODO: Handle player input here
}

void Game::UpdateGame()
{
	while (SDL_GetTicks() < mTicksCount + frameLimit)
	{
		// Wait for the next frame
	}

	// Delta time is the difference in ticks from last frame
	// converted to seconds
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// Update tick counts for next frame
	//mTicksCount = SDL_GetTicks();
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	// TODO: Update game objects in the game world as a function of delta time

}

void Game::GenerateOutput()
{
	// Renders the background
	// White Color
	SDL_SetRenderDrawColor(mRenderer,
		255,	// R
		255,	// G
		255,	// B
		255		// A
	);
	SDL_RenderClear(mRenderer);


	// Final Load
	SDL_RenderPresent(mRenderer);
}
