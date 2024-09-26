#pragma once
#include "GameNode.h"
class Store : public GameNode
{
private:
	GImage* _store;
	
	int sCount;
	int sIndex;

	RECT _rcStore;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

};


