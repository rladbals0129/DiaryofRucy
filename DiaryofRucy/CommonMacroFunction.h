#pragma once
// CommonMacroFunction

template <typename InterFaceType>
inline void SafeRelease(InterFaceType** currentScene)
{
	if (*currentScene != nullptr)
	{
		(*currentScene)->Release();
		*currentScene = nullptr;
	}
}

template <typename InterFaceType>
inline InterFaceType* safeAcquire(InterFaceType* newObject)
{
	if (newObject != nullptr)
	{
		//너희가 붙히고 싶은 함수
		newObject->AddRef();
	}
	return newObject;
}

// 새로운 객체를 붙일떄 이전 객체를 해제
template <typename InterFaceType>
inline void SafeSet(InterFaceType** currentObject, InterFaceType* newObject)
{
	safeAcquire(newObject);
	SafeRelease(&currentObject);
	currentObject = newObject;
}

//점찍기
inline POINT PointMake(int x, int y) // 2D방향 벡터
{
	POINT pt = { x, y };
	return pt;
}

inline POINTF PointFloatMake(float x, float y)
{
	POINTF pt = { x,y };
	return pt;
}
//줄긋기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}
//사각형 만들어서 보내기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}
//사각형 그리기 (렉트를 이용해서 그림)
inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
// 중앙에 사각형 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}
//사각형 그리기 (좌표와 사이즈를 직접 넣어서 그림)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}


// 원 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
// 센터에 원 만들기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}


inline void moveRect(RECT rc, POINT pt, int size, int clickX, int clickY)
{
	 rc.left = pt.x - clickX;
	 rc.top = pt.y - clickY;
	 rc.right = rc.left + size;
	 rc.bottom = rc.top + size;

}

// 충돌 영역 리사이징
inline RECT CollisionAreaResizing(RECT rcDest, int width, int height)
{
	RECT rc =
	{
		rcDest.left + width / 2, rcDest.top + height / 2, rcDest.right - width / 2, rcDest.bottom - height / 2
	};

	return rc;
}

inline RECT rucyCollisionAreaResizing(RECT rcDest, int width, int height)
{
	RECT rc =
	{
		rcDest.left + width / 2, rcDest.top + height / 2 +20, rcDest.right - width / 2, rcDest.bottom - height / 2 +20
	};

	return rc;
}
