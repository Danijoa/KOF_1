#include "Iori_1P.h"
#include "Image.h"
#include "CommonFunction.h"
#include <vector>

HRESULT Iori_1P::Init()
{
	iori_SidePosition = 1;	//1p의 초기값은 오른쪽을 바라본다 

	name = "Iori";
	pos.x = 200;
	pos.y = 250 + 20;
	hp = 100;

	chracterFrame = 27;
	frameCount = 0;
	elapsedTime = 0;	//윈도우 프레임 100이 될 때마다 애니메이션 프레임 1씩 증가

	ioriState = Chractor_STATE::INIT;

	stateCount = 11;
	img = new Image[stateCount];

	if (FAILED(img[0].Init("Image/iori_walk_front.bmp", 1020 * 3, 138 * 3, 12, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_walk_front.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[1].Init("Image/iori_walk_back.bmp", 1020 * 3, 138 * 3, 12, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_walk_back.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[2].Init("Image/iori_standing.bmp", 539 * 3, 138 * 3, 7, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Iori_standing.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[3].Init("Image/iori_weak_hand.bmp", 812 * 3, 138 * 3, 7, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_weak_hand.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[4].Init("Image/iori_strong_hand.bmp", 1088 * 3, 138 * 3, 8, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_strong_hand 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[5].Init("Image/iori_weak_foot.bmp", 896 * 3, 138 * 3, 7, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_weak_foot.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[6].Init("Image/iori_strong_foot.bmp", 1694 * 3, 138 * 3, 11, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_strong_foot.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[7].Init("Image/iori_combo.bmp", 5016 * 3, 138 * 3, 19, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_combo 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[8].Init("Image/iori_down_up.bmp", 2160 * 3, 138 * 3, 16, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_down_up.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[9].Init("Image/iori_hit.bmp", 1278 * 3, 138 * 3, 9, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_hit.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[10].Init("Image/iori_init.bmp", 2835 * 3, 138 * 3, 27, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_init.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	iori_win = new Image();
	if (FAILED(iori_win->Init("Image/iori_1P_win.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "윈 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	iori_bar_1P = new Image();
	if (FAILED(iori_bar_1P->Init("Image/iori_1P_selected.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, "미니 캐릭 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	canInput = false;
	comboStore = new int[3];
	comboStore[0] = 'Q';
	comboStore[1] = 'Q';
	comboStore[2] = 'E';
	elapsedTime2 = 0;
	elapsedTime3 = 0;
	storeLast = 0 - '0';
	checkCombo = false;

	//배경
	moveback_R = false;
	moveback_L = false;

	//충돌
	rcHit = { 0, 0, 0, 0 };
	rcAttack = { 0,0,0,0 };

	//
	isOnce = true;

	//
	hitCheck = false;
	isOnceHit = false;

	return S_OK;
}

void Iori_1P::Motion1P()
{
	//앞으로 걷기
	if (KeyManager::GetSingleton()->IsOnceKeyDown('N') && canInput)
	{
		frameCount = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('N') && canInput)
	{
		if (iori_SidePosition == 1)	//1p가 오른쪽을 바라보는 경우
		{
			ioriState = Chractor_STATE::FRONT;
			chracterFrame = 12;
		}
		if (iori_SidePosition == 2)	//1p가 왼쪽을 바라보는 경우
		{
			ioriState = Chractor_STATE::BACK;
			chracterFrame = 12;
		}
		if (pos.x + 250 < WINSIZE_X - 10)
			pos.x += 3;
		if (pos.x + 250 > WINSIZE_X - 200)
			moveback_R = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('N') && canInput)
	{
		ioriState = Chractor_STATE::STAND;
		chracterFrame = 7;
		frameCount = 0;
	}

	//뒤로 걷기
	if (KeyManager::GetSingleton()->IsOnceKeyDown('V') && canInput)
	{
		frameCount = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('V') && canInput)
	{
		if (iori_SidePosition == 1)	//1p가 오른쪽을 바라보는 경우
		{
			ioriState = Chractor_STATE::BACK;
			chracterFrame = 12;
		}
		if (iori_SidePosition == 2)	//1p가 왼쪽을 바라보는 경우
		{
			ioriState = Chractor_STATE::FRONT;
			chracterFrame = 12;
		}
		if (pos.x > 0 + 10)
			pos.x -= 3;
		if (pos.x < 300)
			moveback_L = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('V') && canInput)
	{
		ioriState = Chractor_STATE::STAND;
		chracterFrame = 7;
		frameCount = 0;
	}

	//강손
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	{
		myV.push_back('Q');
		if (canInput)
		{
			attackValue = 20;
			canInput = false;
			ioriState = Chractor_STATE::SHAND;
			chracterFrame = 8 + 1;
			frameCount = 0;
		}
	}

	//강발
	if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))
	{
		myV.push_back('E');
		if (canInput)
		{
			attackValue = 20;
			canInput = false;
			ioriState = Chractor_STATE::SFOOT;
			chracterFrame = 11 + 1;
			frameCount = 0;
		}
	}

	//콤보
	if (checkCombo)
	{
		attackValue = 10;
		canInput = false;
		ioriState = Chractor_STATE::COMBO;
		chracterFrame = 19 + 1;
		frameCount = 0;
		checkCombo = false;
	}

	//맞았을때
	if (hitCheck)
	{
		if (hp > 0)
		{
			canInput = true;
			ioriState = Chractor_STATE::HIT;
			chracterFrame = 9 + 1;
			frameCount = 0;
			isOnceHit = true;
		}
	}

	//약손
	if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
	{
		myV.push_back('A');
		if (canInput)
		{
			attackValue = 10;
			canInput = false;
			ioriState = Chractor_STATE::WHAND;
			chracterFrame = 7 + 1;
			frameCount = 0;
		}
	}

	//약발
	if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))
	{
		myV.push_back('D');
		if (canInput)
		{
			attackValue = 10;
			canInput = false;
			ioriState = Chractor_STATE::WFOOT;
			chracterFrame = 7 + 1;
			frameCount = 0;
		}
	}

}

void Iori_1P::FrameCheck()
{
	elapsedTime++;
	if (elapsedTime >= 9)
	{
		frameCount = (frameCount + 1) % chracterFrame;
		elapsedTime = 0;
	}
}

void Iori_1P::Update()
{
	//게임 종료 다운
	if (hp <= 0)
	{
		canInput = false;
		ioriState = Chractor_STATE::DOWN;
		if (isOnce)
		{
			frameCount = 0;
			isOnce = false;
		}
	}

	//스킬 저장 벡터
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

	elapsedTime3++;
	if (elapsedTime3 >= 9 * 18)
	{
		storeLast = 0 - '0';	//기억한 벡터의 마지막 값도 일정 시간이 흐르면 지워주자
		elapsedTime3 = 0;
	}

	//스킬 변경
	Motion1P();

	//프레임 변경
	if (!canInput && (ioriState == Chractor_STATE::SHAND || ioriState == Chractor_STATE::SFOOT || ioriState == Chractor_STATE::COMBO
		|| ioriState == Chractor_STATE::WFOOT || ioriState == Chractor_STATE::WHAND || ioriState == Chractor_STATE::INIT))
	{
		FrameCheck();

		if (frameCount + 1 == chracterFrame)
		{
			ioriState = Chractor_STATE::STAND;
			chracterFrame = 7;
			frameCount = 0;
			canInput = true;
		}
	}

	else if (isOnceHit && ioriState == Chractor_STATE::HIT)  //맞았을때
	{
		FrameCheck();
		if (frameCount + 1 == chracterFrame)
		{
			ioriState = Chractor_STATE::STAND;
			chracterFrame = 7;
			frameCount = 0;
			isOnceHit = false;
		}
	}

	else if (ioriState == Chractor_STATE::STAND || ioriState == Chractor_STATE::FRONT || ioriState == Chractor_STATE::BACK)
	{
		FrameCheck();
	}
	else //ioriState == Chractor_STATE::DOWN
	{
		elapsedTime++;
		if (elapsedTime >= 9)
		{
			if (frameCount < 16)	//down 부분 프레임 수 넣어주기
				frameCount++;
			elapsedTime = 0;
		}
	}

	//충돌
	Iori_Set_HitBox(frameCount);
	Iori_Set_AttackBox(frameCount);
}

void Iori_1P::Render(HDC hdc)
{
	//char szText[100];
	//wsprintf(szText, "myV[마지막] : %c", storeLast);
	//TextOut(hdc, 10, 2, szText, strlen(szText));
	//if (!myV.empty())
	//{
	//	for (int i = 0; i < myV.size(); i++)	//벡터 안에 있는 값 확인 용 코드
	//	{
	//		wsprintf(szText, "myV[ %d ] : %c", i, myV[i]);
	//		TextOut(hdc, 10, 20 * (i + 1), szText, strlen(szText));
	//	}
	//}

	//hp 옆 미니 캐릭터
	iori_bar_1P->Render(hdc, 0, 0, 0);

	//모션 렌더
	if (iori_SidePosition == 1)
	{
		if (ioriState == Chractor_STATE::FRONT)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[0].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::BACK)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[1].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::STAND)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[2].Render(hdc, pos.x, pos.y, frameCount);

		}

		if (ioriState == Chractor_STATE::WHAND)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[3].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SHAND)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[4].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WFOOT)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[5].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SFOOT)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[6].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::COMBO)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[7].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::DOWN)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[8].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::HIT)
		{
			img[9].Render(hdc, pos.x - 70, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::INIT)
		{
			img[10].Render(hdc, pos.x, pos.y + 10, frameCount);
		}

		if (ioriState == Chractor_STATE::WIN)
		{
			iori_win->Render(hdc, 0, 0, 0);
		}
	}

	if (iori_SidePosition == 2)
	{
		if (ioriState == Chractor_STATE::FRONT)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[0].RenderFlip(hdc, pos.x - img[0].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::BACK)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[1].RenderFlip(hdc, pos.x - img[1].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::STAND)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[2].RenderFlip(hdc, pos.x - img[2].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WHAND)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[3].RenderFlip(hdc, pos.x - img[3].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SHAND)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[4].RenderFlip(hdc, pos.x - img[4].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WFOOT)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[5].RenderFlip(hdc, pos.x - img[5].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SFOOT)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[6].RenderFlip(hdc, pos.x - img[6].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::COMBO)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			//Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[7].RenderFlip(hdc, pos.x - img[7].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::DOWN)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[8].RenderFlip(hdc, pos.x - img[8].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::HIT)
		{
			//Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[9].RenderFlip(hdc, pos.x - img[9].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WIN)
		{
			iori_win->Render(hdc, 0, 0, 0);
		}
	}
}

void Iori_1P::Iori_Set_HitBox(int frameCount)
{
	if (iori_SidePosition == 1)
	{
		switch (ioriState)
		{
		case Chractor_STATE::FRONT:
			rcHit.left = pos.x + 80; //왼쪽 여백
			rcHit.top = pos.y + 78; //위에 높이 맞춰준 여백때문에 이정도
			rcHit.right = pos.x + img[0].GetImageInfo()->frameWidth - 20; //오른쪽 여백
			rcHit.bottom = pos.y + img[0].GetImageInfo()->frameHeight - 15; //아래 여백
			break;
		case Chractor_STATE::BACK:
			rcHit.left = pos.x + 50;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x + img[1].GetImageInfo()->frameWidth - 30;
			rcHit.bottom = pos.y + img[1].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::STAND:
			rcHit.left = pos.x + 50;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x + img[2].GetImageInfo()->frameWidth - 15;
			rcHit.bottom = pos.y + img[2].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::WHAND:
			rcHit.left = pos.x + 80;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x + img[3].GetImageInfo()->frameWidth - 130;
			rcHit.bottom = pos.y + img[3].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::SHAND:
			if (frameCount == 0)
			{
				rcHit.left = pos.x + 150;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[4].GetImageInfo()->frameWidth - 120;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1)
			{
				rcHit.left = pos.x + 160;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[4].GetImageInfo()->frameWidth - 110;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 2 || frameCount == 3 || frameCount == 4 || frameCount == 5 || frameCount == 6)
			{
				rcHit.left = pos.x + 180;
				rcHit.top = pos.y + 120;
				rcHit.right = pos.x + img[4].GetImageInfo()->frameWidth - 90;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x + 180;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[4].GetImageInfo()->frameWidth - 90;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			break;
		case Chractor_STATE::WFOOT:
			rcHit.left = pos.x + 80;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x + img[5].GetImageInfo()->frameWidth - 140;
			rcHit.bottom = pos.y + img[5].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::SFOOT:
			if (frameCount == 0)
			{
				rcHit.left = pos.x + 70;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[6].GetImageInfo()->frameWidth - 250;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1 || frameCount == 2 || frameCount == 3 || frameCount == 4 || frameCount == 5)
			{
				rcHit.left = pos.x + 90;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[6].GetImageInfo()->frameWidth - 190;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 6 || frameCount == 7 || frameCount == 8)
			{
				rcHit.left = pos.x + 100;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[6].GetImageInfo()->frameWidth - 180;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x + 90;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[6].GetImageInfo()->frameWidth - 190;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}

			break;
		case Chractor_STATE::COMBO:
			if (frameCount == 0)
			{
				rcHit.left = pos.x + 110;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[7].GetImageInfo()->frameWidth - 510;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1 || frameCount == 2)
			{
				rcHit.left = pos.x + 120;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[7].GetImageInfo()->frameWidth - 510;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 3 || frameCount == 4)
			{
				rcHit.left = pos.x + 125;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[7].GetImageInfo()->frameWidth - 505;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x + 135;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x + img[7].GetImageInfo()->frameWidth - 510;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			break;
		case Chractor_STATE::DOWN:
			if (frameCount == 0 || frameCount == 1 || frameCount == 2)
			{
				rcHit.left = pos.x + 90;
				rcHit.top = pos.y + 100;
				rcHit.right = pos.x + img[8].GetImageInfo()->frameWidth - 180;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 3 || frameCount == 4 || frameCount == 5 || frameCount == 6)
			{
				rcHit.left = pos.x + 110;
				rcHit.top = pos.y + 110;
				rcHit.right = pos.x + img[8].GetImageInfo()->frameWidth - 145;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 7)
			{
				rcHit.left = pos.x + 110;
				rcHit.top = pos.y + 120;
				rcHit.right = pos.x + img[8].GetImageInfo()->frameWidth - 160;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 8 || frameCount == 9)
			{
				rcHit.left = pos.x + 45;
				rcHit.top = pos.y + 200;
				rcHit.right = pos.x + img[8].GetImageInfo()->frameWidth - 125;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x + 30;
				rcHit.top = pos.y + 270;
				rcHit.right = pos.x + img[8].GetImageInfo()->frameWidth;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			break;
		}
	}

	if (iori_SidePosition == 2)
	{
		switch (ioriState)
		{
		case Chractor_STATE::FRONT:
			rcHit.left = pos.x + 20 - img[0].GetImageInfo()->frameWidth + 280; //왼쪽 여백
			rcHit.top = pos.y + 78; //위에 높이 맞춰준 여백때문에 이정도
			rcHit.right = pos.x - 80 + 280; //오른쪽 여백
			rcHit.bottom = pos.y + img[0].GetImageInfo()->frameHeight - 15; //아래 여백
			break;
		case Chractor_STATE::BACK:
			rcHit.left = pos.x + 30 - img[1].GetImageInfo()->frameWidth + 280;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x - 50 + 280;
			rcHit.bottom = pos.y + img[1].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::STAND:
			rcHit.left = pos.x + 15 - img[2].GetImageInfo()->frameWidth + 280;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x - 50 + 280;
			rcHit.bottom = pos.y + img[2].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::WHAND:
			rcHit.left = pos.x + 130 - img[3].GetImageInfo()->frameWidth + 280;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x - 80 + 280;
			rcHit.bottom = pos.y + img[3].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::SHAND:
			if (frameCount == 0)
			{
				rcHit.left = pos.x + 120 - img[4].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 150 + 280;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1)
			{
				rcHit.left = pos.x + 110 - img[4].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 160 + 280;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 2 || frameCount == 3 || frameCount == 4 || frameCount == 5 || frameCount == 6)
			{
				rcHit.left = pos.x + 90 - img[4].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 120;
				rcHit.right = pos.x - 180 + 280;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x + 90 - img[4].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 180 + 280;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			break;
		case Chractor_STATE::WFOOT:
			rcHit.left = pos.x + 140 - img[5].GetImageInfo()->frameWidth + 280;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x - 80 + 280;
			rcHit.bottom = pos.y + img[5].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::SFOOT:
			if (frameCount == 0)
			{
				rcHit.left = pos.x - 250 + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 70 + 280;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1 || frameCount == 2 || frameCount == 3 || frameCount == 4 || frameCount == 5)
			{
				rcHit.left = pos.x - 250 + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 70 + 280;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 6 || frameCount == 7 || frameCount == 8)
			{
				rcHit.left = pos.x - 250 + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 80 + 280;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x - 250 + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 70 + 280;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}

			break;
		case Chractor_STATE::COMBO:
			if (frameCount == 0)
			{
				rcHit.left = pos.x + 510 - img[7].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 110 + 280;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1 || frameCount == 2)
			{
				rcHit.left = pos.x + 510 - img[7].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 120 + 280;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 3 || frameCount == 4)
			{
				rcHit.left = pos.x + 505 - img[7].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 125 + 280;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x + 510 - img[7].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 135 + 280;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			break;
		case Chractor_STATE::DOWN:
			if (frameCount == 0 || frameCount == 1 || frameCount == 2)
			{
				rcHit.left = pos.x + 180 - img[8].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 100;
				rcHit.right = pos.x - 90 + 280;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 3 || frameCount == 4 || frameCount == 5 || frameCount == 6)
			{
				rcHit.left = pos.x + 140 - img[8].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 110;
				rcHit.right = pos.x - 110 + 280;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 7)
			{
				rcHit.left = pos.x + 160 - img[8].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 120;
				rcHit.right = pos.x - 110 + 280;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 8 || frameCount == 9)
			{
				rcHit.left = pos.x + 125 - img[8].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 200;
				rcHit.right = pos.x - 45 + 280;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x - img[8].GetImageInfo()->frameWidth + 280;
				rcHit.top = pos.y + 270;
				rcHit.right = pos.x - 30 + 280;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			break;
		}
	}
}

void Iori_1P::Iori_Set_AttackBox(int frameCount)
{
	if (iori_SidePosition == 1)
	{
		switch (ioriState)
		{
		case Chractor_STATE::WHAND:
			if (frameCount == 3 || frameCount == 4)
			{
				rcAttack.left = pos.x + 150;
				rcAttack.top = pos.y + 170;
				rcAttack.right = pos.x + 350;
				rcAttack.bottom = pos.y + 230;
			}
			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		case Chractor_STATE::SHAND:
			if (frameCount == 3 || frameCount == 4)
			{
				rcAttack.left = pos.x + 360;
				rcAttack.top = pos.y + 80;
				rcAttack.right = pos.x + 405;
				rcAttack.bottom = pos.y + 130;
			}
			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		case Chractor_STATE::WFOOT:
			if (frameCount == 3 || frameCount == 4)
			{
				rcAttack.left = pos.x + 150;
				rcAttack.top = pos.y + 190;
				rcAttack.right = pos.x + 380;
				rcAttack.bottom = pos.y + 260;
			}
			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		case Chractor_STATE::SFOOT:
			if (frameCount == 5 || frameCount == 6)
			{
				rcAttack.left = pos.x + 150;
				rcAttack.top = pos.y + 130;
				rcAttack.right = pos.x + 460;
				rcAttack.bottom = pos.y + 200;
			}
			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		case Chractor_STATE::COMBO:
			if (frameCount == 6)
			{
				rcAttack.left = pos.x + 375;
				rcAttack.top = pos.y + 230;
				rcAttack.right = pos.x + 447;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 7)
			{
				rcAttack.left = pos.x + 396;
				rcAttack.top = pos.y + 230;
				rcAttack.right = pos.x + 490;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 8)
			{
				rcAttack.left = pos.x + 426;
				rcAttack.top = pos.y + 250;
				rcAttack.right = pos.x + 513;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 9)
			{
				rcAttack.left = pos.x + 447;
				rcAttack.top = pos.y + 270;
				rcAttack.right = pos.x + 546;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 10)
			{
				rcAttack.left = pos.x + 486;
				rcAttack.top = pos.y + 300;
				rcAttack.right = pos.x + 566;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 11)
			{
				rcAttack.left = pos.x + 519;
				rcAttack.top = pos.y + 180;
				rcAttack.right = pos.x + 596;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 12)
			{
				rcAttack.left = pos.x + 546;
				rcAttack.top = pos.y + 180;
				rcAttack.right = pos.x + 627;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 13)
			{
				rcAttack.left = pos.x + 594;
				rcAttack.top = pos.y + 250;
				rcAttack.right = pos.x + 669;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 14)
			{
				rcAttack.left = pos.x + 621;
				rcAttack.top = pos.y + 300;
				rcAttack.right = pos.x + 684;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 15)
			{
				rcAttack.left = pos.x + 657;
				rcAttack.top = pos.y + 300;
				rcAttack.right = pos.x + 705;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 16)
			{
				rcAttack.left = pos.x + 684;
				rcAttack.top = pos.y + 300;
				rcAttack.right = pos.x + 732;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 17)
			{
				rcAttack.left = pos.x + 711;
				rcAttack.top = pos.y + 336;
				rcAttack.right = pos.x + 759;
				rcAttack.bottom = pos.y + 387;
			}

			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		}
	}

	if (iori_SidePosition == 2)
	{
		switch (ioriState)
		{
		case Chractor_STATE::WHAND:
			if (frameCount == 3 || frameCount == 4)
			{
				rcAttack.right = pos.x - 150 + 280;
				rcAttack.top = pos.y + 170;
				rcAttack.left = pos.x - 350 + 280;
				rcAttack.bottom = pos.y + 230;
			}
			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		case Chractor_STATE::SHAND:
			if (frameCount == 3 || frameCount == 4)
			{
				rcAttack.right = pos.x - 360 + 280;
				rcAttack.top = pos.y + 80;
				rcAttack.left = pos.x - 405 + 280;
				rcAttack.bottom = pos.y + 130;
			}
			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		case Chractor_STATE::WFOOT:
			if (frameCount == 3 || frameCount == 4)
			{
				rcAttack.right = pos.x - 150 + 280;
				rcAttack.top = pos.y + 190;
				rcAttack.left = pos.x - 380 + 280;
				rcAttack.bottom = pos.y + 260;
			}
			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		case Chractor_STATE::SFOOT:
			if (frameCount == 5 || frameCount == 6)
			{
				rcAttack.right = pos.x - 150 + 280;
				rcAttack.top = pos.y + 130;
				rcAttack.left = pos.x - 460 + 280;
				rcAttack.bottom = pos.y + 200;
			}
			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		case Chractor_STATE::COMBO:
			if (frameCount == 6)
			{
				rcAttack.right = pos.x - 375 + 280;
				rcAttack.top = pos.y + 230;
				rcAttack.left = pos.x - 447 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 7)
			{
				rcAttack.right = pos.x - 396 + 280;
				rcAttack.top = pos.y + 230;
				rcAttack.left = pos.x - 490 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 8)
			{
				rcAttack.right = pos.x - 426 + 280;
				rcAttack.top = pos.y + 250;
				rcAttack.left = pos.x - 513 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 9)
			{
				rcAttack.right = pos.x - 447 + 280;
				rcAttack.top = pos.y + 270;
				rcAttack.left = pos.x - 546 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 10)
			{
				rcAttack.right = pos.x - 486 + 280;
				rcAttack.top = pos.y + 300;
				rcAttack.left = pos.x - 566 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 11)
			{
				rcAttack.right = pos.x - 519 + 280;
				rcAttack.top = pos.y + 180;
				rcAttack.left = pos.x - 596 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 12)
			{
				rcAttack.right = pos.x - 546 + 280;
				rcAttack.top = pos.y + 180;
				rcAttack.left = pos.x - 627 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 13)
			{
				rcAttack.right = pos.x - 594 + 280;
				rcAttack.top = pos.y + 250;
				rcAttack.left = pos.x - 669 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 14)
			{
				rcAttack.right = pos.x - 621 + 280;
				rcAttack.top = pos.y + 300;
				rcAttack.left = pos.x - 684 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 15)
			{
				rcAttack.right = pos.x - 657 + 280;
				rcAttack.top = pos.y + 300;
				rcAttack.left = pos.x - 705 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 16)
			{
				rcAttack.right = pos.x - 684 + 280;
				rcAttack.top = pos.y + 300;
				rcAttack.left = pos.x - 732 + 280;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 17)
			{
				rcAttack.right = pos.x - 711 + 280;
				rcAttack.top = pos.y + 336;
				rcAttack.left = pos.x - 759 + 280;
				rcAttack.bottom = pos.y + 387;
			}

			else
			{
				rcAttack.left = 0;
				rcAttack.top = 0;
				rcAttack.right = 0;
				rcAttack.bottom = 0;
			}
			break;
		}
	}
}

void Iori_1P::Release()
{
	if (img)
	{
		for (int i = 0; i < stateCount; i++)
		{
			img[i].Release();
		}
		delete[] img;
		img = nullptr;
	}
}

Iori_1P::Iori_1P()
{
}

Iori_1P::~Iori_1P()
{
}
