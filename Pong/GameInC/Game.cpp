#include "Game.h"

const int windowWidth = 1024;
const int windowHeight = 768;
const int frameLimit = 16;
const float paddleSpeed = 100.0f;

const float thickness = 15.0f;
const float paddleHeight = 100.0f;

Game::Game() 
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mTicksCount(0)
	, mPaddleDirection(0)
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

	// Initialize Positions
	// Player 1 initial position
	mPaddlePosition.x = 10.0f;
	mPaddlePosition.y = windowHeight / 2.0f;
	// Player 2 initial position
	mPaddlePosition2.x = windowWidth - 10.0f;
	mPaddlePosition2.y = windowHeight / 2.0f;
	// Ball initial position and velocity
	mBallPosition.x = windowWidth / 2.0f;
	mBallPosition.y = windowHeight / 2.0f;
	mBallVelocity.x = -20.0f;
	mBallVelocity.y = 23.0f;

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
	// Player 1 controls
	mPaddleDirection = 0.0f;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDirection -= 1.0f;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDirection += 1.0f;
	}
	// Player 2 controls
	mPaddleDirection2 = 0.0f;
	if(state[SDL_SCANCODE_I])
	{
		mPaddleDirection2 -= 1.0f;
	}
	if(state[SDL_SCANCODE_K])
	{
		mPaddleDirection2 += 1.0f;
	}
}

void Game::UpdateGame()
{
	while(SDL_GetTicks() < mTicksCount + frameLimit)
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
	// Updates the player 1 paddle position
	if(mPaddleDirection != 0.0f)
	{
		mPaddlePosition.y += mPaddleDirection * paddleSpeed * deltaTime;

		// Make sure the paddle doesn't move off the screen!
		if (mPaddlePosition.y < (paddleHeight / 2.0f + thickness))
		{
			mPaddlePosition.y = paddleHeight / 2.0f + thickness;
		}
		else if (mPaddlePosition.y > (windowHeight - paddleHeight / 2.0f - thickness))
		{
			mPaddlePosition.y = windowHeight - paddleHeight / 2.0f - thickness;
		}
	}
	// Updates the player 2 paddle position
	if (mPaddleDirection2 != 0.0f)
	{
		mPaddlePosition2.y += mPaddleDirection2 * paddleSpeed * deltaTime;
		if (mPaddlePosition2.y < (paddleHeight / 2.0f + thickness))
		{
			mPaddlePosition2.y = paddleHeight / 2.0f + thickness;
		}
		else if (mPaddlePosition2.y > (windowHeight - paddleHeight / 2.0 - thickness))
		{
			mPaddlePosition2.y = windowHeight - paddleHeight / 2.0 - thickness;
		}
	}

	// Updates the ball Position
	mBallPosition.x += mBallVelocity.x * deltaTime;
	mBallPosition.y += mBallVelocity.y * deltaTime;
	// Find the difference in y values
	// Negates the bounce on the top wall
	if (mBallPosition.y <= thickness && mBallVelocity.y < 0.0f)
	{
		mBallVelocity.y *= -1;
	}
	// Negates the bounce on the bottom wall
	else if (mBallPosition.y >= windowHeight - thickness && mBallVelocity.y > 0.0f)
	{
		mBallVelocity.y *= -1;
	}

	// checks if it hits the player 1's paddle
	float diff = mBallPosition.y - mPaddlePosition.y;
	// absolute value
	if (diff < 0.0f)
	{
		diff = -diff;
	}
	if (
			diff <= paddleHeight / 2.0f
			&& mBallPosition.x >= 20.0f 
			&& mBallPosition.x <= 25.0f
			&& mBallVelocity.x < 0.0f
		)
	{
		mBallVelocity.x *= -1.0f;
	}
	// check if it hits player 2's paddle
	diff = mBallPosition.y - mPaddlePosition2.y;
	// absolute value
	if (diff < 0.0f)
	{
		diff = -diff;
	}
	if (
			diff <= paddleHeight / 2.0f
			&& mBallPosition.x >= windowWidth - 25.0f 
			&& mBallPosition.x <= windowWidth - 20.0f
			&& mBallVelocity.x > 0.0f
		)
	{
		mBallVelocity.x *= -1.0f;
	}

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

	// Renders the walls
	SDL_FRect wall{
	0.0f,		// Top left x
	0.0f,		// Top left y
	1024.0f,	// Width
	thickness	// Height
	};

	// Black Color
	SDL_SetRenderDrawColor(mRenderer,
		0,		// R
		0,		// G
		0,		// B
		255		// A
	);
	
	// top wall
	SDL_RenderFillRect(mRenderer, &wall);
	
	// bottom wall
	wall.y = 768.0f - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Render paddles
	wall.w = thickness;
	wall.h = paddleHeight;

	// Player 1 paddle
	wall.x = mPaddlePosition.x - thickness / 2.0f;
	wall.y = mPaddlePosition.y - paddleHeight / 2.0f;

	SDL_RenderFillRect(mRenderer, &wall);

	// Player 2 paddle
	wall.x = mPaddlePosition2.x - thickness / 2.0f;
	wall.y = mPaddlePosition2.y - paddleHeight / 2.0f;

	SDL_RenderFillRect(mRenderer, &wall);
	    
	// Render ball
	SDL_FRect ball
	{
		mBallPosition.x - thickness / 2.0f,
		mBallPosition.y - thickness / 2.0f,
		thickness,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &ball);

	// Final Load
	SDL_RenderPresent(mRenderer);
}
