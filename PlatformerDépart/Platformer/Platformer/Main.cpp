#include <vld.h>
#include "Game.h"

int main()
{
	platformer::Game game;
	if (!game.init())
		return false;
	return game.run();
}