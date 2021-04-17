#include "Game/MyGame.hpp"

int main(int argc, char** argv)
{
	MyGame game;

	if (game.Initialize())
	{
		game.Run();
	}

	game.Shutdown();
}
