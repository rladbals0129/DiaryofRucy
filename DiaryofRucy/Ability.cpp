#include "Stdafx.h"
#include "Ability.h"

Ability::Ability(D2DImageInfo* image, string name, string description, int hp, int mp, int attackDamage, int magicDamage, float attackSpeed, int attackBoundary)
{
	_image = image;
	_name = name;
	_description = description;

	_hpIncrease = hp;
	_mpIncrease = mp;
	_attackDamageIncerease = attackDamage;
	_magicDamageIncerease = magicDamage;
	_attackSpeedIncerease = attackSpeed;
	_attackBoundaryIncerease = attackBoundary;
}

Ability::~Ability()
{

}
