#pragma once
#include "Map.h"
#include "Potal.h"



class EndMap : public Map
{

private:
	Potal* _potal;
	bool _soundPotal;

public:
	HRESULT vInit(void);
	void release(void);
	void objectUpdate(void);

	void d2dObjectRender(void);


	EndMap() {}
	~EndMap() {}
};

