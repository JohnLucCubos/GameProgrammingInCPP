#pragma once
#include"SDL3/SDL.h"

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
private:
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

};