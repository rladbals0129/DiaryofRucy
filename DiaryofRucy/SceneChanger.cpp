#include "Stdafx.h"
#include "SceneChanger.h"
HRESULT SceneChanger::init(void)
{
	for (int i = 0; i < Eindex::ENDGAME; i++)
	{
		_index[i]._rc = RectMakeCenter(100 + i % 4 *150, 100 + i / 4 * 50, 150, 50);
	}

	// 여기에 씬 박스 추가 ▼
	
	 wsprintf(_index[Eindex::REPORT]._name,"팀 과제 x");
	 wsprintf(_index[Eindex::OPENING]._name, "오프닝");
	 wsprintf(_index[Eindex::STAGE]._name,"스테이지");
	 wsprintf(_index[Eindex::GAMEOVER]._name,"게임오버");
	 wsprintf(_index[Eindex::ENDING]._name,"엔딩");
	 wsprintf(_index[Eindex::LOADING]._name,"로딩");
	 wsprintf(_index[Eindex::JSON]._name, "json");

	 SOUNDMANAGER->stop("opening");
	 SOUNDMANAGER->stop("liebestraum_short");
	 SOUNDMANAGER->stop("die");

	// 여기에 씬 박스 추가 ▲
	return S_OK;
}

void SceneChanger::release(void)
{

} 

void SceneChanger::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < Eindex::ENDGAME; i++)
		{
			if (PtInRect(&_index[i]._rc, _ptMouse))
			{
				switch (i)
				{
				
				case Eindex::REPORT:
					SCENEMANAGER->chanegeScene("x자과제씬");
					break;

				case Eindex::OPENING:
					SCENEMANAGER->chanegeScene("오프닝씬");
					break;

				case Eindex::STAGE:
					SCENEMANAGER->chanegeScene("스테이지씬");
					break;

				case Eindex::GAMEOVER:
					SCENEMANAGER->chanegeScene("게임오버씬");
					break;
				case Eindex::ENDING:
					SCENEMANAGER->chanegeScene("엔딩씬");
					break;

				case Eindex::LOADING:
					SCENEMANAGER->chanegeScene("로딩씬");
					break;
				case Eindex::JSON:
					SCENEMANAGER->chanegeScene("json1");
					break;
				default:

					break;
				}
			}
		}
	}

	
}

void SceneChanger::render(void)
{
	SetTextAlign(getMemDC(), TA_CENTER);
	for (int i = 0; i < Eindex::ENDGAME; i++)
	{
		DrawRectMake(getMemDC(), _index[i]._rc);
		TextOut(getMemDC(), _index[i]._rc.left + (_index[i]._rc.right - _index[i]._rc.left) / 2,
			_index[i]._rc.top + 13, _index[i]._name, strlen(_index[i]._name));
	}
	SetTextAlign(getMemDC(), TA_LEFT);
}
