#include "ModuleInput.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"

ModuleInput::ModuleInput(bool startEnabled) : Module(startEnabled)
{}

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

	return ret;
}

UpdateResult ModuleInput::PreUpdate()
{
	// Read new SDL events, mostly from the window
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || keys[SDL_SCANCODE_ESCAPE] == KeyState::KEY_REPEAT)	return UpdateResult::UPDATE_STOP;
	}

	// Read all keyboard data and update our custom array
	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i]) keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	if (App->input->keys[SDL_SCANCODE_P] == KeyState::KEY_DOWN) {
		App->pause = !App->pause;
		
	}

	if (App->pause)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_REPEAT)
		{
			App->pause = !App->pause;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 20);
		}

		if (App->input->keys[SDL_SCANCODE_BACKSPACE] == KeyState::KEY_REPEAT)
		{
			App->pause = !App->pause;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 20);
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

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}