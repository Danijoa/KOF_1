#pragma once
#include "GameNode.h"
#include <string>

class Image;

class CharacterPick : public GameNode
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;

	RECT *shape1P;			
	RECT* shape2P;

	RECT* select_1p;
	RECT* select_2p;
	HPEN Pen, OldPen;

	Image* backBuffer;		//이미지 정보들을 한곳에 담아 보내 줄 수 있도록 하는 백버퍼
	Image* backGround;		//배경
	Image* big_1p;			//1P 큰창 캐릭터 3개
	Image* small_1p;		//1P 작은창 캐릭터 3개
	Image* big_2p;			//2P 큰창 캐릭터 3개
	Image* small_2p;		//2P 작은창 캐릭터 3개

	char text1P[100], text2P[100];		//1p 2p 확인용 TEXT 담을 곳
	const char* nameCheck[3];			//이름 저장 해 두는 곳 (char, char*, const char 어렵다... ...)
	bool curPick;						//현재 1P 2P가 가리리고 있는 위치 검사
	int curSmall_1P,  curSmall_2P;		//작은창 몇번째 캐릭터 가리키고 있는지

	bool nextScene;

public:
	HRESULT Init();	
	void Update();
	void Release();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	inline bool getNext() { return nextScene; }
	inline int get1P() { return curSmall_1P; }
	inline int get2P() { return curSmall_2P; }

	CharacterPick();
	~CharacterPick();
};


