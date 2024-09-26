#include "Stdafx.h"
#include "Animation.h"


Animation::Animation(void) : _frameNum(0),
_frameWidth(0),
_frameHeight(0),
_frameNumWidth(0),
_frameNumHeight(0),
_frameUpdateSec(0),
_elapsedSec(0),
_nowPlayIdx(0),
_isPlay(false),
_loop(false)
{
}


HRESULT Animation::init(int totalW, int totalH, int frameW, int frameH)
{
    //가로
    _frameWidth = frameW;
    _frameNumWidth = totalW / _frameWidth;
    //세로
    _frameHeight = frameH;
    _frameNumHeight = totalH / _frameHeight;
    //총 프레임
    _frameNum = _frameNumWidth * _frameNumHeight;

    _frameList.clear(); //오류방지

    //추가
    for (int i = 0; i < _frameNumHeight; i++)
    {
        for (int j = 0; j < _frameNumWidth; j++)
        {
            POINT framePos;
            framePos.x = j * _frameWidth;
            framePos.y = i * _frameHeight;

            _frameList.push_back(framePos);
        }
    }

    //기본세팅
    setDefPlayFrame();

    return S_OK;
}

void Animation::release(void)
{
}

//기본프레임 세팅
void Animation::setDefPlayFrame(bool reverse, bool loop)
{
    _loop = loop;
    _playList.clear();

    //너 다시 돌아오니? 
    if (reverse)
    {
        if (_loop)
        {
            //갈때
            for (int i = 0; i < _frameNum; i++)
            {
                _playList.push_back(i);
            }
            //올때
            for (int i = _frameNum - 2; i > 0; i--) //이 수치를 조정해서 자연스럽게 맞추자. 게임에따라 다름
            {
                _playList.push_back(i);
            }
        }
        else
        {   //갈때
            for (int i = 0; i < _frameNum; i++)
            {
                _playList.push_back(i);
            }
            //올때                          elapsedTime때문에 안들어오는경우가 있으니 >=로 잡아주자
            for (int i = _frameNum - 2; i >= 0; i--) //이 수치를 조정해서 자연스럽게 맞추자. 게임에따라 다름
            {
                _playList.push_back(i);
            }
        }


    }
    else
    {
        for (int i = 0; i < _frameNum; i++)
        {
            _playList.push_back(i);
        }

    }
}

//원하는 프레임(위치) 출력 가능
void Animation::setPlayFrame(int* playARR, int arrLen, bool loop)
{
    _loop = loop;
    // _playList.clear();

    if (_loop)
    {
        for (int i = 0; i < arrLen; i++)
        {
            _playList.push_back(playARR[i]);
        }

        for (int i = arrLen - 2; i > 0; i--)
        {
            _playList.push_back(playARR[i]);
        }
    }
    else
    {
        for (int i = 0; i < arrLen; i++)
        {
            _playList.push_back(playARR[i]);
        }
    }


}

//지정해준 구간만 잘라서 재생 -> S -> E
void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
    _loop = loop;
    //_playList.clear();
    if (reverse)
    {
        if (_loop)
        {
            for (int i = start; i < end; i++)
            {
                _playList.push_back(i);
            }

            for (int i = end - 2; i > start; i--)
            {
                _playList.push_back(i);
            }
        }
        else
        {
            for (int i = start; i <= end; i++)
            {
                _playList.push_back(i);
            }

            for (int i = end - 2; i > start; i--)
            {
                _playList.push_back(i);
            }
        }
    }
    else
    {
        for (int i = start; i < end; i++)
        {
            _playList.push_back(i);
        }
    }
}

void Animation::setFPS(int framePerSec)
{
    _frameUpdateSec = 1.f / framePerSec;
 
}

void Animation::frameUpdate(float elapsedTime)
{
    if (_isPlay)
    {
        _elapsedSec += elapsedTime;

        if (_elapsedSec >= _frameUpdateSec)
        {
            _elapsedSec -= _frameUpdateSec;

            _nowPlayIdx++;
            if (_nowPlayIdx == _playList.size())
            {
                if (_loop)
                {
                    _nowPlayIdx = 0;
                }
                else
                {
                    _nowPlayIdx--;
                    _isPlay = false;
                }
            }
        }
    }
}

void Animation::frameUpdate(float elapsedTime, int start)
{
    if (_isPlay)
    {
        _elapsedSec += elapsedTime;

        if (_elapsedSec >= _frameUpdateSec)
        {
            _elapsedSec -= _frameUpdateSec;

            _nowPlayIdx++;
            if (_nowPlayIdx == _playList.size())
            {
                if (_loop)
                {
                    _nowPlayIdx = start;
                }
                else
                {
                    _nowPlayIdx--;
                    _isPlay = false;
                }
            }
        }
    }
}

void Animation::AniStart(void)
{
    _isPlay = true;
    _nowPlayIdx = 0;
}

void Animation::AniStop(void)
{
    _isPlay = false;
    _nowPlayIdx = 0;
}

void Animation::AniPause(void)
{
    _isPlay = false;

}

void Animation::AniResume(void)
{
    _isPlay = true;
}