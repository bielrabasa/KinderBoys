#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__

#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL_scancode.h"

#define MAX_KEYS 256
#define MAX_PADS 4

struct _SDL_GameController;
struct _SDL_Haptic;

enum KeyState
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GamePad
{
	// Input data
	bool start, back, guide;
	bool x, y, a, b, l1, r1, l3, r3;
	bool up, down, left, right;
	float l2, r2;
	float left_x, left_y, right_x, right_y, left_dz, right_dz;

	// Controller data
	bool enabled;
	int index;
	_SDL_GameController* controller;
	_SDL_Haptic* haptic;

	// Rumble controller
	int rumble_countdown;
	float rumble_strength;
};

class ModuleInput : public Module
{
public:
	// Constructor
	ModuleInput(bool startEnabled);

	// Destructor
	~ModuleInput();

	// Called on application start.
	// Initializes the SDL system for input detection
	bool Init() override;

	// Called at the beginning of the application loop
	// Updates all input data received from SDL
	UpdateResult PreUpdate() override;

	// Called on application exit.
	// Uninitializes the SDL system for input detection
	bool CleanUp() override;

	// Activates SDL device funcionallity when a gamepad has been connected
	void HandleDeviceConnection(int index);

	// Deactivates SDL device funcionallity when a gamepad has been disconnected
	void HandleDeviceRemoval(int index);

	// Called at PreUpdate
	// Iterates through all active gamepads and update all input data
	void UpdateGamepadsInput();

	bool ShakeController(int id, int duration, float strength = 0.5f);
	const char* GetControllerName(int id) const;

public:
	// An array to fill in the state of all the keyboard keys
	KeyState keys[MAX_KEYS] = { KEY_IDLE };

	// An array to fill in all detected gamepads
	GamePad pads[MAX_PADS];
};

#endif // __ModuleInput_H__