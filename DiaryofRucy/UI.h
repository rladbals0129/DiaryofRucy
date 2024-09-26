#pragma once
#include "GameNode.h"

#define MAXHP     20
#define MAXMP     10

class Player;
class KingSlime;
class MegaFlime;
class MushMamBoss;
class Stage;
class Ability;


struct tagBaseUI
{
	D2DImageInfo* d2dImage;
	int* pframe;
	int frame;
	int x, y;
	RECT rc;
	string name;
};

struct tagMiniMap
{
	tagBaseUI backGround;
	tagBaseUI miniMap;
	tagBaseUI playerPoint;
	float alpha;
};

struct tagWeaponSlot
{
	tagBaseUI baseUI;
	bool* slotChange;
	int* currentWeapon;
	// 아이템정보 추가할 것
};

struct tagPotionSlot
{
	tagBaseUI baseUI;
	// 아이템정보 추가할 것
};

struct tagProgressBar
{
	tagBaseUI baseUI;
	float* gauge;
	float width;
};

struct tagSkillSlot
{
	tagBaseUI baseUI[4];
	float coolTime[4];
	int manaCost;
	int* currentSkillIndex;
	RECT rcCurrntSkill;
	RECT rcCurrntSkillMana;
};

struct tagCharge
{
	D2DImageInfo* d2dImage;
	RECT* pRc;
	float* pX;
	float* pY;
	int frameX, frameY;
	int frameCount;
	bool* isCharging;
};

struct tagChargeProgressBar
{
	D2DImageInfo* d2dImageBack;
	D2DImageInfo* d2dImageFront;
	float* pX;
	float* pY;
	float* gauge;
	float width;
};

struct tagBossHPProgressBar
{
	D2DImageInfo* d2dImageBack;
	D2DImageInfo* d2dImageFront;
	float x, y;
	RECT rc1;
	RECT rc2;
	float hp1;
	float hp2;
	float width1;
	float width2;
};

struct tagToggleMap
{
	D2DImageInfo* d2dImage;
	int x;
	int y;
	RECT rc;
	bool isToggleKeyOn;
	bool isSelectRoom;
	int selectRoomX, selectRoomY;

	RECT rcMap[4][5];
	float currentAlpha;
};

struct tagAbilityUI
{
	D2DImageInfo* d2dImage;
	int x;
	int y;
	RECT rc;
	RECT rcDescription;
};

class UI : public GameNode
{
private:
	tagBaseUI _stemina;
	tagProgressBar _steminaProgressBar;
	tagProgressBar _expProgressBar;
	tagBaseUI _level;
	tagBaseUI _goldNumber1;
	tagBaseUI _goldNumber10;
	tagBaseUI _goldG;
	tagMiniMap _miniMap;
	tagWeaponSlot _weaponSlot;
	tagPotionSlot _potionSlot;
	tagSkillSlot _skillSlotUI;
	tagBaseUI _currentSkill;
	tagCharge _chargeUI;
	tagChargeProgressBar _chargeBarUI;
	tagBossHPProgressBar _bossUIHPBar;
	tagToggleMap _toggleMap;
	tagAbilityUI _abilityUI[10];



	vector<tagBaseUI> _vMaxHP;
	vector<tagBaseUI> _vCurrentHP;
	vector<tagBaseUI> _vMaxMP;
	vector<tagBaseUI> _vCurrentMP;
	


private:
	Player* _player;
	Stage* _stage;


	KingSlime* _kingSlime;
	MegaFlime* _megaFlime;
	MushMamBoss* _mushMamBoss;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void d2drender(void);
	void UIrender(void);


	void steminaUpdate(void);
	void expUpdate(void);
	void skillUpdate(void);
	void miniMapUpdate(void);
	void chargeUpdate(void);
	void bossUIUpdate(void);
	void toggleMapUIUpdate(void);


	void skillRender(void);
	void HPUpdateRender(void);
	void MPUpdateRender(void);
	void miniMapRender(void);
	void chargeRender(void);
	void bossUIRender(void);
	void toggleMapUIRender(void);
	void abillityUIRender(void);

public:
	bool getIsToggleKeyOn() { return _toggleMap.isToggleKeyOn; }

	void setPlayerMemoryAddress(Player* player) { this->_player = player; }
	void setStageMemoryAddress(Stage* stage) { this->_stage = stage; }

	void setKingSlimeMemoryAddress(KingSlime* kingSlime) { _kingSlime = kingSlime; }
	void setMegaFlimeMemoryAddress(MegaFlime* megaFlime) { _megaFlime = megaFlime; }
	void setMushMamBossMemoryAddress(MushMamBoss* mushMamBoss) { _mushMamBoss = mushMamBoss; }


	UI() {}
	~UI() {}
};

