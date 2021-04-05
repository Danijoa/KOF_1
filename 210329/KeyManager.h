#pragma once;
#include "Singleton.h"
#define MAX_KEY_COUNT 256
using namespace std;
//자료구조

class KeyManager :public Singleton<KeyManager>
{
private:
	bitset<MAX_KEY_COUNT> keyUp;	//우린 키 입력을 얻을 것이니까: bitSet<키 개수>
	bitset<MAX_KEY_COUNT> keyDown;

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	//처음 down 판단해주는 함수
	bool IsOnceKeyUp(int key);	//해당 키가 처음 down 후 up 되었는지
	bool IsStayKeyDown(int key);	//키가 down 상태인지

	void SetKeyDown(int key, bool state) { this->keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { this->keyUp.set(key, state); }
};
