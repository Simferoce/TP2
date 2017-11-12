#include "Spawner.h"
#include "SceneNiveau.h"

namespace platformer
{
	sf::Texture Spawner::texture = sf::Texture();
	sf::Texture& Spawner::initTexture()
	{
		return texture;
	}
	Spawner::Spawner() : Bloc(initTexture())
	{
	}
	sf::FloatRect Spawner::getGlobalBounds()
	{
		return sf::FloatRect(0,0,0,0);
	}
	Spawner::~Spawner()
	{
	}
}


