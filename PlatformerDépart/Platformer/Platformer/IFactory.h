#pragma once
namespace platformer
{
	class Enemy;
	class IFactory
	{
	public:
		virtual Enemy* Spawn() = 0;
		virtual ~IFactory(){}
	};
}
