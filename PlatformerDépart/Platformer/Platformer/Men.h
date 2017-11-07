#pragma once
#include "Ennemi.h"
using namespace platformer;
class Men :public Enemy
{
public:
	Men();
	~Men();
	bool Init(const int limiteGauche, const int limiteDroite, const String texturePath);
	int GetNbVies();
private:
	Texture texture;
	int nbVies;
};