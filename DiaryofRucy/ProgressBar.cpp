#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int correctionX, int correctionY, int width, int height, string imageName)
{
	_x = x;
	_y = y;
	_correctionX = correctionX;
	_correctionY = correctionY;
	_rc = RectMakeCenter(_x, _y, width, height);

	_progressBarDown = IMAGEMANAGER->findImage(imageName);
	_progressBarUp = IMAGEMANAGER->findImage(imageName);

	_width = _progressBarUp->getWidth();

	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{
	_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(),
		_progressBarDown->getHeight());
}

void ProgressBar::render(void)
{
	_progressBarDown->render(getMemDC(),
		_rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2,
		0, 0,
		_progressBarDown->getWidth(),
		_progressBarDown->getHeight());

	_progressBarUp->render(getMemDC(),
		_rc.left + _correctionX,
		_rc.top + _correctionY,
		0, 0,
		_width,
		_progressBarUp->getHeight());
}

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getWidth();
}
