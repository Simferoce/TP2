
#pragma once
#include "Enemy.h"
namespace platformer
{
	class Bloc;
	class Men2 :public Enemy
	{
		static const std::string texturePath;
	public:
		Men2();
		~Men2();
		void Move();
		void init();
	};
}