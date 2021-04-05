#include "config.h"
#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	keyUp.set();	//��ü 1(true) �ʱ�ȭ5
	keyDown.reset();

	return E_NOTIMPL;
}

void KeyManager::Release()
{
	ReleaseSingleton();
}

bool KeyManager::IsOnceKeyDown(int key)
{
	// GetAsyncKeyState(VK_...) : �Լ� ȣ�� ������ Virtual Key�� ���¸� �˷���
	// 0X0000 : �� & ���� ������ ����
	// 0X0001 : �� ������ ���� & ���� ������ ����
	// 0X8000 : �� ������ ���� & ���� ������ ���� -> 0X8 2����(bit ǥ��) 1000
	// 0X8001 : �� & ���� ������ ����

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
	if (GetAsyncKeyState(key) & 0x8000)	//Ű���� ������ ���̶��(�Ѵ� 1�϶��� ��)
	{
		keyUp[key] = false;
	}
	else //Ű���尡 up �� ���¸�
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
	if (GetAsyncKeyState(key) & 0x8000)	//���̶��
	{
		return true;
	}
	return false;
}
