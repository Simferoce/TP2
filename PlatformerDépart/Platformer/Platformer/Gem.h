#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Gem :
	public sf::Sprite
{
	static sf::Texture* texture;
public:
	static bool init();
	static bool decharger();
	Gem();
	~Gem();
};

