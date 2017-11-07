#include "Men.h";
using namespace platformer;
Men::Men():Enemy()
{
	sizeNumberEnemies++;
	typeEquipe = MEN;
}
Men::~Men()
{
	
}
bool Men::Init(const int limiteGauche, const int limiteDroite, const String texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}
	setTexture(texture);
	setTextureRect(persoRect);

	nbVies = 1;
	this->limiteGauche = limiteGauche;
	this->limiteDroite = limiteDroite;

	return true;
}


