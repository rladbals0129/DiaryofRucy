#pragma once
#include "GameNode.h"


class ProgressBar : public GameNode
{
private:
	GImage* _progressBarUp;
	GImage* _progressBarDown;

	RECT _rc;
	int _x, _y;
	int _correctionX, _correctionY;
	float _width;

public:
	HRESULT init(int x, int y, int correctionX, int correctionY, int width, int height, string imageName);
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentScore, float maxScore);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	ProgressBar() {}
	virtual ~ProgressBar() {}
};