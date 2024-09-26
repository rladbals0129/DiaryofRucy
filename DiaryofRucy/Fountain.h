#pragma once
#include "GameNode.h"

// 캐릭터가 공격했을시
// 돈을 떨군다.

class Fountain : public GameNode
{
private:

	GImage* _objImg;
	RECT _rc;

	float _x, _y;

	int _fountainType;

	int _currentFrameX;
	int _currentFrameY;
	float _worldTimeCount;

	bool _off;

	// 골드정보 가져오기
	// 플레이어 체력/마나 정보 가져오기
public:
	HRESULT init(int fountainType);
	void release(void);
	void update(void);
	void render(void);

	void fountainOff();

	bool getOff() { return _off; }

	// 플레이어가 분수를 공격했을 시
	// 체력/마나를 깎는다.
	// 골드를 내보내고 얻는다.


	Fountain() {}
	~Fountain() {}
};

