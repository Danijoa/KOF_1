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
	//키입력 기능 불러오기
	KeyManager::GetSingleton()->Init();

	// 메인게임의 초기화 함수
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	//백버퍼 만들어주기
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	//배경
	backGround = new Image();
	backGround->Init("Image/background_new2.bmp", 44520, WINSIZE_Y, 19, 1);	// 44520 719 / 1505 719 (19개)
	backPos.x = -400;
	backPos.y = 0;
	backgroundCount = 0;
	backgroundFrame = 0;

	//캐릭터 미리 init 시키기(이게 맞는지... -> 아니다 KOF_Character만 헤더에 추가해 주고 다형성을 사용하자)
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

	//격투
	//whoHitted = " ";	//확인용 변수
	//whoAttack = " ";	//확인용 변수
	elapsedTime = 0;

	//상단 hp바
	sizeX1P = 459;
	sizeX2P = 459;
	barPosX = 166;
	hpBar = new Image();
	if (FAILED(hpBar->Init("Image/ui_bar.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "바 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}
	hp1PBar = new Image();
	if (FAILED(hp1PBar->Init("Image/only_hpbar.bmp", sizeX1P, 25, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "바 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}
	hp2PBar = new Image();
	if (FAILED(hp2PBar->Init("Image/only_hpbar.bmp", sizeX2P, 25, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "바 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	//타이머
	timerCount = 0;
	timeFrame = 0;
	timer = new Image();
	if (FAILED(timer->Init("Image/timer.bmp", 18300 / 2, 192 / 2, 61, 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "타이머 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	//게임 종료
	checkGameOver = false;
	gameOver = new Image();
	if (FAILED(gameOver->Init("Image/gameover.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "게임 오버 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	//init 확인
	isInited = true;

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
		if (character_1P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kyo1P->setBackMove_L(FALSE);
		}
		if (character_1P_backR)
		{
			if (backPos.x > -800)
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
		if (character_1P_backL)
		{
			if (backPos.x < 0)
				backPos.x -= 3;
			iori1P->setBackMove_L(FALSE);
		}
		if (character_1P_backR)
		{
			if (backPos.x > -800)
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
		if (character_1P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kim1P->setBackMove_L(FALSE);
		}
		if (character_1P_backR)
		{
			if (backPos.x > -800)
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
		if (character_2P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kyo2P->setBackMove_L(FALSE);
		}
		if (character_2P_backR)
		{
			if (backPos.x > -800)
				backPos.x -= 3;
			kyo2P->setBackMove_R(FALSE);
		}
		break;
	case 1:
		iori2P->Update();

		//충돌
		RectHit_2P = iori2P->getRcHit();
		RectAttack_2P = iori2P->getRcAttack();

		//attackValue
		character_2P_AttackValue = iori2P->getAttackValue();
		character_2P_HP = iori2P->getHP();

		//위치반전
		character_2P_posX = (iori2P->getPosX() + iori2P->getPosX() + 255) / 2;
		if (character_1P_posX > character_2P_posX)
			iori2P->setSidePos(1);
		if (character_1P_posX <= character_2P_posX)
			iori2P->setSidePos(2);

		//배경 좌우 이동
		character_2P_backR = iori2P->getBackMove_R();
		character_2P_backL = iori2P->getBackMove_L();
		if (character_2P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			iori2P->setBackMove_L(FALSE);
		}
		if (character_2P_backR)
		{
			if (backPos.x > -800)
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

		//위치 반전
		character_2P_posX = (kim2P->getPosX() + kim2P->getPosX() + 230) / 2;
		if (character_1P_posX > character_2P_posX)
			kim2P->setSidePos(1);
		if (character_1P_posX <= character_2P_posX)
			kim2P->setSidePos(2);

		//배경 좌우 이동
		character_2P_backR = kim2P->getBackMove_R();
		character_2P_backL = kim2P->getBackMove_L();
		if (character_2P_backL)
		{
			if (backPos.x < 0)
				backPos.x += 3;
			kim2P->setBackMove_L(FALSE);
		}
		if (character_2P_backR)
		{
			if (backPos.x > -800)
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
	//배경
	backgroundCount++;
	if (backgroundCount >= 9)
	{
		backgroundFrame = (backgroundFrame + 1) % 20;
		backgroundCount = 0;
	}

	//타이머
	timerCount++;
	if (timerCount >= 70)
	{
		timeFrame++;
		timerCount = 0;
	}

	//1P
	Manager1P();

	//2P
	Manager2P();

	//캐릭터가 중앙에 올 때 배경도 다시 중앙으로
	if (backPos.x >= -400)
	{
		if (character_1P_posX > 150 && character_2P_posX > 150)
			backPos.x -= 3;
	}
	if (backPos.x < -400)
	{
		if (character_1P_posX + 250 < WINSIZE_X - 150 && character_2P_posX + 250 < WINSIZE_X - 150)
			backPos.x += 3;
	}

	//충돌 관리 + hp 승패 관리
	if (IntersectRect(&rcTemp1, &RectHit_1P, &RectAttack_2P))	//1P가 맞고 2P가 때리고
	{
		whoHitted = "1P";
		whoAttack = "2P";
		if (elapsedTime == 0)
		{
			//1Php 줄기
			barPosX += character_2P_AttackValue * 5;
			sizeX1P -= character_2P_AttackValue * 5;

			if (character_1P == 0)
			{
				kyo1P->setHP(character_2P_AttackValue);
				kyo1P->SetHitCheck(true);
			}
			if (character_1P == 1)
			{
				iori1P->setHP(character_2P_AttackValue);
				iori1P->SetHitCheck(true);
			}
			if (character_1P == 2)
			{
				kim1P->setHP(character_2P_AttackValue);
				kim1P->SetHitCheck(true);
			}
		}
		elapsedTime++;
	}
	else if (IntersectRect(&rcTemp2, &RectHit_2P, &RectAttack_1P))	//2P가 맞고 1P가 때리고
	{
		whoHitted = "2P";
		whoAttack = "1P";
		if (elapsedTime == 0)
		{
			//2Php 줄기
			sizeX2P -= character_1P_AttackValue * 5;

			if (character_2P == 0)
			{
				kyo2P->setHP(character_1P_AttackValue);
				kyo2P->SetHitCheck(true);
			}
			if (character_2P == 1)
			{
				iori2P->setHP(character_1P_AttackValue);
				iori2P->SetHitCheck(true);
			}
			if (character_2P == 2)
			{
				kim2P->setHP(character_1P_AttackValue);
				kim2P->SetHitCheck(true);
			}
		}
		elapsedTime++;
	}
	else
	{
		/*whoHitted = " ";
		whoAttack = " ";*/
		elapsedTime = 0;

		//맞는 모션 꺼주기
		if (character_1P == 0)
			kyo1P->SetHitCheck(false);

		if (character_1P == 1)
			iori1P->SetHitCheck(false);

		if (character_1P == 2)
			kim1P->SetHitCheck(false);

		if (character_2P == 0)
			kyo2P->SetHitCheck(false);

		if (character_2P == 1)
			iori2P->SetHitCheck(false);

		if (character_2P == 2)
			kim2P->SetHitCheck(false);
	}

	//배틀 종료 HP==0 && Time <=0
	if (character_1P_HP <= 0)	//HP = 0
	{
		checkGameOver = true;
		if (character_2P == 0)
			kyo2P->setWin();
		if (character_2P == 1)
			iori2P->setWin();
		if (character_2P == 2)
			kim2P->setWin();
	}
	if (character_2P_HP <= 0)
	{
		checkGameOver = true;
		if (character_1P == 0)
			kyo1P->setWin();
		if (character_1P == 1)
			iori1P->setWin();
		if (character_1P == 2)
			kim1P->setWin();
	}
	if (timeFrame >= 60) // time = 0 (time out)
	{
		checkGameOver = true;
		timeFrame = 60;
		if (character_1P_HP < character_2P_HP)
		{
			if (character_2P == 0)
				kyo2P->setWin();
			if (character_2P == 1)
				iori2P->setWin();
			if (character_2P == 2)
				kim2P->setWin();
		}
		if (character_1P_HP > character_2P_HP)
		{
			if (character_1P == 0)
				kyo1P->setWin();
			if (character_1P == 1)
				iori1P->setWin();
			if (character_1P == 2)
				kim1P->setWin();
		}
		if (character_1P_HP == character_2P_HP)
		{
			//draw
		}
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

	if (hpBar)
	{
		hpBar->Release();
		delete kim2P;
		kim2P = nullptr;
	}

	if (timer)
	{
		timer->Release();
		delete timer;
		timer = nullptr;
	}

	if (gameOver)
	{
		gameOver->Release();
		delete gameOver;
		gameOver = nullptr;
	}

	if (hp1PBar)
	{
		hp1PBar->Release();
		delete hp1PBar;
		hp1PBar = nullptr;
	}

	if (hp2PBar)
	{
		hp2PBar->Release();
		delete hp2PBar;
		hp2PBar = nullptr;
	}

	KillTimer(g_hWnd, 0);
}

void MainGame::Render(HDC hdc)
{
	//백버퍼를 DC에 연결
	HDC hBack = backBuffer->GetMemDC();

	//배경 렌더
	if (backGround)
		backGround->Render(hBack, backPos.x, backPos.y, backgroundFrame);	//hdc 그릴 시작 좌표

	//타이머 렌더
	if (timer)
		timer->Render(hBack, WINSIZE_X / 2 - 75, 50, timeFrame);

	//충돌 확인용 출력
	//char szText[100], szText1[100], szText2[100], szText3[100];

	//wsprintf(szText, "%s가 맞았다", whoHitted);
	//TextOut(hBack, 400, 2, szText, strlen(szText));
	//wsprintf(szText1, "%s 가 때렸다", whoAttack);
	//TextOut(hBack, 400, 30, szText1, strlen(szText1));

	//wsprintf(szText2, "1hp: %d", character_1P_HP);
	//TextOut(hBack, 200, 2, szText2, strlen(szText2));
	//wsprintf(szText3, "2hp: %d", character_2P_HP);
	//TextOut(hBack, 700, 2, szText3, strlen(szText3));

	//1P 렌더
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

	//2P 렌더
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

	//hp바 렌더
	if (hpBar)
		hpBar->Render(hBack, 0, 0);
	if (hp1PBar)
		hp1PBar->RenderBar(hBack, barPosX + 6, 93, sizeX1P, 25);
	if (hp2PBar)
		hp2PBar->RenderBar(hBack, 857 + 10, 93, sizeX2P, 25);

	//종료 렌더
	if (checkGameOver)
		gameOver->Render(hBack, 0, 0);

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