#pragma once
#include "SingletonBase.h"

#pragma endregion
class JsonSaveLoad : public SingletonBase<JsonSaveLoad>
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWithFileStream(char* fileName);



public:
	HRESULT init(void);
	void release(void);
	void saveJsonFile(char* fileName, Json::Value root);

	Json::Value loadJsonFile(char* fileName);


	JsonSaveLoad();
	~JsonSaveLoad();

};

