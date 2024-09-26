#pragma once

/*
 - 시간관련 API 공용 함수
  ㄴ 문제가 있다....
  ㄴ 최초 설계단계에서 게임을 고려하고 만든 타이머들이 아니기 때문에 정밀도가 떨어진다.

timeGetTime (윈도우가 시작되고 1분이 지났으면 60000리턴)
GetTickCount (부팅시간 체크 -> 부팅된 이후 1초에 1000씩 틱이 증가한다 약 50일 이후 오류)
				반환 시간이 최대 DWORD(32비트)이다. 49.7일동안 윈도우를 종료하지 않으면 0으로 초기화된다.
GetTickCount64

 - 타이머
  ㄴ 시간을 측정하는 함수들은 기본적으로 윈도우가 시작된 이후 지난 시간을 Milli Second 단위로 반환(1/1000초)
  ㄴ 밀리세컨은 기본적으로 정밀도가 떨어진다 -> 게임에서
  ㄴ 그렇기 때문에 보다 높은 정밀도를 원한다면 고해상도 타이머를 추가해서 사용해야 한다.

 - 타이머를 구현할 때는 보통 해상도와 클럭을 알고 있어야 한다.

 ◈ 해상도?

  - 다양한 시간 함수들은 시간을 측정하기 위한 각각의 틱 계산 로직이 있다.
	ㄴ 이 기준은 1분을 중저으로 삼았을 때 얼마나 많은 프레임으로 나눌 수 있는지 계산
  - 1분동안 얼마나 많은 틱으로 나눠서 시간의 정확도를 높이느냐가 고해상도와 저해상도의 차이를 발생시킨다.

  ◈ 클럭 (진동수)
  - 타이머에서 말하는 클럭은 CPU클럭
  - 클럭 자체는 디지털 회로의 전기적 진동 수 이며 헤르츠(Hz) 단위로 표기하는게 일반적
	ㄴ EX: 1초에 1Hz면 이진수의 신호를 한번 준다는 얘기 (0또는1)
		ㄴ 1 비트를 옮길 수 있다는 말
		ㄴ 1GHz는 10의 9제곱 -> 10억번
		ㄴ 3.7GHz는 약 37억번 (1초에 36억 비트를 옮길 수 있다.)

  단위
  ㄴ Milli Second
  ㄴ 10 Milli Second (세티)
  ㄴ 100 Milli Second (데시)
*/

class Timer
{
private:
	float _timeScale;				// 경과시간
	float _timeElapsed;				// 현재~마지막 경과값
	bool _isHardware;				// 하드웨어 지원 여부

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:

	HRESULT init(void);
	// -> 프레임 떨어질 시 이거 풀고 해보자
	void tick(float lockFPS = 0.0f);

	unsigned long getFrameRate(char* str = nullptr) const;
	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }
	// const 멤버변수의 값을 변경시키지 않겠다 (데이터 접근 허용하지 않겠다)


	Timer() {}
	~Timer() {}
};

