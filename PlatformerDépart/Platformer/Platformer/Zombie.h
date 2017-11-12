#pragma once
#pragma once
#include "Enemy.h"
namespace platformer
{
	class Bloc;
	class Zombie :public Enemy
	{
		static const std::string texturePath;
	public:
		Zombie();
		~Zombie();
		void Move();
		void init();
	};
}