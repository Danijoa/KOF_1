#include "MainGame.h"
#include "Image.h"
#include "Kyo_1P.h"	
#include "Kyo_2P.h"	
#include "Iori_1P.h"	
#include "Iori_2P.h"	
#include "KimKaphwan_1P.h"	
#include "Kimkaphwan_2P.h"
#include "CommonFunction.h"
#include <WinUser.h>

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	// 메인게임의 초기화 함수
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	backGround->Init("Image/background_2.bmp", 1705, WINSIZE_Y);	// 1465 719 / 1505 719
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

	//
	whoHitted = " ";
	whoAttack = " ";
	elapsedTime = 0;

	return S_OK;
}

void MainGame::Manager1P()
{
	//1P
	switch (character_1P)
	{
	case 0:
		kyo1P->Update();

		//충돌 박스
		RectHit_1P = kyo1P->getRcHit();
		RectAttack_1P = kyo1P->getRcAttack();

		//attackValue
		character_1P_AttackValue = kyo1P->getAttackValue();
		character_1P_HP = kyo1P->getHP();

		//서로 위치가 반전시켜주기
		character_1P_posX = (kyo1P->getPosX() + kyo1P->getPosX() + 280) / 2;
		if (character_1P_posX > character_2P_posX)
			kyo1P->setSidePos(2);
		if (character_1P_posX <= character_2P_posX)
			kyo1P->setSidePos(1);

		//배경 좌우로 움직이기
		character_1P_backR = kyo1P->getBackMove_R();
		character_1P_backL = kyo1P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kyo1P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			kyo1P->setBackMove_R(FALSE);
		}
		break;
	case 1:
		iori1P->Update();

		//충돌 박스
		RectHit_1P = iori1P->getRcHit();
		RectAttack_1P = iori1P->getRcAttack();

		//attackValue
		character_1P_AttackValue = iori1P->getAttackValue();
		character_1P_HP = iori1P->getHP();

		//위치 반전
		character_1P_posX = (iori1P->getPosX() + iori1P->getPosX() + 255) / 2;
		if (character_1P_posX > character_2P_posX)
			iori1P->setSidePos(2);
		if (character_1P_posX <= character_2P_posX)
			iori1P->setSidePos(1);

		//배경
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
			if (backPos.x > -200)
				backPos.x -= 3;
			iori1P->setBackMove_R(FALSE);
		}
		break;
	case 2:
		kim1P->Update();

		//충돌 박스
		RectHit_1P = kim1P->getRcHit();
		RectAttack_1P = kim1P->getRcAttack();

		//attackValue
		character_1P_AttackValue = kim1P->getAttackValue();
		character_1P_HP = kim1P->getHP();

		//위치 반전
		character_1P_posX = (kim1P->getPosX() + kim1P->getPosX() + 230) / 2;
		if (character_1P_posX > character_2P_posX)
			kim1P->setSidePos(2);
		if (character_1P_posX <= character_2P_posX)
			kim1P->setSidePos(1);

		//배경
		character_1P_backR = kim1P->getBackMove_R();
		character_1P_backL = kim1P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kim1P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			kim1P->setBackMove_R(FALSE);
		}
		break;
	default:
		break;
	}

}

