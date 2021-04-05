#pragma once;
#include "Singleton.h"
#define MAX_KEY_COUNT 256
using namespace std;
//�ڷᱸ��

class KeyManager :public Singleton<KeyManager>
{
private:
	bitset<MAX_KEY_COUNT> keyUp;	//�츰 Ű �Է��� ���� ���̴ϱ�: bitSet<Ű ����>
	bitset<MAX_KEY_COUNT> keyDown;

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	//ó�� down �Ǵ����ִ� �Լ�
	bool IsOnceKeyUp(int key);	//�ش� Ű�� ó�� down �� up �Ǿ�����
	bool IsStayKeyDown(int key);	//Ű�� down ��������

	void SetKeyDown(int key, bool state) { this->keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { this->keyUp.set(key, state); }
};
