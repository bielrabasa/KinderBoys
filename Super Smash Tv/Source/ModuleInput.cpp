#include "ModuleInput.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "level2.h"
#include "ModuleBOSS.h"

#include "SDL/include/SDL.h"

#include <string.h>

ModuleInput::ModuleInput(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_KEYS; ++i) keys[i] = KEY_IDLE;

	memset(&pads[0], 0, sizeof(GamePad) * MAX_PADS);
}

ModuleInput::~ModuleInput()
{}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_INIT_GAMECONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_InitSubSystem(SDL_INIT_HAPTIC) < 0)
	{
		LOG("SDL_INIT_HAPTIC could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

UpdateResult ModuleInput::PreUpdate()
{
	// Read new SDL events, mostly from the window
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || keys[SDL_SCANCODE_ESCAPE] == KeyState::KEY_REPEAT || App->input->pads->l1)	return UpdateResult::UPDATE_STOP;
	}

	// Read all keyboard data and update our custom array
	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KeyState::KEY_IDLE) ? KeyState::KEY_DOWN : KeyState::KEY_REPEAT;
		else
			keys[i] = (keys[i] == KeyState::KEY_REPEAT || keys[i] == KeyState::KEY_DOWN) ? KeyState::KEY_UP : KeyState::KEY_IDLE;
	}
	if (pads->left_x < 0.0f) {
		keys[SDL_SCANCODE_A] = KeyState::KEY_REPEAT;
	}
	if (pads->left_x > 0.0f) {
		keys[SDL_SCANCODE_D] = KeyState::KEY_REPEAT;
	}
	if (pads->left_y < 0.0f) {
		keys[SDL_SCANCODE_W] = KeyState::KEY_REPEAT;
	}
	if (pads->left_y > 0.0f) {
		keys[SDL_SCANCODE_S] = KeyState::KEY_REPEAT;
	}
	if (pads->x) {
		keys[SDL_SCANCODE_LEFT] = KeyState::KEY_REPEAT;
	}
	if (pads->a) {
		keys[SDL_SCANCODE_DOWN] = KeyState::KEY_REPEAT;
	}
	if (pads->b) {
		keys[SDL_SCANCODE_RIGHT] = KeyState::KEY_REPEAT;
	}
	if (pads->y) {
		keys[SDL_SCANCODE_UP] = KeyState::KEY_REPEAT;
	}
	if (pads->left) {
		keys[SDL_SCANCODE_A] = KeyState::KEY_REPEAT;
	}
	if (pads->down) {
		keys[SDL_SCANCODE_S] = KeyState::KEY_REPEAT;
	}
	if (pads->right) {
		keys[SDL_SCANCODE_D] = KeyState::KEY_REPEAT;
	}
	if (pads->up) {
		keys[SDL_SCANCODE_W] = KeyState::KEY_REPEAT;
	}
	// Read new SDL events

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case(SDL_CONTROLLERDEVICEADDED):
		{
			HandleDeviceConnection(event.cdevice.which);
			break;
		}
		case(SDL_CONTROLLERDEVICEREMOVED):
		{
			HandleDeviceRemoval(event.cdevice.which);
			break;
		}
		case(SDL_QUIT):
		{
			return UpdateResult::UPDATE_STOP;
			break;
		}
		}
	}

	UpdateGamepadsInput();

	if (App->input->keys[SDL_SCANCODE_P] == KeyState::KEY_DOWN) {
		App->pause = !App->pause;
		
	}

	if (App->pause)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_REPEAT || App->input->pads->a == KeyState::KEY_DOWN)
		{
			App->pause = !App->pause;
			if(App->sceneLevel_1->lvl1 = true)
			{
				App->sceneLevel_1->levelcont = 0;
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneSwap, 20);
			}
			if(App->sceneLevel2->lvl2 = true)
			{
				App->boss->Disable();
				App->sceneLevel_1->levelcont = 0;
				App->fade->FadeToBlack((Module*)App->sceneLevel2, (Module*)App->sceneSwap, 20);
				App->sceneLevel2->Disable();

			}
			App->player->vides = 5;
			App->player->score = 0;
		}

		if (App->input->keys[SDL_SCANCODE_BACKSPACE] == KeyState::KEY_REPEAT)
		{
			App->pause = !App->pause;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 20 || App->input->pads->a == KeyState::KEY_DOWN);
			App->player->vides = 5;
			App->player->score = 0;
		}
		
		if (App->input->keys[SDL_SCANCODE_RETURN] == KeyState::KEY_REPEAT)
		{
			return UpdateResult::UPDATE_STOP;
		}
	}
	return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");

	// Stop rumble from all gamepads and deactivate SDL functionallity
	for (uint i = 0; i < MAX_PADS; ++i)
	{
		if (pads[i].haptic != nullptr)
		{
			SDL_HapticStopAll(pads[i].haptic);
			SDL_HapticClose(pads[i].haptic);
		}
		if (pads[i].controller != nullptr) SDL_GameControllerClose(pads[i].controller);
	}

	SDL_QuitSubSystem(SDL_INIT_HAPTIC);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