void MainGame::Manager2P()
{
	//2P
	switch (character_2P)
	{
	case 0:
		kyo2P->Update();

		//충돌
		RectHit_2P = kyo2P->getRcHit();
		RectAttack_2P = kyo2P->getRcAttack();

		//attackValue
		character_2P_AttackValue = kyo2P->getAttackValue();
		character_2P_HP = kyo2P->getHP();

		//위치 반전
		character_2P_posX = (kyo2P->getPosX() + kyo2P->getPosX() + 280) / 2;
		if (character_1P_posX > character_2P_posX)
			kyo2P->setSidePos(1);
		if (character_1P_posX <= character_2P_posX)
			kyo2P->setSidePos(2);

		//배경
		character_2P_backR = kyo2P->getBackMove_R();
		character_2P_backL = kyo2P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kyo2P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			kyo2P->setBackMove_R(FALSE);
		}
		break;
	case 1:
		iori2P->Update();

		//
		RectHit_2P = iori2P->getRcHit();
		RectAttack_2P = iori2P->getRcAttack();

		//attackValue
		character_2P_AttackValue = iori2P->getAttackValue();
		character_2P_HP = iori2P->getHP();

		character_2P_posX = (iori2P->getPosX() + iori2P->getPosX() + 255) / 2;
		if (character_1P_posX > character_2P_posX)
			iori2P->setSidePos(1);
		if (character_1P_posX <= character_2P_posX)
			iori2P->setSidePos(2);

		character_2P_backR = iori2P->getBackMove_R();
		character_2P_backL = iori2P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			iori2P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			iori2P->setBackMove_R(FALSE);
		}
		break;
	case 2:
		kim2P->Update();

		//충돌
		RectHit_2P = kim2P->getRcHit();
		RectAttack_2P = kim2P->getRcAttack();

		//attackValue
		character_2P_AttackValue = kim2P->getAttackValue();
		character_2P_HP = kim2P->getHP();

		character_2P_posX = (kim2P->getPosX() + kim2P->getPosX() + 230) / 2;
		if (character_1P_posX > character_2P_posX)
			kim2P->setSidePos(1);
		if (character_1P_posX <= character_2P_posX)
			kim2P->setSidePos(2);

		character_2P_backR = iori2P->getBackMove_R();
		character_2P_backL = iori2P->getBackMove_L();
		if (character_1P_backL || character_2P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kim2P->setBackMove_L(FALSE);
		}
		if (character_1P_backR || character_2P_backR)
		{
			if (backPos.x > -200)
				backPos.x -= 3;
			kim2P->setBackMove_R(FALSE);
		}
		break;
	default:
		break;
	}
}

void MainGame::Update()
{
	//1P
	Manager1P();

	//2P
	Manager2P();

	//배경 이동
	if (backPos.x >= -100)
	{
		if (character_1P_posX > 150 && character_2P_posX > 150)
			backPos.x -= 3;
	}
	if (backPos.x < -100)
	{
		if (character_1P_posX < WINSIZE_X - 150 && character_2P_posX < WINSIZE_X - 150)
			backPos.x += 3;
	}

	//충돌 관리 + hp 승패 관리
	if (IntersectRect(&rcTemp1, &RectHit_1P, &RectAttack_2P))	//1P가 맞고 2P가 때리고
	{
		whoHitted = "1P";
		whoAttack = "2P";
		if (elapsedTime == 0)
		{
			if(character_1P == 0)
				kyo1P->setHP(character_2P_AttackValue);
			if (character_1P == 1)
				iori1P->setHP(character_2P_AttackValue);
			if (character_1P == 2)
				kim1P->setHP(character_2P_AttackValue);
		}
		elapsedTime++;
	}
	else if (IntersectRect(&rcTemp2, &RectHit_2P, &RectAttack_1P))	//2P가 맞고 1P가 때리고
	{
		whoHitted = "2P";
		whoAttack = "1P";
		if (elapsedTime == 0)
		{
			if (character_2P == 0)
				kyo2P->setHP(character_1P_AttackValue);
			if (character_2P == 1)
				iori2P->setHP(character_1P_AttackValue);
			if (character_2P == 2)
				kim2P->setHP(character_1P_AttackValue);
		}
		elapsedTime++;
	}
	else
	{
		whoHitted = " ";
		whoAttack = " ";
		elapsedTime = 0;
	}

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

	char szText[100];
	char szText1[100];
	char szText2[100];
	char szText3[100];

	wsprintf(szText, "%s가 맞았다", whoHitted);
	TextOut(hBack, 400, 2, szText, strlen(szText));
	wsprintf(szText1, "%s 가 때렸다", whoAttack);
	TextOut(hBack, 400, 30, szText1, strlen(szText1));

	wsprintf(szText2, "1hp: %d", character_1P_HP);
	TextOut(hBack, 200, 2, szText2, strlen(szText2));
	wsprintf(szText3, "2hp: %d", character_2P_HP);
	TextOut(hBack, 700, 2, szText3, strlen(szText3));

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

	//RenderRect(hdc, RectAttack_1P.left, RectAttack_1P.top, RectAttack_1P.)

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