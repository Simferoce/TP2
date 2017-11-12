#include "SpawnerMen2.h"
#include "Men2.h"

namespace platformer
{
	SpawnerMen2::SpawnerMen2()
	{
	}
	SpawnerMen2::~SpawnerMen2()
	{
	}
	Enemy * SpawnerMen2::Spawn()
	{
		platformer::Men2* enemy = new platformer::Men2();
		enemy->init();
		enemy->setPosition(getPosition());
		return (Enemy*)enemy;
	}
}
