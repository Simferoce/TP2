#include "SpawnerZombie.h"
#include "Zombie.h"

namespace platformer
{

	SpawnerZombie::SpawnerZombie()
	{
	}


	SpawnerZombie::~SpawnerZombie()
	{
	}
	Enemy * SpawnerZombie::Spawn()
	{
		platformer::Zombie* enemy = new platformer::Zombie();
		enemy->init();
		enemy->setPosition(getPosition());
		return (Enemy*)enemy;
	}
}
