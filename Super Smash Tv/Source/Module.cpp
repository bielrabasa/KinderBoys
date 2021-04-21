#include "Module.h"

Module::Module(bool startEnabled) : isEnabled(startEnabled)
{

}

bool Module::Init()
{
	return true;
}

bool Module::Start()
{
	return true;
}

UpdateResult Module::PreUpdate()
{
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Module::Update()
{
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Module::PostUpdate()
{
	return UpdateResult::UPDATE_CONTINUE;
}

bool Module::CleanUp()
{
	return true;
}

void Module::OnCollision(Collider* c1, Collider* c2)
{

}

void Module::Enable()
{
	if (!isEnabled)
	{
		isEnabled = true;
		Start();
	}
}

void Module::Disable()
{
	// L10: TODO 0: Call CleanUp() when disabling a module
	if (isEnabled) {
		isEnabled = false;
		CleanUp();
	}
}
