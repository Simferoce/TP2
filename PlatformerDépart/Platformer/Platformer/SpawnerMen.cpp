#include "SpawnerMen.h"
#include "Men.h"

namespace platformer
{
	SpawnerMen::SpawnerMen()
	{
	}


	SpawnerMen::~SpawnerMen()
	{
	}

	Enemy * SpawnerMen::Spawn()
	{
		platformer::Men* enemy = new platformer::Men();
		enemy->init();
		enemy->setPosition(getPosition());
		return (Enemy*)enemy;
	}
}

