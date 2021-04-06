#include "Iori_2P.h"
#include "CommonFunction.h"
#include "Image.h"
#include <vector>


HRESULT Iori_2P::Init()
{
	iori_SidePosition = 2;

	name = "Iori";
	pos.x = 800;
	pos.y = 250;
	hp = 100;

	chracterFrame = 7;
	frameCount = 0;
	elapsedTime = 0;	//윈도우 프레임 100이 될 때마다 애니메이션 프레임 1씩 증가

	ioriState = Chractor_STATE::STAND;

	stateCount = 9;
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

	return S_OK;
}

void Iori_2P::Motion2P()
{
	//앞으로 걷기
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT) && canInput)
	{
		frameCount = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) && canInput)
	{
		if (iori_SidePosition == 2)
		{
			ioriState = Chractor_STATE::FRONT;
			chracterFrame = 12;
		}
		if (iori_SidePosition == 1)
		{
			ioriState = Chractor_STATE::BACK;
			chracterFrame = 12;
		}
		if (pos.x > 0 + 10)
			pos.x -= 3;
		if (pos.x < 0 + 150)
			moveback_L = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) && canInput)
	{
		ioriState = Chractor_STATE::STAND;
		chracterFrame = 7;
		frameCount = 0;
	}

	//뒤로 걷기
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT) && canInput)
	{
		frameCount = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT) && canInput)
	{
		if (iori_SidePosition == 2)
		{
			ioriState = Chractor_STATE::BACK;
			chracterFrame = 6;
		}
		if (iori_SidePosition == 1)
		{
			ioriState = Chractor_STATE::FRONT;
			chracterFrame = 5;
		}
		if (pos.x + 522 / 5 < WINSIZE_X - 50)
			pos.x += 3;
		if (pos.x + 522 / 5 > WINSIZE_X - 200)
			moveback_R = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT) && canInput)
	{
		ioriState = Chractor_STATE::STAND;
		chracterFrame = 7;
		frameCount = 0;
	}

	//강손
	if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
	{
		myV.push_back('U');
		if (canInput)
		{
			canInput = false;
			ioriState = Chractor_STATE::SHAND;
			chracterFrame = 8 + 1;
			frameCount = 0;
		}
	}

	//강발
	if (KeyManager::GetSingleton()->IsOnceKeyDown('O'))
	{
		myV.push_back('O');
		if (canInput)
		{
			canInput = false;
			ioriState = Chractor_STATE::SFOOT;
			chracterFrame = 11 + 1;
			frameCount = 0;
		}
	}

	//콤보
	if (checkCombo)
	{
		canInput = false;
		ioriState = Chractor_STATE::COMBO;
		chracterFrame = 19 + 1;
		frameCount = 0;
		checkCombo = false;
	}

	//약손
	if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
	{
		myV.push_back('J');
		if (canInput)
		{
			canInput = false;
			ioriState = Chractor_STATE::WHAND;
			chracterFrame = 7 + 1;
			frameCount = 0;
		}
	}

	//약발
	if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
	{
		myV.push_back('L');
		if (canInput)
		{
			canInput = false;
			ioriState = Chractor_STATE::WFOOT;
			chracterFrame = 7 + 1;
			frameCount = 0;
		}
	}

}

void Iori_2P::FrameCheck()
{
	elapsedTime++;
	if (elapsedTime >= 9)
	{
		frameCount = (frameCount + 1) % chracterFrame;
		elapsedTime = 0;
	}
}

void Iori_2P::Update()
{
	//적이랑 위치 바뀌면 kyo_SidePosition도 변경 해 주자

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
	Motion2P();

	//프레임 변경
	if (!canInput && (ioriState == Chractor_STATE::SHAND || ioriState == Chractor_STATE::SFOOT || ioriState == Chractor_STATE::COMBO
		|| ioriState == Chractor_STATE::WFOOT || ioriState == Chractor_STATE::WHAND))
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
	else
	{
		FrameCheck();
	}
	///////////// 추가 부분 - 충돌 /////////////////
	Iori_Set_HitBox(frameCount);
	Iori_Set_AttackBox(frameCount);
}

