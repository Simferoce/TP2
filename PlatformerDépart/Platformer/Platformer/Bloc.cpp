#include "Bloc.h"


namespace platformer
{
	Bloc::Collision Bloc::DetermineCollision(sf::FloatRect other, sf::Vector2f deplacementPerFrameObjectOther)
	{
		//Width and Heigh of colision rectangle.
		float colisionX = 0;
		float colisionY = 0;
		if (deplacementPerFrameObjectOther.x > 0)
		{
			if (other.left + other.width > getGlobalBounds().left 
				&& other.left + other.width < getGlobalBounds().left + getGlobalBounds().width)
			{
				colisionX = other.left + other.width - getGlobalBounds().left;
			}
		}
		else if (deplacementPerFrameObjectOther.x < 0)
		{
			if (other.left <= getGlobalBounds().left + getGlobalBounds().width
				&& other.left >= getGlobalBounds().left)
			{
				colisionX = (other.left - getGlobalBounds().left + getGlobalBounds().width);
			}
		}
		if (deplacementPerFrameObjectOther.y > 0)
		{
			if (other.top + other.height >= getGlobalBounds().top
				&& other.top + other.height <= getGlobalBounds().top + getGlobalBounds().height)
			{
				colisionY = other.top + other.height - getGlobalBounds().top;
			}
		}
		else if (deplacementPerFrameObjectOther.y < 0)
		{
			if (other.top <= getGlobalBounds().top + getGlobalBounds().height
				&& other.top >= getGlobalBounds().top)
			{
				colisionY= (other.top - getGlobalBounds().top + getGlobalBounds().height);
			}
		}
		if (colisionX == 0 && colisionY == 0)
		{
			if (getGlobalBounds().intersects(other))
				return Collision::CollisionWithNoDeterminateSide;
			else
				return  Collision::None;
		}
		else if (colisionX == 0)
		{
			if (deplacementPerFrameObjectOther.y < 0)
				return Collision::Bot;
			else if (deplacementPerFrameObjectOther.y > 0)
				return Collision::Top;
			else
				static_assert(true, "Should not be here");
		}
		else if (colisionY == 0)
		{
			if (deplacementPerFrameObjectOther.x < 0)
				return Collision::Right;
			else if (deplacementPerFrameObjectOther.x > 0)
				return Collision::Left;
			else
				static_assert(true, "Should not be here");
		}
		else
		{
			float numbFrameBetweenColisionAndDectectionX = colisionX / deplacementPerFrameObjectOther.x;
			float numbFrameBetweenColisionAndDectectionY = colisionY / deplacementPerFrameObjectOther.y;

			if (abs(numbFrameBetweenColisionAndDectectionX) > abs(numbFrameBetweenColisionAndDectectionY))
			{
				if (deplacementPerFrameObjectOther.x < 0)
					return Collision::Right;
				else if (deplacementPerFrameObjectOther.x > 0)
					return Collision::Left;
				else
					static_assert(true, "Should not be here");
			}
			else if (abs(numbFrameBetweenColisionAndDectectionX) < abs(numbFrameBetweenColisionAndDectectionY))
			{
				if (deplacementPerFrameObjectOther.y < 0)
					return Collision::Bot;
				else if (deplacementPerFrameObjectOther.y > 0)
					return Collision::Top;
				else
					static_assert(true, "Should not be here");
			}
			else
			{
				//Cas spécial. Priorité de haut / bas

				if (deplacementPerFrameObjectOther.y < 0)
					return Collision::Bot;
				else if (deplacementPerFrameObjectOther.y > 0)
					return Collision::Top;
				else if (deplacementPerFrameObjectOther.x < 0)
					return Collision::Left;
				else if (deplacementPerFrameObjectOther.x > 0)
					return Collision::Right;
				else
					static_assert(true, "Should not be here");
			}
		}
	}

	Bloc::Bloc(sf::Texture& texture)
	{
		setTexture(texture);
	}


	Bloc::~Bloc()
	{
	}
}