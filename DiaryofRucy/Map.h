#pragma once
#include "GameNode.h"
#include "Camera.h"

class EnemyManager;
class Player;
class KingSlime;
class MegaFlime;
class MushMamBoss;


class Map : public GameNode
{
protected:
	string _mapName;
	GImage* _image;
	GImage* _colImg;
	GImage* _objImg;
	GImage* _itemImg;
	Camera* _camera;

	// 이미지에서 파인드이미지 사용해서 이름 가져오기
	string _imgName;
	string _pImgNameR;
	string _pImgNameL;
	int _indexX;
	int _indexY;

	RECT _rcMap;
	float _x, _y;

	int _playerX;
	int _playerY;

	int _currentFrameX;
	int _currentFrameY;

	float _rndTimeCount;
	float _worldTimeCount;

	Player* _player;

	bool _isVisit;
	bool _isClear;
	int* _stage;

	bool _save;
	
public:

	HRESULT init(int* stage);
	virtual HRESULT vInit(void);

	void release(void);

	void update(void);
	virtual void objectUpdate(void) {}
	virtual void enemyUpdate(void) {}
	virtual void bossUpdate(void) {}

	void render(void);
	virtual void objectRender(void) {}
	virtual void enemyRender(void) {}
	virtual void bossRender(void) {}
	
	void d2drender(void);
	virtual void d2dObjectRender(void) {}
	virtual void d2dEnemyRender(void) {}
	virtual void d2dBossRender(void) {}

	void draw();

	void setPlayerMemoryAddress(Player* player) { _player = player; }
	void setPlayerPosition(POINT playerPosition) { {_playerX = playerPosition.x, _playerY = playerPosition.y; }; }
	void setIsVisit(void) { _isVisit = true; }
	void setIsClear(void) { _isClear = true; }
	void setSaveComplete() { this->_save = false; }

	virtual EnemyManager* getEnemyManagerMemoryAddress() { return 0; }
	virtual KingSlime* getKingSlimeMemoryAddress() { return 0; }
	virtual MegaFlime* getMegaFlimeMemoryAddress() { return 0; }
	virtual MushMamBoss* getMushMamBossMemoryAddress() { return 0; }

	bool getIsClear(void) { return _isClear; }
	bool getIsVisit(void) { return _isVisit; }
	bool getSave(void) { return _save; }
	
	string getMapName() { return _mapName; }
	string getImgName() { return _imgName; }
	string getPImgNameR() { return _pImgNameR; }
	string getPImgNameL() { return _pImgNameL; }

	Map() {}
	virtual ~Map() {}
};
