#include "Game.h"
#include <SFML\Audio.hpp>
//https://github.com/SFML/SFML/wiki/Projects#open-source
//http://en.sfml-dev.org/forums/index.php?topic=20245.0


int main()
{
	Game game;
	while (game.isRunning())
	{
		game.update();
		game.render();
		game.lateUpdate();
	}

	return 0;


}