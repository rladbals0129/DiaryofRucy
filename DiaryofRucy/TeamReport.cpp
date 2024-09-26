#include "Stdafx.h"
#include "TeamReport.h"


HRESULT TeamReport::init(void)
{
	//_obb = new OBBCollision;
	_switch = false;
	_initNum = 0;
	const vector<string> tempStr = {
	"이호준 : 시작",
	"김유민 : 뭘 시작하시나요?" ,
	"박성한 : 나도낄래",
	"박성한 : 싫어 안할래", 
	"이호준 : 사실 이편지는 영국에서 시작되어",
	"박성한 :  그만 하십쇼 형님",
	"김유민 : ㅎ",
	"신혜빈 : 하이염 하이염",
	"신혜빈 : 치킨이 좋아요",
	"박성한 : 떙겨~~~~~~~~일ㄹㄹㄹㄹㄹㄹㄹㄹㄹㄹㄹㄹ햐!!!",
	"신혜빈 : 치킨이 싫어요",
	"신혜빈 : 치킨이 좋아요",
	"김유민 : 무료 배달이라더니... 햄버거 가격 눈속임",
	"박성한 : 아 밥 떙긴다 떙겨어어어어어어어잇!!",
	"박성한 : 아 밥 뭐드실???",
	"김유민 : 하나둘셋 하면 태양식당에서 뭐먹을지 적기",
	"김유민 : 나는 매운꼼장어볶음",
	"신혜빈 : ㅎㅇㅎㅇㅎㅇ요",
	"이호준 : 제발... 잘 좀 하자...",
	"박성한 : 히히 텍스트 발싸",
	"박성한 : 두줄이라니... 마스터 이렇게라도 하지 않으면..."
	"김유민 : 마스터에서 작업을 해야되는거구나..",
	"김유민 : 다른분기 누르고 작업했었네요",
	"신혜빈 : 저는 오늘 저녁을 굶겠습니다",
	"신혜빈 : 왜냐면 음료를 먹을거거든요",
	"이호준 : 어 그래 애들아 밥 맛있게 먹었니",
	"이호준 : 이러다 나 죽어~~",

	 /*여기에 이어서 추가할 것*/};

	_curFrameX2 = 2;
	_curFrameY2 = 1;

	_curFrameX3 = 3;
	_curFrameY3 = 2;
	//_img->init(getMemDC());

	_img= D2DMANAGER->loadImageD2D("임시", L"Resources/Images/Effect/60FPS_AC3T026_Nova_02.png",
		960, 3840,5,20);
	////_img = D2DMANAGER->addFrameImage(getMemDC(),"임시", L"Resources/Images/Effect/60FPS_AC3T026_Nova_02.png",
	////	960, 3840, 5, 20);
	////
	//_img2=D2DMANAGER->loadImageD2D("임시2", L"Resources/Images/Effect/60FPS_ACQ021_Fire.png",
	//	960, 3840,5,20);

	//_img3=D2DMANAGER->loadImageD2D("임시3", L"Resources/Images/Effect/60FPS_AC3T018_Tempest_02.png",
	//	960, 3840);

	//D2DMANAGER->loadImageD2D("테스트다", L"Resources/Images/test/actor1.png", 60, 60);

	testAngle = 0;
	for (int i = 0; i < tempStr.size(); i++)
	{
		int x, y;
		if (!_switch)
		{
			x = i * 40;
			y = i * 30;
		}
		else
		{		
			x = WINSIZE_X-((i- _initNum) * 40) - 100;
			y = (i - _initNum) * 30;
		}
		if (y >= WINSIZE_Y - 80)
		{
			_switch = true;
			// 텍스트가 y가 winsizeY까지 왔을 때 위로초기화 시켜주는 변수
			_initNum = i;
			
		}
		_vXpoint.emplace_back(x, y, tempStr[i]);
	}

	rc1 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 300, 100);
	rc2 = RectMakeCenter(WINSIZE_X / 2-100, WINSIZE_Y / 2-200, 300, 100);

	return S_OK;
}