void Iori_2P::Render(HDC hdc)
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

	//모션 렌더
	if (iori_SidePosition == 1)
	{
		if (ioriState == Chractor_STATE::FRONT)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[0].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::BACK)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[1].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::STAND)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[2].Render(hdc, pos.x, pos.y, frameCount);

		}

		if (ioriState == Chractor_STATE::WHAND)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[3].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SHAND)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[4].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WFOOT)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[5].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SFOOT)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[6].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::COMBO)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[7].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::DOWN)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[8].Render(hdc, pos.x, pos.y, frameCount);
		}
	}

	if (iori_SidePosition == 2)
	{
		if (ioriState == Chractor_STATE::FRONT)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[0].RenderFlip(hdc, pos.x - img[0].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::BACK)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[1].RenderFlip(hdc, pos.x - img[1].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::STAND)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[2].RenderFlip(hdc, pos.x - img[2].GetImageInfo()->frameWidth + 280, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WHAND)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[3].RenderFlip(hdc, pos.x - img[3].GetImageInfo()->frameWidth, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SHAND)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[4].RenderFlip(hdc, pos.x - img[4].GetImageInfo()->frameWidth, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WFOOT)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[5].RenderFlip(hdc, pos.x - img[5].GetImageInfo()->frameWidth, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SFOOT)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[6].RenderFlip(hdc, pos.x - img[6].GetImageInfo()->frameWidth, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::COMBO)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			Rectangle(hdc, rcAttack.left, rcAttack.top, rcAttack.right, rcAttack.bottom);
			img[7].RenderFlip(hdc, pos.x - img[7].GetImageInfo()->frameWidth, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::DOWN)
		{
			Rectangle(hdc, rcHit.left, rcHit.top, rcHit.right, rcHit.bottom);
			img[8].RenderFlip(hdc, pos.x - img[8].GetImageInfo()->frameWidth, pos.y, frameCount);
		}
	}
}


void Iori_2P::Release()
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

void Iori_2P::Iori_Set_HitBox(int frameCount)
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
			rcHit.left = pos.x + 20 - img[0].GetImageInfo()->frameWidth; //왼쪽 여백
			rcHit.top = pos.y + 78; //위에 높이 맞춰준 여백때문에 이정도
			rcHit.right = pos.x - 80; //오른쪽 여백
			rcHit.bottom = pos.y + img[0].GetImageInfo()->frameHeight - 15; //아래 여백
			break;
		case Chractor_STATE::BACK:
			rcHit.left = pos.x + 30 - img[1].GetImageInfo()->frameWidth;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x - 50;
			rcHit.bottom = pos.y + img[1].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::STAND:
			rcHit.left = pos.x + 15 - img[2].GetImageInfo()->frameWidth;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x - 50;
			rcHit.bottom = pos.y + img[2].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::WHAND:
			rcHit.left = pos.x + 130 - img[3].GetImageInfo()->frameWidth;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x - 80;
			rcHit.bottom = pos.y + img[3].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::SHAND:
			if (frameCount == 0)
			{
				rcHit.left = pos.x + 120 - img[4].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 150;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1)
			{
				rcHit.left = pos.x + 110 - img[4].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 160;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 2 || frameCount == 3 || frameCount == 4 || frameCount == 5 || frameCount == 6)
			{
				rcHit.left = pos.x + 90 - img[4].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 120;
				rcHit.right = pos.x - 180;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x + 90 - img[4].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 180;
				rcHit.bottom = pos.y + img[4].GetImageInfo()->frameHeight - 15;
			}
			break;
		case Chractor_STATE::WFOOT:
			rcHit.left = pos.x + 140 - img[5].GetImageInfo()->frameWidth;
			rcHit.top = pos.y + 78;
			rcHit.right = pos.x - 80;
			rcHit.bottom = pos.y + img[5].GetImageInfo()->frameHeight - 15;
			break;
		case Chractor_STATE::SFOOT:
			if (frameCount == 0)
			{
				rcHit.left = pos.x - 250;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 70;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1 || frameCount == 2 || frameCount == 3 || frameCount == 4 || frameCount == 5)
			{
				rcHit.left = pos.x - 250;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 70;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 6 || frameCount == 7 || frameCount == 8)
			{
				rcHit.left = pos.x - 250;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 80;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x - 250;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 70;
				rcHit.bottom = pos.y + img[6].GetImageInfo()->frameHeight - 15;
			}

			break;
		case Chractor_STATE::COMBO:
			if (frameCount == 0)
			{
				rcHit.left = pos.x + 510 - img[7].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 110;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 1 || frameCount == 2)
			{
				rcHit.left = pos.x + 510 - img[7].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 120;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 3 || frameCount == 4)
			{
				rcHit.left = pos.x + 505 - img[7].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 125;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x + 510 - img[7].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 78;
				rcHit.right = pos.x - 135;
				rcHit.bottom = pos.y + img[7].GetImageInfo()->frameHeight - 15;
			}
			break;
		case Chractor_STATE::DOWN:
			if (frameCount == 0 || frameCount == 1 || frameCount == 2)
			{
				rcHit.left = pos.x + 180 - img[8].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 100;
				rcHit.right = pos.x - 90;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 3 || frameCount == 4 || frameCount == 5 || frameCount == 6)
			{
				rcHit.left = pos.x + 140 - img[8].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 110;
				rcHit.right = pos.x - 110;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 7)
			{
				rcHit.left = pos.x + 160 - img[8].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 120;
				rcHit.right = pos.x - 110;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else if (frameCount == 8 || frameCount == 9)
			{
				rcHit.left = pos.x + 125 - img[8].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 200;
				rcHit.right = pos.x - 45;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			else
			{
				rcHit.left = pos.x - img[8].GetImageInfo()->frameWidth;
				rcHit.top = pos.y + 270;
				rcHit.right = pos.x - 30;
				rcHit.bottom = pos.y + img[8].GetImageInfo()->frameHeight - 15;
			}
			break;
		}
	}
}

