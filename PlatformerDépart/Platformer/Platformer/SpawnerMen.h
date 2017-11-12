#pragma once
#include "Spawner.h"
namespace platformer
{
	class SpawnerMen :
		public Spawner
	{
	public:
		SpawnerMen();
		~SpawnerMen();
		Enemy* Spawn() override;
	};
}


