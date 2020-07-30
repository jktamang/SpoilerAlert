#include "game.h"

int main(int argc, char* args[])
{
	Game game = Game();
	if (game.Init())
	{
		while (!game.ProcessInput())
		{
			game.StartFrame();
			game.Update();
			game.Render();
		}
	}
	game.Close();
	return 0;
}