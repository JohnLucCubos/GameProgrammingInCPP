#include "Game.h"
#include <algorithm>

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
	// CHAPTER 3: Game Objects
	
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
	// CHAPTER 3: Game Objects
	// Update all actors
	mUpdatingActors = true;
	for(auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;
	// Move any pending actors to mActors
	for(auto pending: mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();
	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for(auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
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

void Game::AddActor(Actor* actor) {
	// if updating actors, need to add to pendingActors
	if(mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor) {
	// Check if actor is in pending actors
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erasing copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	// Check if actor is in actors
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erasing copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::Shutdown() {
	while(!mActors.empty())
	{
		delete mActors.back();
	}

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	SDL_Quit();
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
	//auto iter = mTextures.find(fileName);
	//if (iter != mTextures.end()) {
	//	return iter->second;
	//}

	//SDL_Texture* tex = IMG_LoadTexture(mRenderer, fileName.c_str());
	//if (!tex) {
	//	SDL_Log("Failed to load texture %s: %s", fileName.c_str(), SDL_GetError());
	//	return nullptr;
	//}

	//mTextures.emplace(fileName, tex);
	//return tex;
}