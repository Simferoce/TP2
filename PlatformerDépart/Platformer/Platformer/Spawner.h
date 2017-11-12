#pragma once
#include "Bloc.h"
#include "IFactory.h"
#include <SFML/Graphics/Texture.hpp>

namespace platformer
{
	class Spawner :
		public platformer::Bloc, public IFactory
	{
	protected:
		static sf::Texture texture;
		sf::Texture& initTexture();
	public:
		Spawner();
		virtual sf::FloatRect getGlobalBounds();
		virtual ~Spawner();
	};
}


