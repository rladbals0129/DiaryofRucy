#include "Stdafx.h"
#include "Utils.h"


namespace MY_UTIL
{
	// 두 점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	// 스타트 -> 엔드 -> 각을 라디안으로
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x * x + y * y);

		float angle = acos(x / d);

		if (y > 0) angle = PI_2 - angle;

		return angle;
	}


	// 기준 수로부터 일정 거리 안에 수가 있는지 확인하는 함수
	bool getAbsRange(float reference, float range, float comparison)
	{
		if (reference - range <= comparison  && comparison <= reference + range)
		{
			return true;
		}
		return false;
	}

}


namespace OBB_COLLISION
{

	double absDotVector(VECTOR a, VECTOR b) 
	{
		return abs(a.x * b.x + a.y * b.y);
	}

	// 두 사각형의 중심간 거리 벡터 계산 함수
	VECTOR getDistanceVector(SHAPE a, SHAPE b) 
	{
		VECTOR ret;
		ret.x = (a.left + a.width / 2) - (b.left + b.width / 2);
		ret.y = (a.top + a.height / 2) - (b.top + b.height / 2);
		return ret;
	}

	// 사각형의 높이 벡터 계산 함수
	VECTOR getHeightVector(SHAPE s) 
	{
		VECTOR ret;

		ret.x = s.height * cos(static_cast<float>(s.rot + PI / 2)) / 2;
		ret.y = -s.height * sin(static_cast<float>(s.rot + PI / 2)) / 2;

		return ret;
	}

	// 사각형의 너비 벡터 계산 함수
	VECTOR getWidthVector(SHAPE s) 
	{
		VECTOR ret;

		ret.x = s.width * cos(static_cast<float>(s.rot)) / 2;
		ret.y = -s.width * sin(static_cast<float>(s.rot)) / 2;

		return ret;
	}

	// 단위벡터 계산 함수: 각 요소를 크기로 나눔으로써 얻음.
	VECTOR getUnitVector(VECTOR a) 
	{
		VECTOR ret;
		double size;

		size = sqrt(pow(a.x, 2) + pow(a.y, 2));
		ret.x = a.x / size;
		ret.y = a.y / size;

		return ret;
	}

	// RECT 구조체를 SHAPE 구조체로 변환하는 함수.
	SHAPE rectToShape(RECT rc1, float radian1) 
	{
		SHAPE tempShape;

		tempShape.top = rc1.top;
		tempShape.left = rc1.left;
		tempShape.width = (double)(rc1.right - rc1.left);
		tempShape.height = (double)(rc1.bottom - rc1.top);
		tempShape.rot = radian1;

		return tempShape;
	}

	bool isOBBCollision(RECT rc1, float radian1, RECT rc2, float radian2)
	{
		SHAPE shapeA = rectToShape(rc1, radian1);
		SHAPE shapeB = rectToShape(rc2, radian2);

		VECTOR dist = getDistanceVector(shapeA, shapeB);
		VECTOR vec[4] = { getHeightVector(shapeA),getHeightVector(shapeB),getWidthVector(shapeA),getWidthVector(shapeB) };

		VECTOR unit;
		for (int i = 0; i < 4; i++) 
		{
			double sum = 0;
			unit = getUnitVector(vec[i]);
			for (int j = 0; j < 4; j++) 
			{
				sum += absDotVector(vec[j], unit);
			}
			if (absDotVector(dist, unit) > sum)
			{
				return false;
			}
		}
		return true;
	}


	void OBBDrawRotatedRect(HDC hdc, RECT rc, float radian)
	{
		// 변환 매트릭스 초기화
		XFORM xForm;
		xForm.eM11 = (FLOAT)cos(radian);
		xForm.eM12 = (FLOAT)sin(radian);
		xForm.eM21 = (FLOAT)-sin(radian);
		xForm.eM22 = (FLOAT)cos(radian);

		// 중심점으로 이동
		int centerX = (rc.right + rc.left) / 2;
		int centerY = (rc.bottom + rc.top) / 2;

		xForm.eDx = (FLOAT)centerX;
		xForm.eDy = (FLOAT)centerY;

		// 원점 주위로 회전 후 다시 중심점으로 돌아오기
		SetGraphicsMode(hdc, GM_ADVANCED);
		SetWorldTransform(hdc, &xForm);

		Rectangle(hdc, rc.left - centerX, rc.top - centerY,
			rc.right - centerX, rc.bottom - centerY);

		// 원래의 그래픽 모드로 복원
		xForm.eM11 = 1.0f;
		xForm.eM12 = 0.0f;
		xForm.eM21 = 0.0f;
		xForm.eM22 = 1.0f;
		xForm.eDx = 0.0f;
		xForm.eDy = 0.0f;

		SetWorldTransform(hdc, &xForm);
		SetGraphicsMode(hdc, GM_COMPATIBLE);
	}
	

}