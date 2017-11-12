#pragma once
#include "Spawner.h"
namespace platformer
{
	class SpawnerZombie :
		public Spawner
	{
	public:
		SpawnerZombie();
		~SpawnerZombie();
		Enemy* Spawn() override;
	};
}


