#pragma once
#include "Map.h"
#include "EnemyManager.h"

class NormalMap : public Map
{
private:
	int randMap;
	EnemyManager* _em;
	

public:

	HRESULT vInit();
	void release(void);
	void enemyUpdate(void);
	void enemyRender(void);
	void d2dEnemyRender(void);
	void d2dObjectRender(void);

	EnemyManager* getEnemyManagerMemoryAddress() override { return _em; }

	

	NormalMap() {}
	~NormalMap() {}
};

