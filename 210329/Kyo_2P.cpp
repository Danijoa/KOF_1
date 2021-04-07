#include "Kyo_2P.h"
#include "Image.h"
#include "CommonFunction.h"
#include <vector>

HRESULT Kyo_2P::Init()
{
	kyo_SidePosition = 2;

	name = "KYO";
	pos.x = WINSIZE_X - 700;
	pos.y = 100 + 80;
	hp = 100;

	characterFrame = 10;
	frameCount = 0;
	elapsedTime = 0;
	attackValue = 10;

	kyoState = State::STAND;

	imageSizeY = 190 * 3;
	imageSize[(int)State::STAND] = 750 * 3 / 10;
	kyo_stand = new Image();
	if (FAILED(kyo_stand->Init("Image/kyo_stand.bmp", 750 * 3, imageSizeY, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "stand 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	imageSize[(int)State::FRONT] = 460 * 3 / 5;
	kyo_walkFront = new Image();
	if (FAILED(kyo_walkFront->Init("Image/kyo_walkfront.bmp", 460 * 3, imageSizeY, 5, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "앞으로 걷기 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	imageSize[(int)State::BACK] = 522 * 3 / 6;
	kyo_walkBack = new Image();
	if (FAILED(kyo_walkBack->Init("Image/kyo_walkback.bmp", 522 * 3, imageSizeY, 6, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "뒤고 걷기 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	imageSize[(int)State::SHAND] = 952 * 3 / 7;
	kyo_gangson = new Image();
	if (FAILED(kyo_gangson->Init("Image/kyo_gangson.bmp", 952 * 3, imageSizeY, 7, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "강손 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	imageSize[(int)State::SFOOT] = 1593 * 3 / 9;
	kyo_gangbal = new Image();
	if (FAILED(kyo_gangbal->Init("Image/kyo_gangbal.bmp", 1593 * 3, imageSizeY, 9, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "강발 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	imageSize[(int)State::COMBO] = 2420 * 3 / 20;
	kyo_combo = new Image();
	if (FAILED(kyo_combo->Init("Image/kyo_combo_motion.bmp", 2420 * 3, imageSizeY, 20, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "콤보 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	imageSize[(int)State::WHAND] = 630 * 3 / 5;
	kyo_yakson = new Image();
	if (FAILED(kyo_yakson->Init("Image/kyo_yakson.bmp", 630 * 3, imageSizeY, 5, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "약손 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	imageSize[(int)State::WFOOT] = 1113 * 3 / 7;
	kyo_yakbal = new Image();
	if (FAILED(kyo_yakbal->Init("Image/kyo_yakbal.bmp", 1113 * 3, imageSizeY, 7, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "약발 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	imageSize[(int)State::DOWN] = 3189 * 3 / 17;
	kyo_hitted = new Image();
	if (FAILED(kyo_hitted->Init("Image/kyo_hitted.bmp", 1488 * 3, imageSizeY, 8, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "힛 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	kyo_win = new Image();
	if (FAILED(kyo_win->Init("Image/kyo_2P_win.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "윈 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	kyo_bar_2P = new Image();
	if (FAILED(kyo_bar_2P->Init("Image/kyo_2P_selected.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "미니 캐릭 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	rcHit_Size.x = imageSize[(int)State::STAND] * 0.75;														// 초록색 hit 네모의 (x)가로 크기
	rcHit_Size.y = imageSizeY * 0.5;																		// 초록색 hit 네모의 (y)세로 크기
	rcHIT_pos.x = 0;
	rcHIT_pos.y = 0;
	rcHit = { (LONG)rcHIT_pos.x, (LONG)rcHIT_pos.y, (LONG)rcHit_Size.x, (LONG)rcHit_Size.y };				// 시작x, 시작y, 가로크기, 세로크기
	rcAttack_Size.x = 0;																					// 빨간색 attack 네모의 (x)가로 크기
	rcAttack_Size.y = 0;																					// 빨간색 attack 네모의 (y)세로 크기
	rcAttack_pos.x = pos.x;
	rcAttack_pos.y = pos.y;
	rcAttack = { (LONG)rcAttack_pos.x, (LONG)rcAttack_pos.y, (LONG)rcAttack_Size.x, (LONG)rcAttack_Size.y };

	canInput = true;
	comboStore = new int[3];
	comboStore[0] = 'U';
	comboStore[1] = 'U';
	comboStore[2] = 'O';
	elapsedTime2 = 0;
	elapsedTime3 = 0;
	storeLast = 0 - '0';
	checkCombo = false;

	moveback_R = false;
	moveback_L = false;

	//
	isOnce = true;

	return S_OK;
}

void Kyo_2P::Motion2P()
{
	//앞으로 걷기
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT) && canInput)
	{
		frameCount = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) && canInput)
	{
		if (kyo_SidePosition == 2)
		{
			kyoState = State::FRONT;
			characterFrame = 5;
		}
		if (kyo_SidePosition == 1)
		{
			kyoState = State::BACK;
			characterFrame = 6;
		}
		if (pos.x > 0 + 10)
			pos.x -= 3;
		if (pos.x < 0 + 150)
			moveback_L = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) && canInput)
	{
		kyoState = State::STAND;
		characterFrame = 10;
		frameCount = 0;
	}

	//뒤로 걷기
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT) && canInput)
	{
		frameCount = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT) && canInput)
	{
		if (kyo_SidePosition == 2)
		{
			kyoState = State::BACK;
			characterFrame = 6;
		}
		if (kyo_SidePosition == 1)
		{
			kyoState = State::FRONT;
			characterFrame = 5;
		}
		if (pos.x + 250 < WINSIZE_X - 10)
			pos.x += 3;
		if (pos.x + 250 > WINSIZE_X - 200)
			moveback_R = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT) && canInput)
	{
		kyoState = State::STAND;
		characterFrame = 10;
		frameCount = 0;
	}

	//강손
	if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
	{
		myV.push_back('U');
		if (canInput)
		{
			attackValue = 20;
			canInput = false;
			kyoState = State::SHAND;
			characterFrame = 7 + 1;
			frameCount = 0;
		}
	}

	//강발
	if (KeyManager::GetSingleton()->IsOnceKeyDown('O'))
	{
		myV.push_back('O');
		if (canInput)
		{
			attackValue = 20;
			canInput = false;
			kyoState = State::SFOOT;
			characterFrame = 9 + 1;
			frameCount = 0;
		}
	}

	//콤보
	if (checkCombo)
	{
		attackValue = 10;
		canInput = false;
		kyoState = State::COMBO;
		characterFrame = 20 + 1;
		frameCount = 0;
		checkCombo = false;
	}

	//약손
	if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
	{
		myV.push_back('J');
		if (canInput)
		{
			attackValue = 10;
			canInput = false;
			kyoState = State::WHAND;
			characterFrame = 5 + 1;
			frameCount = 0;
		}
	}

	//약발
	if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
	{
		myV.push_back('L');
		if (canInput)
		{
			attackValue = 10;
			canInput = false;
			kyoState = State::WFOOT;
			characterFrame = 7 + 1;
			frameCount = 0;
		}
	}
}

void Kyo_2P::CollisionRect()
{
	//콤보
	if (kyoState == State::COMBO)
	{
		if (frameCount == 5 || frameCount == 6 || frameCount == 7)
		{
			if (kyo_SidePosition == 1)
			{
				if (frameCount == 5)
				{
					rcAttack_pos.x = pos.x + 200;
					rcAttack_pos.y = pos.y + 300;
				}
				if (frameCount == 6)
				{
					rcAttack_pos.x = pos.x + 250;
					rcAttack_pos.y = pos.y + 150;
				}
				if (frameCount == 7)
				{
					rcAttack_pos.x = pos.x + 100;
					rcAttack_pos.y = pos.y + 100;
				}
			}
			if (kyo_SidePosition == 2)
			{
				if (frameCount == 5)
				{
					rcAttack_pos.x = pos.x - 50;
					rcAttack_pos.y = pos.y + 350;
				}
				if (frameCount == 6)
				{
					rcAttack_pos.x = pos.x - 100;
					rcAttack_pos.y = pos.y + 180;
				}
				if (frameCount == 7)
				{
					rcAttack_pos.x = pos.x + 20;
					rcAttack_pos.y = pos.y + 100;
				}
			}
			rcAttack_Size.x = 55;
			rcAttack_Size.y = 55;
		}
		else if (frameCount >= 8 && frameCount <= 14)
		{
			if (kyo_SidePosition == 1)
			{
				rcAttack_pos.x = pos.x + 200;
				rcAttack_pos.y = pos.y + 170;
			}
			if (kyo_SidePosition == 2)
			{
				rcAttack_pos.x = pos.x - 140;
				rcAttack_pos.y = pos.y + 160;
			}
			rcAttack_Size.x = 100 + 7 * (frameCount - 8);
			rcAttack_Size.y = 100 + 7 * (frameCount - 8);
		}
		else
		{
			rcAttack_Size.x = 0;
			rcAttack_Size.y = 0;
		}
	}

	//강손
	if (kyoState == State::SHAND)
	{
		if (frameCount >= 2 && frameCount <= 4)
		{
			if (kyo_SidePosition == 1)
			{
				rcAttack_pos.x = pos.x + 310;
				rcAttack_pos.y = pos.y + 220;
			}
			if (kyo_SidePosition == 2)
			{
				rcAttack_pos.x = pos.x - 135;
				rcAttack_pos.y = pos.y + 210;
			}
			rcAttack_Size.x = 55;
			rcAttack_Size.y = 55;
		}
		else
		{
			rcAttack_Size.x = 0;
			rcAttack_Size.y = 0;
		}
	}

	//강발
	if (kyoState == State::SFOOT)
	{
		if (frameCount >= 2 && frameCount <= 4)
		{
			if (kyo_SidePosition == 1)
			{
				rcAttack_pos.x = pos.x + 270;
				rcAttack_pos.y = pos.y + 235;
			}
			if (kyo_SidePosition == 2)
			{
				rcAttack_pos.x = pos.x - 180;
				rcAttack_pos.y = pos.y + 235;
			}
			rcAttack_Size.x = 55 * 3;
			rcAttack_Size.y = 55;
		}
		else
		{
			rcAttack_Size.x = 0;
			rcAttack_Size.y = 0;
		}
	}

	//약손
	if (kyoState == State::WHAND)
	{
		if (frameCount >= 1 && frameCount <= 3)
		{
			if (kyo_SidePosition == 1)
			{
				rcAttack_pos.x = pos.x + 270;
				rcAttack_pos.y = pos.y + 190;
			}
			if (kyo_SidePosition == 2)
			{
				rcAttack_pos.x = pos.x - 110;
				rcAttack_pos.y = pos.y + 190;
			}
			rcAttack_Size.x = 55;
			rcAttack_Size.y = 55;
		}
		else
		{
			rcAttack_Size.x = 0;
			rcAttack_Size.y = 0;
		}
	}

	//약발
	if (kyoState == State::WFOOT)
	{
		if (frameCount >= 2 && frameCount <= 4)
		{
			if (kyo_SidePosition == 1)
			{
				rcAttack_pos.x = pos.x + 330;
				rcAttack_pos.y = pos.y + 370;
			}
			if (kyo_SidePosition == 2)
			{
				rcAttack_pos.x = pos.x - 170;
				rcAttack_pos.y = pos.y + 370;
			}
			rcAttack_Size.x = 55;
			rcAttack_Size.y = 55;
		}
		else
		{
			rcAttack_Size.x = 0;	//공격 모션 끝나면 네모도 사라지게
			rcAttack_Size.y = 0;
		}
	}
}

void Kyo_2P::FrameCheck()
{
	elapsedTime++;
	if (elapsedTime >= 9)
	{
		frameCount = (frameCount + 1) % characterFrame;
		elapsedTime = 0;
	}
}

void Kyo_2P::Update()
{
	//게임 종료 다운
	if (hp <= 0)
	{
		canInput = false;
		kyoState = State::DOWN;
		if (isOnce)
		{
			frameCount = 0;
			isOnce = false;
		}
	}

	//hit 네모
	rcHIT_pos.x = pos.x + 20;
	rcHIT_pos.y = pos.y + 180;
	rcHit = { (LONG)rcHIT_pos.x, (LONG)rcHIT_pos.y, (LONG)rcHit_Size.x, (LONG)rcHit_Size.y };		// 시작x, 시작y, 가로크기, 세로크기
	rcHit_temp = { (LONG)rcHIT_pos.x, (LONG)rcHIT_pos.y, (LONG)rcHit_Size.x + (LONG)rcHIT_pos.x, (LONG)rcHit_Size.y + (LONG)rcHIT_pos.y };

	//attack 네모
	rcAttack = { (LONG)rcAttack_pos.x, (LONG)rcAttack_pos.y, (LONG)rcAttack_Size.x, (LONG)rcAttack_Size.y };
	rcAttack_temp = { (LONG)rcAttack_pos.x, (LONG)rcAttack_pos.y, (LONG)rcAttack_Size.x + (LONG)rcAttack_pos.x, (LONG)rcAttack_Size.y + (LONG)rcAttack_pos.y };

	//스킬 저장 벡터(1)
	elapsedTime2++;
	if (elapsedTime2 >= 9 * 10)	//프레임 업데이트가 10번 일어나면 벡터를 지워준다
	{
		if (!myV.empty())
		{
			storeLast = myV[myV.size() - 1];	//지워주기 전에 벡터의 마지막 값이 무엇인지 기억해주자
		}
		myV.clear();
		elapsedTime2 = 0;
	}
	else
	{
		if (myV.size() > 2)		//벡터가 지워지기 전 콤보 입력이 일어 났는가 확인
		{
			for (int i = myV.size() - 1; i >= 0; i--)
			{
				if (myV[i] == comboStore[2] && i - 2 >= 0)
				{
					if (myV[i - 1] == comboStore[1] && myV[i - 2] == comboStore[0])
					{
						checkCombo = true;
						myV.clear();
						break;
					}
				}
			}
		}
		if (myV.size() == 2)	//벡터가 지워지는 시점에 콤보가 눌린 경우를 대비한 코드
		{
			if (myV[myV.size() - 1] == comboStore[2] && myV[myV.size() - 2] == comboStore[1] && storeLast == comboStore[0])
			{
				checkCombo = true;
				myV.clear();
			}
		}
	}
	//스킬 저장 벡터(2)
	elapsedTime3++;
	if (elapsedTime3 >= 9 * 18)
	{
		storeLast = 0 - '0';	//기억한 벡터의 마지막 값도 일정 시간이 흐르면 지워주자
		elapsedTime3 = 0;
	}

	//스킬 변경
	Motion2P();

	//프레임 변경
	if (!canInput && (kyoState == State::SHAND || kyoState == State::SFOOT || kyoState == State::COMBO
		|| kyoState == State::WFOOT || kyoState == State::WHAND))
	{
		FrameCheck();
		CollisionRect();

		if (frameCount + 1 == characterFrame)
		{
			kyoState = State::STAND;
			characterFrame = 10;
			frameCount = 0;
			canInput = true;
		}
	}
	else if (kyoState == State::STAND || kyoState == State::FRONT || kyoState == State::BACK)
	{
		FrameCheck();
	}
	else //kyoState == State::DOWN
	{
		elapsedTime++;
		if (elapsedTime >= 9)
		{
			if(frameCount<7)	//0~7frame
				frameCount++;
			elapsedTime = 0;
		}
	}
}

void Kyo_2P::Render(HDC hdc)
{
	char szText[100];
	wsprintf(szText, "myV[마지막] : %c", storeLast);
	TextOut(hdc, 900, 2, szText, strlen(szText));
	if (!myV.empty())
	{
		for (int i = 0; i < myV.size(); i++)	//벡터 안에 있는 값 확인 용 코드
		{
			wsprintf(szText, "myV[ %d ] : %c", i, myV[i]);
			TextOut(hdc, 900, 20 * (i + 1), szText, strlen(szText));
		}
	}

	//hit 네모
	RenderRect(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);

	//attack 네모
	RenderRect(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);

	//hpbar
	kyo_bar_2P->Render(hdc, 0, 0, 0);

	//모션 렌더
	if (kyo_SidePosition == 1)
	{
		switch (kyoState)
		{
		case State::STAND:
			kyo_stand->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::FRONT:
			kyo_walkFront->Render(hdc, pos.x - 20, pos.y, frameCount);
			break;
		case State::BACK:
			kyo_walkBack->Render(hdc, pos.x - 10, pos.y, frameCount);
			break;
		case State::SHAND:
			kyo_gangson->Render(hdc, pos.x - 15, pos.y, frameCount);
			break;
		case State::SFOOT:
			kyo_gangbal->Render(hdc, pos.x - 70, pos.y, frameCount);
			break;
		case State::COMBO:
			kyo_combo->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WHAND:
			kyo_yakson->Render(hdc, pos.x - 30, pos.y, frameCount);
			break;
		case State::WFOOT:
			kyo_yakbal->Render(hdc, pos.x - 80, pos.y, frameCount);
			break;
		case State::DOWN:
			kyo_hitted->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WIN:
			kyo_win->Render(hdc, 0, 0, 0);
			break;
		}
	}
	else if (kyo_SidePosition == 2)	
	{
		switch (kyoState)
		{
		case State::STAND:
			kyo_stand->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::FRONT:
			kyo_walkFront->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::BACK:
			kyo_walkBack->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::SHAND:
			kyo_gangson->RenderFlip(hdc, pos.x - 160, pos.y, frameCount);
			break;
		case State::SFOOT:
			kyo_gangbal->RenderFlip(hdc, pos.x - 220, pos.y, frameCount);
			break;
		case State::COMBO:
			kyo_combo->RenderFlip(hdc, pos.x - 170, pos.y, frameCount);
			break;
		case State::WHAND:
			kyo_yakson->RenderFlip(hdc, pos.x - 130, pos.y, frameCount);
			break;
		case State::WFOOT:
			kyo_yakbal->RenderFlip(hdc, pos.x - 180, pos.y, frameCount);
			break;
		case State::DOWN:
			kyo_hitted->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WIN:
			kyo_win->Render(hdc, 0, 0, 0);
			break;
		}
	}
}

void Kyo_2P::Release()
{
	kyo_stand->Release();
	delete kyo_stand;
	kyo_stand = nullptr;

	kyo_walkFront->Release();
	delete kyo_walkFront;
	kyo_walkFront = nullptr;

	kyo_walkBack->Release();
	delete kyo_walkBack;
	kyo_walkBack = nullptr;

	kyo_gangbal->Release();
	delete kyo_gangbal;
	kyo_gangbal = nullptr;

	kyo_gangson->Release();
	delete kyo_gangson;
	kyo_gangson = nullptr;

	kyo_yakbal->Release();
	delete kyo_yakbal;
	kyo_yakbal = nullptr;

	kyo_yakson->Release();
	delete kyo_yakson;
	kyo_yakson = nullptr;

	kyo_hitted->Release();
	delete kyo_hitted;
	kyo_hitted = nullptr;
}