#include "Stdafx.h"
#include "JsonDataScene.h"

HRESULT JsonDataScene::init(void)
{
	_questSample = new ItemSample;
	_questSample->init();

	queue<ItemData*>* queue = _questSample->getQuest(); //json내용이 없어서 못찍음
	while (queue->empty() == false)
	{
		ItemData* nowItem = queue->front(); //순차적? 컴파일러가 좋아하는 오류 모호함

		itemDatas.push_back(nowItem);

		images.push_back(
			IMAGEMANAGER->addImage(nowItem->getName().c_str(),
				nowItem->getFileLocation().c_str(),
				nowItem->getX(), nowItem->getY(), nowItem->getWidth(),
				nowItem->getHeight(), nowItem->getRGB(), RGB(255, 0, 255))
		);

		queue->pop();
	}
	inven = IMAGEMANAGER->addImage("인벤",
		"Resources/Images/UI/inven.bmp",240,296,true,RGB(255,0,255));
	return S_OK;
}

void JsonDataScene::release(void)
{
	//do nothing


}

void JsonDataScene::update(void)
{
	//do nothing
	

}

void JsonDataScene::render(void)
{
	questPopUp();
	inven->render(getMemDC(), 100, 100);
	
}

void JsonDataScene::questPopUp()
{
	
	Info();
	Image();
}

void JsonDataScene::Info()
{
	char str[256];

	for (int i = 0; i < itemDatas.size(); i++)
	{
		sprintf_s(str, "이름:%s", itemDatas[i]->getName().c_str());
		//TextOut(getMemDC(), 200 + i * width, 150, str, strlen(str));

		sprintf_s(str, "파일 위치:%s", itemDatas[i]->getFileLocation().c_str());
		//TextOut(getMemDC(), 200 + i * width, 170, str, strlen(str));

		sprintf_s(str, "아이템 설명:%s", itemDatas[i]->getEx().c_str());
		//TextOut(getMemDC(), 200 + i * width, 190, str, strlen(str));

		sprintf_s(str, "x:%f", itemDatas[i]->getX());
		//TextOut(getMemDC(), 200 + i * width, 210, str, strlen(str));

		sprintf_s(str, "y:%f", itemDatas[i]->getY());
		//TextOut(getMemDC(), 200 + i * width, 230, str, strlen(str));

		sprintf_s(str, "길이:%d", itemDatas[i]->getWidth());
		//TextOut(getMemDC(), 200 + i * width, 250, str, strlen(str));

		sprintf_s(str, "높이:%d", itemDatas[i]->getHeight());
		//TextOut(getMemDC(), 200 + i * width, 270, str, strlen(str));

		sprintf_s(str, "RGB유무:%d", itemDatas[i]->getRGB());
		//TextOut(getMemDC(), 200 + i * width, 290, str, strlen(str));

		sprintf_s(str, "공격력:%f", itemDatas[i]->getAtk());
		//TextOut(getMemDC(), 200 + i * width, 310, str, strlen(str));

		sprintf_s(str, "방어력:%f", itemDatas[i]->getMpk());
		//TextOut(getMemDC(), 200 + i * width, 330, str, strlen(str));

		sprintf_s(str, "최대체력:%f", itemDatas[i]->getMhp());
		//TextOut(getMemDC(), 200 + i * width, 350, str, strlen(str));

		sprintf_s(str, "최대마나:%f", itemDatas[i]->getMmp());
		//TextOut(getMemDC(), 200 + i * width, 370, str, strlen(str));

		sprintf_s(str, "페이지번호:%d", itemDatas[i]->getPage());
		//TextOut(getMemDC(), 200 + i * width, 390, str, strlen(str));

		sprintf_s(str, "장착유무:%d", itemDatas[i]->getactiveFlg());
		//TextOut(getMemDC(), 200 + i * width, 410, str, strlen(str));
	}
}

void JsonDataScene::Image()
{
	int width = 50;
	for (int i = 0; i < images.size(); i++)
	{
		images[i]->render(getMemDC(), 0 + i * width, 0);
	}
}

