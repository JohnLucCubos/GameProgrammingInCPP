#pragma once
#include"SDL3/SDL.h"

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
	// Vector 2 used to store positions
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
	// Player 1 variables
	float mPaddleDirection;
	Vector2 mPaddlePosition;
	// Player 2 variables
	float mPaddleDirection2;
	Vector2 mPaddlePosition2;
	// Ball variables
	Vector2 mBallPosition;
	Vector2 mBallVelocity;
};