void Iori_2P::Iori_Set_AttackBox(int frameCount)
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
				rcAttack.left = pos.x - 150;
				rcAttack.top = pos.y + 170;
				rcAttack.right = pos.x - 350;
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
				rcAttack.left = pos.x - 360;
				rcAttack.top = pos.y + 80;
				rcAttack.right = pos.x - 405;
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
				rcAttack.left = pos.x - 150;
				rcAttack.top = pos.y + 190;
				rcAttack.right = pos.x - 380;
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
				rcAttack.left = pos.x - 150;
				rcAttack.top = pos.y + 130;
				rcAttack.right = pos.x - 460;
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
				rcAttack.left = pos.x - 375;
				rcAttack.top = pos.y + 230;
				rcAttack.right = pos.x - 447;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 7)
			{
				rcAttack.left = pos.x - 396;
				rcAttack.top = pos.y + 230;
				rcAttack.right = pos.x - 490;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 8)
			{
				rcAttack.left = pos.x - 426;
				rcAttack.top = pos.y + 250;
				rcAttack.right = pos.x - 513;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 9)
			{
				rcAttack.left = pos.x - 447;
				rcAttack.top = pos.y + 270;
				rcAttack.right = pos.x - 546;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 10)
			{
				rcAttack.left = pos.x - 486;
				rcAttack.top = pos.y + 300;
				rcAttack.right = pos.x - 566;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 11)
			{
				rcAttack.left = pos.x - 519;
				rcAttack.top = pos.y + 180;
				rcAttack.right = pos.x - 596;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 12)
			{
				rcAttack.left = pos.x - 546;
				rcAttack.top = pos.y + 180;
				rcAttack.right = pos.x - 627;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 13)
			{
				rcAttack.left = pos.x - 594;
				rcAttack.top = pos.y + 250;
				rcAttack.right = pos.x - 669;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 14)
			{
				rcAttack.left = pos.x - 621;
				rcAttack.top = pos.y + 300;
				rcAttack.right = pos.x - 684;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 15)
			{
				rcAttack.left = pos.x - 657;
				rcAttack.top = pos.y + 300;
				rcAttack.right = pos.x - 705;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 16)
			{
				rcAttack.left = pos.x - 684;
				rcAttack.top = pos.y + 300;
				rcAttack.right = pos.x - 732;
				rcAttack.bottom = pos.y + 387;
			}
			else if (frameCount == 17)
			{
				rcAttack.left = pos.x - 711;
				rcAttack.top = pos.y + 336;
				rcAttack.right = pos.x - 759;
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

Iori_2P::Iori_2P()
{
}

Iori_2P::~Iori_2P()
{
}
