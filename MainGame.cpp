#include "MainGame.h"
#include "Image.h"
#include "Kyo_1P.h"	
#include "Kyo_2P.h"	
#include "Iori_1P.h"	
#include "Iori_2P.h"	
#include "KimKaphwan_1P.h"	
#include "Kimkaphwan_2P.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	// 메인게임의 초기화 함수
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	backGround->Init("Image/background_2.bmp", 1705, WINSIZE_Y);	//1465 719 / 1505 719
	backPos.x = -100;
	backPos.y = 0;

	kyo1P = new Kyo_1P();
	kyo1P->Init();

	kyo2P = new Kyo_2P();
	kyo2P->Init();

	iori1P = new Iori_1P();
	iori1P->Init();

	iori2P = new Iori_2P();
	iori2P->Init();

	kim1P = new KimKaphwan_1P();
	kim1P->Init();

	kim2P = new KimKaphwan_2P();
	kim2P->Init();

	isInited = true;

	return S_OK;
}

void MainGame::Update()
{
	switch (character_1P)
	{
	case 0:
		kyo1P->Update();

		character_1P_posX = kyo1P->getPosX();
		if (character_1P_posX > character_2P_posX)		//서로 위치가 반전시켜주기
			kyo1P->setSidePos(2);
		if (character_1P_posX <= character_2P_posX)
			kyo1P->setSidePos(1);

		character_1P_backR = kyo1P->getBackMove_R();	//배경 좌우로 움직이기
		character_1P_backL = kyo1P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			kyo1P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kyo1P->setBackMove_R(FALSE);
		}
		break;
	case 1:
		iori1P->Update();

		character_1P_posX = iori1P->getPosX();
		if (character_1P_posX > character_2P_posX)
			iori1P->setSidePos(2);
		if (character_1P_posX <= character_2P_posX)
			iori1P->setSidePos(1);

		character_1P_backR = iori1P->getBackMove_R();
		character_1P_backL = iori1P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			iori1P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			iori1P->setBackMove_R(FALSE);
		}
		break;
	case 2:
		kim1P->Update();

		character_1P_posX = kim1P->getPosX();
		if (character_1P_posX > character_2P_posX)
			kim1P->setSidePos(2);
		if (character_1P_posX <= character_2P_posX)
			kim1P->setSidePos(1);

		character_1P_backR = kim1P->getBackMove_R();
		character_1P_backL = kim1P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			kim1P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kim1P->setBackMove_R(FALSE);
		}
		break;
	default:
		break;
	}

	switch (character_2P)
	{
	case 0:
		kyo2P->Update();

		character_2P_posX = kyo2P->getPosX();
		if (character_1P_posX > character_2P_posX)
			kyo2P->setSidePos(1);
		if (character_1P_posX <= character_2P_posX)
			kyo2P->setSidePos(2);

		character_2P_backR = kyo2P->getBackMove_R();
		character_2P_backL = kyo2P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			kyo2P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kyo2P->setBackMove_R(FALSE);
		}
		break;
	case 1:
		iori2P->Update();

		character_2P_posX = iori2P->getPosX();
		if (character_1P_posX > character_2P_posX)
			iori2P->setSidePos(1);
		if (character_1P_posX <= character_2P_posX)
			iori2P->setSidePos(2);

		character_2P_backR = iori2P->getBackMove_R();
		character_2P_backL = iori2P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			iori2P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			iori2P->setBackMove_R(FALSE);
		}
		break;
	case 2:
		kim2P->Update();

		character_2P_posX = kim2P->getPosX();
		if (character_1P_posX > character_2P_posX)
			kim2P->setSidePos(1);
		if (character_1P_posX <= character_2P_posX)
			kim2P->setSidePos(2);

		character_2P_backR = iori2P->getBackMove_R();
		character_2P_backL = iori2P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			kim2P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kim2P->setBackMove_R(FALSE);
		}
		break;
	default:
		break;
	}

	//배경 이동
	if (backPos.x >= -100)
	{
		if (character_1P_posX < WINSIZE_X - 150 && character_2P_posX < WINSIZE_X - 150) 
			backPos.x -= 3;
		if (character_1P_posX > WINSIZE_X - 150 && character_2P_posX > WINSIZE_X - 150)
			backPos.x -= 3;
	}
	if (backPos.x < -100)
	{
		if (character_1P_posX > 150 && character_2P_posX > 150)
			backPos.x += 3;
		if (character_1P_posX < 150 && character_2P_posX < 150)
			backPos.x += 3;
	}

	//충돌 관리

	//hp 승패 관리

	InvalidateRect(g_hWnd, NULL, false);
}


void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();

	backBuffer->Release();
	delete backBuffer;
	backBuffer = nullptr;

	backGround->Release();
	delete backGround;
	backGround = nullptr;

	if (kyo1P)
	{
		kyo1P->Release();
		delete kyo1P;
		kyo1P = nullptr;
	}

	if (kyo2P)
	{
		kyo2P->Release();
		delete kyo2P;
		kyo2P = nullptr;
	}

	if (iori1P)
	{
		iori1P->Release();
		delete iori1P;
		iori1P = nullptr;
	}

	if (iori2P)
	{
		iori2P->Release();
		delete iori2P;
		iori2P = nullptr;
	}

	if (kim1P)
	{
		kim1P->Release();
		delete kim1P;
		kim1P = nullptr;
	}

	if (kim2P)
	{
		kim2P->Release();
		delete kim2P;
		kim2P = nullptr;
	}

	KillTimer(g_hWnd, 0);
}

void MainGame::Render(HDC hdc)
{
	HDC hBack = backBuffer->GetMemDC();

	if (backGround)
		backGround->Render(hBack, backPos.x, backPos.y);	//hdc 그릴 시작 좌표

	switch (character_1P)
	{
	case 0:
		kyo1P->Render(hBack);
		break;
	case 1:
		iori1P->Render(hBack);
		break;
	case 2:
		kim1P->Render(hBack);
		break;
	default:
		break;
	}

	switch (character_2P)
	{
	case 0:
		kyo2P->Render(hBack);
		break;
	case 1:
		iori2P->Render(hBack);
		break;
	case 2:
		kim2P->Render(hBack);
		break;
	default:
		break;
	}

	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}