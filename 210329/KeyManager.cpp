#include "config.h"
#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	keyUp.set();	//전체 1(true) 초기화5
	keyDown.reset();

	return E_NOTIMPL;
}

void KeyManager::Release()
{
	ReleaseSingleton();
}

bool KeyManager::IsOnceKeyDown(int key)
{
	// GetAsyncKeyState(VK_...) : 함수 호출 시점에 Virtual Key의 상태를 알려줌
	// 0X0000 : 전 & 현재 누른적 없음
	// 0X0001 : 전 누른적 있음 & 현재 누른적 없음
	// 0X8000 : 전 누른적 없음 & 현재 누른적 있음 -> 0X8 2진수(bit 표현) 1000
	// 0X8001 : 전 & 현재 누른적 있음

	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!keyDown[key])
		{
			keyDown[key] = true;
			return true;
		}
	}
	else
	{
		keyDown[key] = false;
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)	//키보드 눌린게 참이라면(둘다 1일때만 참)
	{
		keyUp[key] = false;
	}
	else //키보드가 up 인 상태면
	{
		if (!keyUp[key])
		{
			keyUp[key] = true;
		    return true;
		}
	}
	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)	//참이라면
	{
		return true;
	}
	return false;
}
