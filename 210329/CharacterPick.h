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

	Image* backBuffer;		//�̹��� �������� �Ѱ��� ��� ���� �� �� �ֵ��� �ϴ� �����
	Image* backGround;		//���
	Image* big_1p;			//1P ūâ ĳ���� 3��
	Image* small_1p;		//1P ����â ĳ���� 3��
	Image* big_2p;			//2P ūâ ĳ���� 3��
	Image* small_2p;		//2P ����â ĳ���� 3��

	char text1P[100], text2P[100];		//1p 2p Ȯ�ο� TEXT ���� ��
	const char* nameCheck[3];			//�̸� ���� �� �δ� �� (char, char*, const char ��ƴ�... ...)
	bool curPick;						//���� 1P 2P�� �������� �ִ� ��ġ �˻�
	int curSmall_1P,  curSmall_2P;		//����â ���° ĳ���� ����Ű�� �ִ���

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


