#pragma once
#include "SingletonBase.h"

struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class INIData : public SingletonBase<INIData>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<arrIniData> arrIniDatas;

private:
	arrIniDatas _vIniData;

public:
	HRESULT init(void);
	void release(void);

	// 정보 추가
	void addData(char* section, char* key, char* value);
	// INI파일 디렉토리에 생성
	void iniSave(char* fileName, bool clear = false);

	// 문자열
	char* loadDataString(char* fileName, char* section, char* key);
	// 정수
	int loadDataInteger(char* fileName, char* section, char* key);

	INIData() {}
	~INIData() {}
};