void ModuleInput::HandleDeviceConnection(int index)
{
	if (SDL_IsGameController(index))
	{
		for (int i = 0; i < MAX_PADS; ++i)
		{
			GamePad& pad = pads[i];

			if (pad.enabled == false)
			{
				if (pad.controller = SDL_GameControllerOpen(index))
				{
					LOG("Found a gamepad with id %i named %s", i, SDL_GameControllerName(pad.controller));
					pad.enabled = true;
					pad.left_dz = pad.right_dz = 0.1f;
					pad.haptic = SDL_HapticOpen(index);
					if (pad.haptic != nullptr) LOG("... gamepad has force feedback capabilities");
					pad.index = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pad.controller));
				}
			}
		}
	}
}

void ModuleInput::HandleDeviceRemoval(int index)
{
	// If an existing gamepad has the given index, deactivate all SDL device functionallity
	for (int i = 0; i < MAX_PADS; ++i)
	{
		GamePad& pad = pads[i];
		if (pad.enabled && pad.index == index)
		{
			SDL_HapticClose(pad.haptic);
			SDL_GameControllerClose(pad.controller);
			memset(&pad, 0, sizeof(GamePad));
		}
	}
}

void ModuleInput::UpdateGamepadsInput()
{
	// Iterate through all active gamepads and update all input data
	for (int i = 0; i < MAX_PADS; ++i)
	{
		GamePad& pad = pads[i];

		if (pad.enabled == true)
		{
			pad.a = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_A) == 1;
			pad.b = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_B) == 1;
			pad.x = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_X) == 1;
			pad.y = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_Y) == 1;
			pad.l1 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1;
			pad.r1 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == 1;
			pad.l3 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_LEFTSTICK) == 1;
			pad.r3 = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK) == 1;
			pad.up = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1;
			pad.down = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1;
			pad.left = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1;
			pad.right = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1;

			pad.start = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_START) == 1;
			pad.guide = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_GUIDE) == 1;
			pad.back = SDL_GameControllerGetButton(pad.controller, SDL_CONTROLLER_BUTTON_BACK) == 1;

			pad.l2 = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT)) / 32767.0f;
			pad.r2 = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)) / 32767.0f;

			pad.left_x = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_LEFTX)) / 32767.0f;
			pad.left_y = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_LEFTY)) / 32767.0f;
			pad.right_x = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_RIGHTX)) / 32767.0f;
			pad.right_y = float(SDL_GameControllerGetAxis(pad.controller, SDL_CONTROLLER_AXIS_RIGHTY)) / 32767.0f;

			// Apply deadzone. All values below the deadzone will be discarded
			pad.left_x = (fabsf(pad.left_x) > pad.left_dz) ? pad.left_x : 0.0f;
			pad.left_y = (fabsf(pad.left_y) > pad.left_dz) ? pad.left_y : 0.0f;
			pad.right_x = (fabsf(pad.right_x) > pad.right_dz) ? pad.right_x : 0.0f;
			pad.right_y = (fabsf(pad.right_y) > pad.right_dz) ? pad.right_y : 0.0f;

			if (pad.rumble_countdown > 0)
				pad.rumble_countdown--;
		}
	}
}

bool ModuleInput::ShakeController(int id, int duration, float strength)
{
	bool ret = false;

	// Check if the given id is valid within the array bounds
	if (id < 0 || id >= MAX_PADS) return ret;

	// Check if the gamepad is active and allows rumble
	GamePad& pad = pads[id];
	if (!pad.enabled || pad.haptic == nullptr || SDL_HapticRumbleSupported(pad.haptic) != SDL_TRUE) return ret;

	// If the pad is already in rumble state and the new strength is below the current value, ignore this call
	if (duration < pad.rumble_countdown && strength < pad.rumble_strength)
		return ret;

	if (SDL_HapticRumbleInit(pad.haptic) == -1)
	{
		LOG("Cannot init rumble for controller number %d", id);
	}
	else
	{
		SDL_HapticRumbleStop(pad.haptic);
		SDL_HapticRumblePlay(pad.haptic, strength, duration / 60 * 1000); //Conversion from frames to ms at 60FPS

		pad.rumble_countdown = duration;
		pad.rumble_strength = strength;

		ret = true;
	}

	return ret;
}

const char* ModuleInput::GetControllerName(int id) const
{
	// Check if the given id has a valid controller
	if (id >= 0 && id < MAX_PADS && pads[id].enabled == true && pads[id].controller != nullptr)
		return SDL_GameControllerName(pads[id].controller);

	return "unplugged";
}