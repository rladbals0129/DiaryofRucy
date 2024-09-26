#pragma once
#include "GameNode.h"

class TeamReport : public GameNode
{
private:
	RECT rc1;
	RECT rc2;
	struct tagText
	{
		string _str;
		int _x, _y;

		tagText(int x, int y, const string& str)
		{
			_x = x;
			_y = y;
			_str = str;
		}
	};

private:
	D2DImageInfo* _img;
	D2DImageInfo* _img2;
	D2DImageInfo* _img3;
	vector<tagText> _vXpoint;
	bool _switch;
	int _initNum;

	int _curFrameX;
	int _curFrameY;
	float testAngle;
	int _curFrameX2;
	int _curFrameY2;

	int _curFrameX3;
	int _curFrameY3;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	TeamReport() {}
	~TeamReport() {}
};