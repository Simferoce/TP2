#include "Men.h"
using namespace platformer;
const std::string Men::texturePath = "Ressources\\Sprites\\MonsterA\\Idle.png";
Men::Men() :Enemy(texturePath)
{
	typeActuel = typeEnemy::MEN;
	nbVies = 1;
}
Men::~Men()
{
	
}
//incapable d'appeler ces méthodes
void Men::Move()
{

}
void Men::init()
{
	
}
