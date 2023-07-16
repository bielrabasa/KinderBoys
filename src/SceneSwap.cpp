#include "SceneSwap.h"

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
#include "SceneLevel1.h"

SceneSwap::SceneSwap(bool startEnabled) : Module(startEnabled)
{
	rightAnim.Empty();
	rightAnim.PushBack({ 0, 16, 16, 16 });
	rightAnim.PushBack({ 16, 16, 16, 16 });
	rightAnim.PushBack({ 32, 16, 16, 16 });
	rightAnim.PushBack({ 48, 16, 16, 16 });
	rightAnim.PushBack({ 64, 16, 16, 16 });
	rightAnim.PushBack({ 80, 16, 16, 16 });
	rightAnim.PushBack({ 96, 16, 16, 16 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	currentAnimation = &rightAnim;

	topRightAnim.Empty();
	topRightAnim.PushBack({ 64, 48, 32, 32 });

	currentTopAnimation = &topRightAnim;
}

SceneSwap::~SceneSwap()
{

}

// Load assets
bool SceneSwap::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV.png");
	texture = App->textures->Load("Assets/SpritesSSTV/Entity_Player.png");
	portaTexture = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV_Portes.png");
	porta2Texture = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV_Portes2.png");

	Transicio = 0;

	App->player->Disable();
	App->collisions->Disable();
	App->particles->Disable();
	App->enemies->Disable();
	
	xplayer = 440;
	yplayer = 225;

	if (App->sceneLevel1->levelcont == 0) {
		mapaTransicio = 3;
		portaTransicio = 0;
	}

	if (App->sceneLevel1->levelcont == 1) {
		mapaTransicio = 0;
		portaTransicio = 0;
	}

	if (App->sceneLevel1->levelcont == 2) {
		mapaTransicio = 1;
		portaTransicio = 1;
	}

	return ret;
}

UpdateResult SceneSwap::Update()
{
	/*if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 0);
	}*/

	if (Transicio < 512)
		Transicio += 4;
	
	if(Transicio % 4 == 0 && Transicio != 512)
		xplayer -= 3;

	currentAnimation->Update();

	if(Transicio >= 512 && App->sceneLevel1->levelcont == 0)App->fade->FadeToBlack(this, (Module*)App->sceneLevel1, 10);
	if(Transicio >= 512 && App->sceneLevel1->levelcont == 1)App->fade->FadeToBlack(this, (Module*)App->sceneLevel1, 10);
	if(Transicio >= 512 && App->sceneLevel1->levelcont == 2)App->fade->FadeToBlack(this, (Module*)App->sceneLevel2, 10);
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneSwap::PostUpdate()
{
	// Draw everything
	SDL_Rect fons1 = { (512 * mapaTransicio) + Transicio, 0, 512, 448 }; //512*primerMapaActual, 0, 512, 448
	App->render->DrawTexture(bgTexture, 0, 0, &fons1);

	SDL_Rect rect2 = currentAnimation->GetCurrentFrame();	//Down personatge
	App->render->DrawTexture(texture, xplayer + 2, yplayer + 17, &rect2, 1.5f);

	SDL_Rect rectTop2 = currentTopAnimation->GetCurrentFrame();	//Top personatge
	App->render->DrawTexture(texture, xplayer - 10, yplayer - 7, &rectTop2, 1.5f);

	if (mapaTransicio == 3) {
		SDL_Rect porta2 = { Transicio, 0, 512, 448 }; //Rectangle Porta
		App->render->DrawTexture(porta2Texture, 0, 0, &porta2);
		
		SDL_Rect cameras = { (5 * 512) + Transicio, 0, 512, 448 }; //Rectangle Porta
		App->render->DrawTexture(bgTexture, 0, 0, &cameras);
	}
	else {
		SDL_Rect porta1 = { (512 * portaTransicio) + Transicio, 0, 512, 448 }; //Rectangle Porta
		App->render->DrawTexture(portaTexture, 0, 0, &porta1);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneSwap::CleanUp() {

	LOG("Freeing swap");

	//desinicialitzar tots els sprites
	App->textures->Unload(bgTexture);
	App->textures->Unload(texture);
	App->textures->Unload(portaTexture);

	return true;
}
