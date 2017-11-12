#pragma once
#include "Enemy.h"
namespace platformer
{
	class Bloc;
	class Men:public Enemy
	{
		static const std::string texturePath;
	public:
		Men();
		~Men();
		void Move();
		void init();
	};
}