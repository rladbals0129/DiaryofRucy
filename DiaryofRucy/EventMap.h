#pragma once
#include "Map.h"
#include "Fountain.h"
#include "Statue.h"

// 골드 전방선언

class EventMap : public Map
{
private:
	int _rndEvent;
	int _fountainType;
	int _statueRightType;
	int _statueLeftType;

	Fountain* _fountain;

	Statue* _statue;

public:
	HRESULT vInit(void);

	void release(void);
	void objectUpdate(void);
	void objectRender(void);

	EventMap() {}
	~EventMap() {}
};

