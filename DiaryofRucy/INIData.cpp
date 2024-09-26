#include "Stdafx.h"
#include "INIData.h"

HRESULT INIData::init(void)
{
	return S_OK;
}

void INIData::release(void)
{
	// !do nothing
}

void INIData::addData(char* section, char* key, char* value)
{
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

void INIData::iniSave(char* fileName, bool clear)
{
	char str[256];
	char dir[256];

	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));

	sprintf_s(dir, "\\IniData%s.ini", fileName);

	GetCurrentDirectory(256, str);

	strcat_s(str, dir);

	if (clear)
	{
		// 파일 내의 모든 섹션을 삭제
		for (int i = 0; i < _vIniData.size(); i++)
		{
			arrIniData vData = _vIniData[i];
			WritePrivateProfileString(vData[0].section, NULL, NULL, str);
		}
	}

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];

		WritePrivateProfileString(vData[0].section,	vData[0].key, vData[0].value, str); // 파일의 정보를 쓴다. 해당 섹션과 키값이 없으면 자동으로 생성을 시킨다.

		vData.clear();
	}

	_vIniData.clear();

}


char* INIData::loadDataString(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];

	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));

	sprintf_s(dir, "\\IniData%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	char data[64] = { NULL };

	GetPrivateProfileString
	(
		section,	// 읽어올 Value가 있는 섹션의 이름
		key,		// 읽어올 value의 이름
		"",			// 섹션 이름이나 키 이름을 찾지 못하면 출력할 문자열
		data,		// 키값에서 가르키는 값을 저장할 버퍼
		64,			// 키값을 저장할 버퍼
		str
	);

	return nullptr;
}

int INIData::loadDataInteger(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];

	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));

	sprintf_s(dir, "\\IniData%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat_s(str, dir);


	return GetPrivateProfileInt(section, key, 0, str);
}
