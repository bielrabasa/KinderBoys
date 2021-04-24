#ifndef __MODULECOLLISIONS_H__
#define __MODULECOLLISIONS_H__

#define MAX_COLLIDERS 50

#include "Module.h"
#include "Collider.h"

class ModuleCollisions : public Module
{
public:
	// Constructor
	// Fills all collision matrix data
	ModuleCollisions(bool startEnabled);

	// Destructor
	~ModuleCollisions();

	// Called at the beginning of the application loop
	// Removes all colliders pending to delete
	// Checks for new collisions and calls its listeners
	UpdateResult PreUpdate();

	// Called at the middle of the application loop
	// Switches the debug mode on/off
	UpdateResult Update();

	// Called at the end of the application loop
	// Draw all colliders (if debug mode is enabled)
	UpdateResult PostUpdate();

	// Removes all existing colliders
	bool CleanUp();


	// Adds a new collider to the list
	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr);

	// Draws all existing colliders with some transparency
	void DebugDraw();

	//GodMode
	bool bandera_GodMode = false;
	

private:
	// All existing colliders in the scene
	Collider* colliders[MAX_COLLIDERS] = { nullptr };

	// The collision matrix. Defines the interaction for two collider types
	// If set two false, collider 1 will ignore collider 2
	bool matrix[Collider::Type::MAX][Collider::Type::MAX];

	// Simple debugging flag to draw all colliders
	bool debug = false;

};

#endif // __MODULECOLLISIONS_H__