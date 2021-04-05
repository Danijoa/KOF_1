#pragma once
#include "GameNode.h"

class Image;

class Opening : public GameNode
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;

	Image* backBuffer;
	Image* backGround;

	bool nextScene;

public:
	HRESULT Init();		// 오버라이딩 (상속관계에서 쓰임)
	void Update();
	void Release();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	inline bool getNext() { return nextScene; }

	Opening();
	~Opening();
};

