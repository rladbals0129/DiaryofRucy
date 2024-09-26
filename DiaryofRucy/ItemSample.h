#pragma once
#include "ItemData.h"
#include "ItemSample.h"
class ItemSample
{
private:
	queue<ItemData*> _quest;

public:
	void init(void);
	void questSetup(ItemData* pQuest = nullptr);
	queue<ItemData*>* getQuest()
	{
		return &this->_quest;
	};

	queue<ItemSample*>* getItem() {}
	ItemSample() {}
	~ItemSample() {}
};

