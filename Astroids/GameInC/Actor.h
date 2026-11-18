#pragma once
#include "Game.h"
#include "Component.h"

class Actor
{
public:
	// Used to track state of the actor
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	// Constructor/Destructor
	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from the game
	// Not Overidable
	void Update(float deltaTime);
	// Update all components attached to the actor
	// Not Overridable
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code
	// Overridable
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	// ...
	State GetState() const { return mState; }
	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// Actor's state
	State mState;
	// Transform
	Vector2 mPosition;	// Center position of actor
	float mScale;		// Uniform scale of actor (1.0f for 100% size)
	float mRotation;	// Rotation angle in radians
	// Components held by the actor
	std::vector<class Component*> mComponents;
	class Game* mGame; // Owning game
};