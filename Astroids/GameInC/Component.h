#pragma once
#include "Actor.h"

class Component
{
public:
	// Constructor
	// The lower the update order
	// the earlier the component is updated
	Component(class Actor* owner);
	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	// Owning actor
	class Actor* mOwner;
	// Update order of component
	int mUpdateOrder;
};