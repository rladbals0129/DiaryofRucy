#pragma once
#include "GameNode.h"
#include "Item.h"

class ItemChest : public GameNode
{
private:
	GImage* _objImg;
	RECT _rc;

	float _x, _y;

	int _grade;

	int		_currentFrameX;
	int		_currentFrameY;
	float _worldTimeCount;

	// 플레이어와 상호작용 시 열림
	bool _action;
	
	item* _item;
public:
	HRESULT init(int grade);
	void release(void);
	void update(void);
	void render(void);

	bool getAction() { return _action; }
	void openChest();

	item* getItem() { return _item; }

	int getDistanceWithPlayer() { return _objImg->getFrameWidth(); }

	POINT getPosition() { return { (long)_x, (long)_y }; }

	ItemChest() {}
	~ItemChest() {}
};

