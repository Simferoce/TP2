#include "Men2.h"
using namespace platformer;
const std::string Men2::texturePath = "Ressources\\Sprites\\MonsterB\\Idle.png";
Men2::Men2() :Enemy(texturePath)
{
	typeActuel = typeEnemy::MEN2;
	nbVies = 1;
}
Men2::~Men2()
{

}
//incapable d'appeler ces m�thodes
void Men2::Move()
{
	
}
void Men2::init()
{

}
