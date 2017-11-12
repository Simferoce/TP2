#include "Zombie.h"
using namespace platformer;
const std::string Zombie::texturePath = "Ressources\\Sprites\\MonsterC\\Idle.png";
Zombie::Zombie() :Enemy(texturePath)
{
	typeActuel = typeEnemy::ZOMBIE;
	nbVies = 2;
}
Zombie::~Zombie()
{

}
//incapable d'appeler ces méthodes j'ai supprimer le code
void Zombie::Move()
{
	
}
void Zombie::init()
{

}
