#pragma once
#include "Map.h"
#include "KingSlime.h"
#include "MegaFlime.h"
#include "MushMamBoss.h"

class BossMap : public Map
{
private:
	KingSlime* _kingSlime;
	MegaFlime* _megaFlime;
	MushMamBoss* _mushMamBoss;


	float _startImageAlpha;
public:
	HRESULT vInit(void);
	void release(void);
	void bossUpdate(void);
	void bossRender(void);
	void d2dBossRender(void);

	KingSlime* getKingSlimeMemoryAddress() override { return _kingSlime; }
	MegaFlime* getMegaFlimeMemoryAddress() override { return _megaFlime; }
	MushMamBoss* getMushMamBossMemoryAddress() override { return _mushMamBoss; }

	bool getIsClear(void) { return _isClear; }

	BossMap() {}
	~BossMap() {}
};

