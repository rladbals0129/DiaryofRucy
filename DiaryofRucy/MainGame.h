#pragma once
#include "GameNode.h"
#include "ResourcesClass.h"




class MainGame : public GameNode
{
private:
	ResourcesClass _resources;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	MainGame() {}
	~MainGame() {}
};

