#pragma once
#include "Bloc.h"
#include <SFML/Graphics/Texture.hpp>

namespace platformer
{
	class BlocFin :
		public Bloc
	{
		static sf::Texture& initTexture();
		static sf::Texture texture;
	public:
		BlocFin();
		~BlocFin();
	};
}


