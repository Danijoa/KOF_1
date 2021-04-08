#include "Opening.h"
#include "Image.h"

HRESULT Opening::Init()
{
	KeyManager::GetSingleton()->Init();

	// 메인게임의 초기화 함수
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	backGround->Init("Image/openingScene.bmp", 1505, 719);

	nextScene = false;

	isInited = true;

	return S_OK;
}

void Opening::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		nextScene = true;
	}

	InvalidateRect(g_hWnd, NULL, false);
}

void Opening::Release()
{
	//KeyManager::GetSingleton()->Release();

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	backGround->Release();
	delete backGround;
	backGround = nullptr;

	//KillTimer(g_hWnd, 0);
}

void Opening::Render(HDC hdc)
{
	HDC hBack = backBuffer->GetMemDC();

	if (backGround)
		backGround->Render(hBack);
	
	backBuffer->Render(hdc);
}

LRESULT Opening::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			this->Update();
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);
		if (isInited)
		{
			this->Render(hdc);
		}
		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

Opening::Opening()
{
	isInited = false;
}

Opening::~Opening()
{
}
