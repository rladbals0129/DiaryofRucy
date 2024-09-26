#pragma once
#include "Stdafx.h"
#include "SingletonBase.h"
// 객체지향 전환 -> 설계 방식 / 방법론  (직접 그려보자..)
// 123~126개의 키 조합을 표현 가능하다 fn키 등장으로 256정도는 잡아주는게 좋다
// 키 라는 것은 os가 관리하며 전역적으로 영향을 미친다 = 싱글톤패턴을 사용하면 좋다


#define KEY_MAX 256


class KeyManager : public SingletonBase <KeyManager>
{
private:
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];

	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;


public:
	// 초기화
	HRESULT init(void);

	// 키가 한번만 눌렸는지
	bool isOnceKeyDown(int key);	// 버추얼 키값을 int로 해서 메모리 낭비를 하는지? 수많은 연산 처리중에서 최우선적으로 처리하기 위해
	// 한번 누르고 띄었는지
	bool isOnceKeyUp(int key);
	// 키가 계속 눌려 있는지
	bool isStayKeyDown(int key);
	// 토글키
	bool isToggleKey(int key);
	// 4개의키를 하나도 누르지 않은 상태를 확인
	bool checkMoveKeyDown(int key1, int key2, int key3, int key4);

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }

	KeyManager() {}
	~KeyManager() {}
};

