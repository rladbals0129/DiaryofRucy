#include "Stdafx.h"
#include "ItemSample.h"

void ItemSample::init(void)
{
	questSetup();
}
void ItemSample::questSetup(ItemData* pQuest)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./ItemData.json");

	for (auto it = root["posion"].begin(); it != root["posion"].end(); it++)
	{
		if ((*it).isObject())
		{
			ItemData* qQuest = new ItemData;
			qQuest->init
			(
				(*it)["name"].asString(),
				(*it)["fileLocation"].asString(),
				(*it)["ex"].asString(),
				(*it)["x"].asDouble(),
				(*it)["y"].asDouble(),
				(*it)["width"].asInt(),
				(*it)["height"].asInt(),
				(*it)["RGB"].asBool(),
				(*it)["atk"].asDouble(),
				(*it)["mpk"].asDouble(),
				(*it)["Mhp"].asDouble(),
				(*it)["Mmp"].asDouble(),
				(*it)["page"].asInt(), (*it)["activeFlag"].asBool()
			);
			_quest.push(qQuest);
		}
	}
	for (auto it = root["normal"].begin(); it != root["normal"].end(); it++)
	{
		if ((*it).isObject())
		{
			ItemData* qQuest = new ItemData;
			qQuest->init
			(
				(*it)["name"].asString(),
				(*it)["fileLocation"].asString(),
				(*it)["ex"].asString(),
				(*it)["x"].asDouble(),
				(*it)["y"].asDouble(),
				(*it)["width"].asInt(),
				(*it)["height"].asInt(),
				(*it)["RGB"].asBool(),
				(*it)["atk"].asDouble(),
				(*it)["mpk"].asDouble(),
				(*it)["Mhp"].asDouble(),
				(*it)["Mmp"].asDouble(),
				(*it)["page"].asInt(), 
				(*it)["activeFlag"].asBool()
			);
			_quest.push(qQuest);
		}
	}
}
