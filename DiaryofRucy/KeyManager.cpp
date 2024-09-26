#include "KeyManager.h"

HRESULT KeyManager::init(void)
{
    // 키 값을 전부눌려있지 않은 상태로 초기화
    for (int i = 0; i < KEY_MAX; i++)
    {
        this->setKeyUp(i, false);
        this->setKeyDown(i, false);
    }
    return S_OK;
    // bool b[20] = { true };  이거 트루로 초기화 안댐
    // bool b[20] = { false };  이거 는 댐
}

bool KeyManager::isOnceKeyDown(int key)
{

    /*    
    ▶ GetAsyncKeyState

     - 어떤 키가 입력된건지 체크 / 프로그램에서 키를 입력받고 싶을 때 사용하는 API공용 함수

     - 기본적으로 메세지 큐에 있는 키의 정보를 확인 한다.

     - 키가 눌린 시점을 체크하기 위해 &(AND) 연산을 사용해서 확인한다.

     0X0000 누른적 x 호출시점에 안눌림
     0X0001 누른적 o 호출시점에 안눌림
     0X8000 누른적 x 호출시점에 눌림
     0X8001 누른적 o 호출시점에 눌림
    */

    // 비트단위로 AND 연산을 한다.
    //  ㄴ 둘다 1일 때만 결과가 1이고 / 아니라면 결과가 0

    if (GetAsyncKeyState(key) & 0x8000)
    {
        if (!this->getKeyDown()[key])
        {
            this->setKeyDown(key, true);
            return true;
        }
    }
    else
    {
        this->setKeyDown(key, false);
    }
    return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
    if(GetAsyncKeyState(key) & 0x8000)
    {
        this->setKeyUp(key, true);
    }
    else
    {
        if (this->getKeyUp()[key])
        {
            this->setKeyUp(key, false);
            return true;
        }
    }
    return false;
}

bool KeyManager::isStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        return true;
    }
    return false;
}

bool KeyManager::isToggleKey(int key)
{
    if (GetKeyState(key) & 0x0001)
    {
        return true;
    }
    return false;
}

bool KeyManager::checkMoveKeyDown(int key1, int key2, int key3, int key4)
{
    if (!isStayKeyDown(key1))
    {
        if (!isStayKeyDown(key2))
        {
            if (!isStayKeyDown(key3))
            {
                if (!isStayKeyDown(key4))
                {
                    return true;
                }
            }
        }
    }
    return false;

}
