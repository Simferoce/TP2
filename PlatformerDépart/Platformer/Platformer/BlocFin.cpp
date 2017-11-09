#include "BlocFin.h"
#include "Modele.h"
#include "SceneNiveau.h"

namespace platformer
{
	sf::Texture BlocFin::texture = sf::Texture();
	sf::Texture& BlocFin::initTexture()
	{
		texture.create(SceneNiveau::TAILLE_TUILES_X, SceneNiveau::TAILLE_TUILES_Y);
		return texture;
	}
	BlocFin::BlocFin() : Bloc(initTexture())
	{
	}


	BlocFin::~BlocFin()
	{
	}
}
