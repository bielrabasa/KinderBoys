#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"

ModuleRender::ModuleRender(bool startEnabled) : Module(startEnabled)
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;	
	Uint32 flags = 0;

	if (VSYNC == true) flags |= SDL_RENDERER_PRESENTVSYNC;


	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
UpdateResult ModuleRender::PreUpdate()
{
	// Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Clear rendering target
	SDL_RenderClear(renderer);

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleRender::Update()
{
	/*// Handle positive vertical movement
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT) camera.y -= cameraSpeed;

	// Handle negative vertical movement
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) camera.y += cameraSpeed;

	// L4: DONE 1: Handle horizontal movement of the camera
	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) camera.x -= cameraSpeed;
	if (camera.x < 0) camera.x = 0;

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) camera.x += cameraSpeed;*/

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleRender::PostUpdate()
{
	// Update the screen
	SDL_RenderPresent(renderer);

	return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	// Destroy the rendering context
	if (renderer != nullptr) SDL_DestroyRenderer(renderer);

	return true;
}

// Draw to screen
bool ModuleRender::DrawTexture(SDL_Texture* texture, int x, int y, SDL_Rect* section, float scale)
{
	bool ret = true;

	//fullscreen pantalla centrada
	if (WIN_FULLSCREEN_DESKTOP == 1) {
		SDL_Rect rect = {
			(int)(-camera.x + 500) + x * SCREEN_SIZE,
			(int)(-camera.y + 100) + y * SCREEN_SIZE,
			0, 0
		};
	

	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= (scale*SCREEN_SIZE);
	rect.h *= (scale*SCREEN_SIZE);

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
	}
	else if (WIN_FULLSCREEN_DESKTOP == 0)//no fullscreen
	{
		SDL_Rect rect = {
	(int)(-camera.x) + x * SCREEN_SIZE,
	(int)(-camera.y) + y * SCREEN_SIZE,
	0, 0
		};


		if (section != nullptr)
		{
			rect.w = section->w;
			rect.h = section->h;
		}
		else
		{
			// Collect the texture size into rect.w and rect.h variables
			SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
		}

		rect.w *= (scale * SCREEN_SIZE);
		rect.h *= (scale * SCREEN_SIZE);

		if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}

		return ret;
	}
}

bool ModuleRender::DrawRectangle(const SDL_Rect& rect, SDL_Color color, float speed)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect dstRect {
		(int)(-camera.x * speed) + rect.x * SCREEN_SIZE + 500,
		(int)(-camera.y * speed) + rect.y * SCREEN_SIZE + 100,
		rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}