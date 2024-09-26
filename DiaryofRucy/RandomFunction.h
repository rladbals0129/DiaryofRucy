#pragma once
#include "SingletonBase.h"


class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		//GetTickCount() : API공용함수
		// ㄴ API 함수로 OS가 부팅된 후의 경과 시간을 체크해준다.
		// ㄴ 밀리세컨 단위로 체크가 가능하며 밀리세컨 단위로 시간 값을 반환하기 때문에 규모가 크지 않는 로직에 적합하다
		srand(GetTickCount());
	}


	~RandomFunction() {}

	HRESULT init(void) { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}


	// 0을 조심하자
	inline int getFromIntTo(int fromNum, int toNum)
	{
		// if가 빠진 이유 : 사용자체에 예외처리를 할 뿐더러 inline화 안될 수 가 있음
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	// 0 ~ 1
	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	// 0 ~ num
	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}
	
	// fromNum ~ toNum
	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}




};