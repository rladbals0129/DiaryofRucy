#pragma once

class Ability
{
private:
	D2DImageInfo* _image;
	string _name;
	string _description;

	int _hpIncrease;
	int _mpIncrease;
	int _attackDamageIncerease;
	int _magicDamageIncerease;
	float _attackSpeedIncerease;
	int _attackBoundaryIncerease;


public:
	
	D2DImageInfo* getImage() { return this->_image; }
	string		  getName() { return this->_name; }
	string		  getDescription() { return this->_description; }
	int			  getHpIncrease() { return this->_hpIncrease; }
	int			  getMpIncrease() { return this->_mpIncrease; }
	int			  getAttackDamageIncerease() { return this->_attackDamageIncerease; }
	int			  getMagicDamageIncerease() { return this->_magicDamageIncerease; }
	float		  getAttackSpeedIncerease() { return this->_attackSpeedIncerease; }
	int			  getAttackBoundaryIncerease() { return this->_attackBoundaryIncerease; }




	Ability(D2DImageInfo* image, string name, string description, int hp, int mp, int attackDamage, int magicDamage, float attackSpeed, int attackBoundary);
	~Ability();
};

