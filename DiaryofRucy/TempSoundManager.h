#pragma once
#include "SingletonBase.h"

// 윈도우 내장 라이브러리 (재생)
// 시간 or v사운드 -> PlaySound()
#include <mmsystem.h>
// 멀티미디어컨트롤인터페이스  api 툴 (장치관리자에 접근)
// mciSendString()이라는 함수를 사용하기 위해 추가
#include <mciapi.h>
// mm 멀티 미디어의 약자
#pragma comment(lib, "Winmm.lib")
class TempSoundManager : public SingletonBase <TempSoundManager>
{

public:

	HRESULT init(void);
	// MP3
	void addMp3FileWithKey(string key, string fileName);
	// WAV
	void addWaveFileWithKey(string key, string fileName);
	// 효과음
	void playEffectSoundWave(char* fileName);
	// MP3 재생
	void playSoundWithKey(string key);
	// MP3 정지
	void stopMp3WithKey(string key);

	
	TempSoundManager() {}
	~TempSoundManager() {}
};

