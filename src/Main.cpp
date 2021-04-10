#include "Core/Game.hpp"

int main(int argc, char** argv)
{
	Game game;

	if (game.Initialize())
	{
		game.Run();
	}

	game.Shutdown();
}
