#include "Gem.h"

sf::Texture* Gem::texture = nullptr;

bool Gem::init()
{
	texture = new sf::Texture();
	if (!texture->loadFromFile("Ressources//Sprites//Gem.png"))
		return false;
	return true;
}

bool Gem::decharger()
{
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
	return texture == nullptr;
}

Gem::Gem()
{
	setTexture(*texture);
}


Gem::~Gem()
{
}
