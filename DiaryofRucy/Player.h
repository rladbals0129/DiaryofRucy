#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "PlayerBullet.h"
#include "Skill.h"
#include "Ability.h"




// 1스테이지 활
// 2스테이지 검
// 3스테이지 지팡이



class EnemyManager;
class KingSlime;
class MegaFlime;
class MushMamBoss;
class BigSlime;
class UI;

enum class EWeaponType : int
{
	NOMAL, SWORD, BOW, STAFF
};

enum class ERucyDirection : int
{
	LEFTUP, UP,
	RIGHTUP, RIGHT,
	RIGHTDOWN, DOWN,
	LEFTDOWN, LEFT
};

struct tagAvoidAfterImage
{
	RECT rc;
	float time;
	int frameX;
};

struct tagDamageBox
{
	int damage;
	POINT pt;
	int count;
	tagDamageBox()
	{
		count = 30;
	}
};

struct tagHitEffect
{
	RECT rc;
	int frameX;
	int frameY;
	float worldTime;
	tagHitEffect(int x, int y)
	{
		rc = RectMakeCenter(x, y, D2DMANAGER->findImage("히트이펙트")->frameWidth, D2DMANAGER->findImage("히트이펙트")->frameHeight);
		frameX = 0;
		frameY = 0;
		worldTime = TIMEMANAGER->getWorldTime();
	}
};

class Player : public GameNode
{
private:
	enum EBehaviorType : int
	{
		STOP, MOVE,
		DAMAGED, SKILL, AVOID,
		SWORDATTACK, BOWATTACK, STAFFATTACK,
		SLASH_ATTACK, DIE,
		BEHAVIOR_MAX
	};
private:
	GImage* _image;
	float	_x, _y;
	POINT	_ptXY;
	POINT	_ptSlashStartXY;
	RECT	_rcCollision;
	RECT	_rc;
	ERucyDirection _direction;
	ERucyDirection _avoidDirection;
	EWeaponType _weaponType;
	BYTE _alpha;

	int _frame;
	int _preFrame;
	int _currentMoveFrameX;
	int _currentAvoidFrameX;
	int _preAvoidFrameX;
	int _currentAttackFrameX;
	int _hitFrameX;
	int _hitFrameY;
	bool _run;
	bool _isCharging;
	bool _weaponSlot;
	float _staffGauge;
	int _swordCombo;
	bool _canSlash;
	bool _canTripleShot;
	bool _avoidManaRecovery;
	bool _invincible;
	bool _damagedInvincible;
	float _invincibilityTime;
	float _skillCastWorldTime;
	float _skillCastFrame;
	int _invincibilityCount;
	bitset<(int)EBehaviorType::BEHAVIOR_MAX> _bBehaviorType;


	vector<tagAvoidAfterImage>			 _vAvoidAfterImage;
	vector<tagAvoidAfterImage>::iterator _viAvoidAfterImage;

	vector<Ability> _vAbillity;
	vector<Ability>::iterator _viAbillity;

	queue<tagDamageBox> _qDamageBox;
	queue<tagHitEffect> _qHitEffect;

private:
	int		_level;
	int		_maxExp;
	float	_currentExp;
	
	int		_maxHp, _maxMp;
	int		_currentHp, _currentMp;
	float	_stemina;
	float	_balance;
	float	_attackDamage;
	float	_attackSpeed;
	float	_magicDamage;
	float	_coolTimeReduce;
	float	_moveSpeed;
	int		_critical;
	int		_gold;

	
	float _abilityAttackDamage;
	float _abilityMagicDamage;
	int _swordStack;
	int _bowStack;
	int _staffStack;
	
	int _currentSkill;
	float _avoidDistance;
	float _attackBoundary;
	float _attackRange;
	float _bulletSpeed;
	

	int _runSoundCnt;



	float finalDamage
	(
		float attackDamage,
		float magicDamage,
		float weaponAttackDamage,
		float weaponMagicDamage,
		float abilityAttackDamage,
		float abilityMagicDamage,
		float skillDamageMultiple = 1
	);
	void pixelCollision(void);
	void enemyCollision();

private:
	EnemyManager* _em;
	KingSlime* _kingSlime;
	BigSlime* _bigSlime;
	MegaFlime* _megaFlime;
	MushMamBoss* _mushMamBoss;
	UI* _ui;

	Arrow* _arrow;
	MagicBall* _magicBall;
	ChargingMagicBall* _chargingMagicBall;
	Sword1* _sword1;
	Sword2* _sword2;
	Sword3* _sword3;
	SlashSword* _slashSword;

	Skill* _SkillSlot[4];

