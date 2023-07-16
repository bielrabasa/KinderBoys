#include "Application.h"
#include "Globals.h"
#include "SDL.h"

enum class MainState
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char* argv[])
{
	int main_result = EXIT_FAILURE;
	MainState state = MainState::MAIN_CREATION;

	while (state != MainState::MAIN_EXIT)
	{
		switch (state)
		{
			case MainState::MAIN_CREATION:
			{
				App = new Application();
				state = MainState::MAIN_START;
			}	break;

			case MainState::MAIN_START:
			{
				state = App->Init() ? MainState::MAIN_UPDATE : MainState::MAIN_EXIT;
			}	break;

			case MainState::MAIN_UPDATE:
			{
				UpdateResult status = App->Update();
				switch(status)
				{
					case UpdateResult::UPDATE_CONTINUE:
						continue;
					case UpdateResult::UPDATE_ERROR:
						state = MainState::MAIN_EXIT;
						break;
					case UpdateResult::UPDATE_STOP:
						state = MainState::MAIN_FINISH;
					default: break;
				}
			}	break;

			case MainState::MAIN_FINISH:
			{
				if (App->CleanUp() == true) main_result = EXIT_SUCCESS;
				state = MainState::MAIN_EXIT;
			}
			default: break;
		}
	}

	delete App;

	return main_result;
}
