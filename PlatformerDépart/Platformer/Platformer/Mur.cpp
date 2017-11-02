#include "Mur.h"
#include "Modele.h"
namespace platformer
{
	Mur::Mur() : Bloc(*Modele::textureMur[rand() % Modele::NBRE_TEXTURE_MUR])
	{
	}


	Mur::~Mur()
	{
	}
}