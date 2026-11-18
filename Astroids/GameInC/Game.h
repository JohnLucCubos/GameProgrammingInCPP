#pragma once
#include"SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include"Actor.h"
#include<string>
#include <vector>
// CHAPTER 2: Game Loop
// Vector 2 used to store positions
struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	~Game();
	// Initialize the game
	bool Initialize();
	// Run the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
	// CHAPTER 3: Game Objects
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	SDL_Texture* GetTexture(const std::string& fileName);
private:
	// CHAPTER 2: Game Loop
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer used to draw on the window
	bool mIsRunning;
	// Renderer used to draw on the window
	SDL_Renderer* mRenderer;
	// Time management
	Uint32 mTicksCount;
	// CHAPTER 3: Game Objects
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	bool mUpdatingActors;
};