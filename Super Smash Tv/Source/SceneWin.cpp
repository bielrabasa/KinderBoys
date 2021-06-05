#include "SceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleBOSS.h"

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled)
{

}

SceneWin::~SceneWin()
{

}

// Load assets
bool SceneWin::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/Score_screen_2.png");
	fontTexture = App->textures->Load("Assets/SpritesSSTV/Font.png");
	//App->audio->PlayMusic("Assets/Audio/SFX/End point count.wav", 1.0f);
	App->audio->PlayMusic("Assets/Music/06-_Super_Smash_TV_-_Win_Game.ogg", 1.0f);
	Win = App->audio->LoadFx("Assets/Audio/SFX/End point count 2.wav");

	
	App->audio->PlayFx(Win);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	App->player->CleanUp();
	App->collisions->CleanUp();
	App->particles->CleanUp();

	App->enemies->Disable();
	App->boss->Disable();

	diners = 0;

	return ret;
}

UpdateResult SceneWin::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN || pad.a == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 20);
	}

	//Suma diners
	if (diners < App->player->money && diners + 300 < App->player->money)
		diners += 300; //velocitat de pujada de diners, 3 està bé
	else if (diners < App->player->money)
		diners++;

	//Gestió Array de la font
	dinerscopia = diners;

	for (int i = 0; i < 7; ++i) {
		arrdiners[i] = dinerscopia % 10;
		dinerscopia /= 10;
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneWin::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);

	//Render Font
	SDL_Rect rect0 = { 234, 64, 25, 42 };
	SDL_Rect rect1 = { 0, 64, 25, 42 };
	SDL_Rect rect2 = { 26, 64, 25, 42 };
	SDL_Rect rect3 = { 52, 64, 25, 42 };
	SDL_Rect rect4 = { 78, 64, 25, 42 };
	SDL_Rect rect5 = { 104, 64, 25, 42 };
	SDL_Rect rect6 = { 130, 64, 25, 42 };
	SDL_Rect rect7 = { 156, 64, 25, 42 };
	SDL_Rect rect8 = { 182, 64, 25, 42 };
	SDL_Rect rect9 = { 208, 64, 25, 42 };


	for (int i = 0; i < 7; ++i) {

		switch (arrdiners[i]) {
		case 0:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect0, 0.5f);
			break;
		case 1:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect1, 0.5f);
			break;
		case 2:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect2, 0.5f);
			break;
		case 3:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect3, 0.5f);
			break;
		case 4:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect4, 0.5f);
			break;
		case 5:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect5, 0.5f);
			break;
		case 6:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect6, 0.5f);
			break;
		case 7:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect7, 0.5f);
			break;
		case 8:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect8, 0.5f);
			break;
		case 9:
			App->render->DrawTexture(fontTexture, posicioFont, 100, &rect9, 0.5f);
			break;
		}

		posicioFont -= 14; //Separació entre nombres
	}
	posicioFont = 200; //Posició del primer element de la dreta

	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneWin::CleanUp() {

	LOG("Freeing swap");

	//desinicialitzar tots els sprites
	App->textures->Unload(bgTexture);

	return true;
}