	bitset<4> _bPixelCollision;
	bitset<4> _bEnemyCollision;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	
	void move(void);
	void attack(void);
	void slashAttack(void);
	void skillUpdate(void);
	void skillRender(void);
	void skillShot(void);
	void skillCast(void);
	void skillCollision(void);
	void avoid(void);
	void invincibilityTimer(float time);
	void bulletUpdate(void);
	void bulletCollision(void);
	void bulletRender(void);
	void moveAnimation(void);
	void attackAnimation(void);
	void avoidAnimation(void);
	void damagedAnimation(void);
	void draw(void);
	void inputKey(void);
	void setAttackDirectionAngle(void);
	void stateUpdate(void);
	void damageBoxRender(void);
	void hitEffect(void);
	void abilityIncrease(void);

public:
	void setPosition(float x, float y) 
	{
		this->_x = x; 
		this->_y = y; 
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		_rcCollision = rucyCollisionAreaResizing(_rc, 80, 90);
		_image = IMAGEMANAGER->findImage("루시걷기");
		_image->setFrameX(1);
	}

	void setExp(float exp) { this->_currentExp += exp; }
	void setLevel(int level) { this->_level = level; }
	void setMaxHP(int maxHP) { this->_maxHp += maxHP; }
	void setMaxMP(int maxMP) { this->_maxMp += maxMP; }
	void setCurrentHP(int currentHP) { this->_currentHp += currentHP; }
	void setCurrentMP(int currentMP) { this->_currentMp += currentMP; }
	void setPixelColTrue(int direction) { this->_bPixelCollision.set(direction); }
	void setPixelColFalse(int direction) { this->_bPixelCollision.reset(direction); }	
	void setEnemyManagerMomoryAddress(EnemyManager* em) { this->_em = em; }
	void setKingSlimeMemoryAddress(KingSlime* kingSlime) { this->_kingSlime = kingSlime; }
	void setMegaFlimeMemoryAddress(MegaFlime* megaFlime) { this->_megaFlime = megaFlime; }
	void setMushMamBossMemoryAddress(MushMamBoss* mushMamBoss) { this->_mushMamBoss = mushMamBoss; }
	void setBigSlimeMemoryAddress(BigSlime* bigSlime) { this->_bigSlime = bigSlime; }
	void setUIMemoryAddress(UI* ui) { this->_ui = ui; }
	void setSkill(Skill* skill) 
	{
		for (int i = 0; i < 4; i++)
		{
			if (_SkillSlot[i] == nullptr)
			{
				_SkillSlot[i] = skill;
				skill->init();
				break;
			}
		}
	}
	void setAbility(Ability ability)
	{
		this->_vAbillity.push_back(ability);
		abilityIncrease();
	}
	void setDamaged(int damage = 1)
	{
		if (damage > 1) _currentHp -= damage;
		else _currentHp--;
		_bBehaviorType.reset();

		if (_currentHp < 1)
		{
			_bBehaviorType.set(DIE);
			return;
		}
		_bBehaviorType.set(DAMAGED);
		_damagedInvincible = true;
		_invincibilityTime = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("루시피격음", 0.5f);
	}
	// 회피하면 
	void setAvoidManaRecovery() 
	{ 
		if (_currentMp < _maxMp && !_avoidManaRecovery) _currentMp++;
		this->_avoidManaRecovery = true;
		if (_weaponType == EWeaponType::SWORD) this->_canSlash = true;
		if (_weaponType == EWeaponType::BOW) this->_canTripleShot = true;
	}



	bool getBehaviorType(int arr) { return this->_bBehaviorType.test(arr); }
	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }
	RECT getRect(void) { return this->_rc; }
	RECT getCollisionRect(void) { return this->_rcCollision; }
	bool getInvincible(void) { return this->_invincible; }
	
	float* getpX(void) { return &_x; }
	float* getpY(void) { return &_y; }
	RECT* getpRcColision(void) { return &_rcCollision; }
	int* getLevel(void) { return &_level; }
	int* getGold(void) { return &_gold; }
	bool* getWeaponSlot(void) { return &_weaponSlot; }
	int* getMaxHP(void) { return &_maxHp; }
	int* getCurrentHP(void) { return &_currentHp; }
	int* getMaxMP(void) { return &_maxMp; }
	int* getCurrentMP(void) { return &_currentMp; }
	float* getStemina(void) { return &_stemina; }
	float* getExp(void) { return &_currentExp; }
	Skill* getSkill(int index) { return _SkillSlot[index]; }
	int* getCurrentSkillIndex() { return &_currentSkill; }
	bool* getIsCharging() { return &_isCharging; }
	float* getChargeGauge() { return &_staffGauge; }
	int* getWeaponType() { return (int*)&_weaponType; }
	vector<Ability> getAbility() { return _vAbillity; }

	Player() {}
	~Player() {}
};