#pragma once
#include "Map.h"
#include "ItemChest.h"

class item;
class Ability;

class ChestMap : public Map
{
private:
	int _rndChest;

	ItemChest* _itemChest;

	//vector<item*> _vItem;

public:
	HRESULT vInit(void);

	void objectUpdate(void);
	void objectRender(void);

	ChestMap(){}
	~ChestMap() {}
};

