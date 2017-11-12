#pragma once
#include "Spawner.h"
namespace platformer
{
	class SpawnerMen2 :
		public Spawner
	{
	public:
		SpawnerMen2();
		~SpawnerMen2();
		Enemy* Spawn() override;
	};
}


