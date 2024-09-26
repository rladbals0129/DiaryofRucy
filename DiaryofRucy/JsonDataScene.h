#pragma once
#include "GameNode.h"
#include "ItemSample.h"
class JsonDataScene :public GameNode
{
private:
	ItemSample* _questSample;
	vector<GImage*> images;
	vector<ItemData*> itemDatas;
	ItemData* _name;
	GImage* inven;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void questPopUp();
	void Info();
	void Image();
	JsonDataScene() {}
	~JsonDataScene() {}
};