void TeamReport::release(void)
{
	/*SAFE_DELETE(_img);
	SAFE_DELETE(_img2);
	SAFE_DELETE(_img3);*/
}

void TeamReport::update(void)
{
	
	if(KEYMANAGER->isStayKeyDown(VK_RIGHT)) testAngle++;
	if(KEYMANAGER->isStayKeyDown(VK_LEFT)) testAngle--;

	//cout << testAngle << endl;

}

void TeamReport::render(void)
{
	//for (const auto& textPrint : _vXpoint)
	//{
	//	FONTMANAGER->drawText(getMemDC(), textPrint._x, textPrint._y, (char*)textPrint._str.c_str());
	//}
	// 
	DrawRectMake(getMemDC(), rc1);
	//DrawRectMake(getMemDC(), rc2);
	
	//if (_obb->isOBBCollision(rc1, 0, rc2, testAngle))
	//{
	//	cout << "된거니?" << endl;
	//}
	//else
	//{
	//	cout << "안된거니?" << endl;

	//}

	//_obb->drawRotatedRect(getMemDC(), rc2, DEGREE_RADIAN(testAngle));
	//if (_obb->isOBBCollision(rc1, 0, rc2, DEGREE_RADIAN(testAngle)))
	//{
	//	cout << testAngle << endl;
	//	cout << "충돌" << endl;
	//	FONTMANAGER->drawText(getMemDC(), WINSIZE_X/2  + 200, WINSIZE_Y / 2, "충돌");
	//}

	OBBDrawRotatedRect(getMemDC(), rc2, DEGREE_RADIAN(testAngle));
	if (isOBBCollision(rc1, 0, rc2, DEGREE_RADIAN(testAngle)))
	{
		cout << testAngle << endl;
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X / 2 + 200, WINSIZE_Y / 2, "충돌",30, 600, RGB(0,0,0));
	}

}


void TeamReport::d2drender(void)
{

	//_curFrameX++;
	//if (_img->maxFrameX < _curFrameX)
	//{
	//	_curFrameX = 0;
	//	_curFrameY++;
	//	if (_img->maxFrameY < _curFrameY)
	//	{
	//		_curFrameX = 0;
	//		_curFrameY = 0;
	//	}
	//}
	//D2DMANAGER->alphaRender("임시2", 0, 0,WINSIZE_X,WINSIZE_Y, 0.5f);
	////D2DMANAGER->frameAlphaRender("임시",0,0,_curFrameX,_curFrameY,WINSIZE_X,WINSIZE_Y,0.5f);
	//D2DMANAGER->frameRotateRender("임시",0,0,_curFrameX,_curFrameY,WINSIZE_X,WINSIZE_Y,testAngle);
	//
	//D2DMANAGER->rotateRender("테스트다", WINSIZE_X/ 2, WINSIZE_Y / 2, testAngle, 1.f);
	//_curFrameX2++;
	//if (_img2->maxFrameX < _curFrameX2)
	//{
	//	_curFrameX2 = 0;
	//	_curFrameY2++;
	//	if (_img2->maxFrameY < _curFrameY2)
	//	{
	//		_curFrameX2 = 0;
	//		_curFrameY2 = 0;
	//	}
	//}
	//D2DMANAGER->frameAlphaRender("임시2", 0, 0, _curFrameX2, _curFrameY2, WINSIZE_X, WINSIZE_Y,0.5f);


	////_curFrameX3++;
	//if (_img3->maxFrameX < _curFrameX3)
	//{
	//	_curFrameX3 = 0;
	//	_curFrameY3++;
	//	if (_img3->maxFrameY < _curFrameY3)
	//	{
	//		_curFrameX3 = 0;
	//		_curFrameY3 = 0;
	//	}
	//}
	//D2DMANAGER->frameRender("임시3", 0, 0, _curFrameX3, _curFrameY3, WINSIZE_X, WINSIZE_Y);

}
