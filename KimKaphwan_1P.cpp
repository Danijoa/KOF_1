#include "KimKaphwan_1P.h"
#include "Image.h"
#include "CommonFunction.h"
#include <vector>

HRESULT KimKaphwan_1P::Init()
{
	kim_SidePosition = 1;
	name = "KIM";
	pos.x = 200;
	pos.y = 100;
	hp = 100;

	characterFrame = 11;
	frameCount = 0;
	elapsedTime = 0;
	attackValue = 10;

	standing = new Image();
	if (FAILED(standing->Init("Image/kim_ngbc.bmp", 2541, 660, 11, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	sHand = new Image();
	if (FAILED(sHand->Init("Image/kimkap_sp.bmp", 1332, 660, 3, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	wHand = new Image();
	if (FAILED(wHand->Init("Image/kimkap_wp.bmp", 582, 660, 2, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	sFoot = new Image();
	if (FAILED(sFoot->Init("Image/kimkap_sk.bmp", 2088, 660, 6, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	wFoot = new Image();
	if (FAILED(wFoot->Init("Image/kimkap_wlk.bmp", 2664, 660, 6, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	front = new Image();
	if (FAILED(front->Init("Image/kimkap_walkf.bmp", 1512, 660, 6, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	back = new Image();
	if (FAILED(back->Init("Image/kimkap_walkb.bmp", 1800, 660, 6, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	combo = new Image();
	if (FAILED(combo->Init("Image/kimkap_super.bmp", 39468, 660, 46, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	down = new Image();
	if (FAILED(combo->Init("Image/kimkap_super.bmp", 5838, 660, 46, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "김갑환 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	canInput = true;
	comboStore = new int[3];
	comboStore[0] = 'Q';
	comboStore[1] = 'Q';
	comboStore[2] = 'E';
	elapsedTime2 = 0;
	elapsedTime3 = 0;
	storeLast = 0 - '0';
	checkCombo = false;

	moveback_R = false;
	moveback_L = false;

	return S_OK;
}

void KimKaphwan_1P::Motion1P()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('N') && canInput)
	{
		frameCount = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('N') && canInput)
	{
		if (kim_SidePosition == 1)	//1p가 오른쪽을 바라보는 경우
		{
			kimState = State::FRONT;
			characterFrame = 6;
		}
		if (kim_SidePosition == 2)	//1p가 왼쪽을 바라보는 경우
		{
			kimState = State::BACK;
			characterFrame = 6;
		}
		if (pos.x + 522 / 5 < WINSIZE_X - 10)
			pos.x += 3;
		if (pos.x + 522 / 5 > WINSIZE_X - 200)
			moveback_R = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('N') && canInput)
	{
		kimState = State::STAND;
		characterFrame = 11;
		frameCount = 0;
	}

	//뒤로 걷기
	if (KeyManager::GetSingleton()->IsOnceKeyDown('V') && canInput)
	{
		frameCount = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('V') && canInput)
	{
		if (kim_SidePosition == 1)	//1p가 오른쪽을 바라보는 경우
		{
			kimState = State::BACK;
			characterFrame = 6;
		}
		if (kim_SidePosition == 2)	//1p가 왼쪽을 바라보는 경우
		{
			kimState = State::FRONT;
			characterFrame = 6;
		}
		if (pos.x > 0 + 10)
			pos.x -= 3;
		if (pos.x < 0 + 150)
			moveback_L = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('V') && canInput)
	{
		kimState = State::STAND;
		characterFrame = 11;
		frameCount = 0;
	}

	//강손
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	{
		myV.push_back('Q');
		if (canInput)
		{
			canInput = false;
			kimState = State::SHAND;
			characterFrame = 3 + 1;
			frameCount = 0;
		}
	}

	//강발
	if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))
	{
		myV.push_back('E');
		if (canInput)
		{
			canInput = false;
			kimState = State::SFOOT;
			characterFrame = 6 + 1;
			frameCount = 0;
		}
	}

	//콤보
	if (checkCombo)
	{
		canInput = false;
		kimState = State::COMBO;
		characterFrame = 46 + 1;
		frameCount = 0;
		checkCombo = false;
		pos.x += 520;
	}

	//약손
	if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
	{
		myV.push_back('A');
		if (canInput)
		{
			canInput = false;
			kimState = State::WHAND;
			characterFrame = 2 + 1;
			frameCount = 0;
		}
	}

	//약발
	if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))
	{
		myV.push_back('D');
		if (canInput)
		{
			canInput = false;
			kimState = State::WFOOT;
			characterFrame = 6 + 1;
			frameCount = 0;
		}
	}
}

void KimKaphwan_1P::FrameCheck()
{
	elapsedTime++;
	if (elapsedTime >= 9)
	{
		frameCount = (frameCount + 1) % characterFrame;
		elapsedTime = 0;
	}
}

void KimKaphwan_1P::Update()
{
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
	if (!canInput && (kimState == State::SHAND || kimState == State::SFOOT || kimState == State::COMBO
		|| kimState == State::WFOOT || kimState == State::WHAND))
	{
		FrameCheck();

		if (frameCount + 1 == characterFrame)
		{
			kimState = State::STAND;
			characterFrame = 11;
			frameCount = 0;
			canInput = true;
		}
	}
	else
	{
		FrameCheck();
	}
}

void KimKaphwan_1P::Render(HDC hdc)
{
	char szText[100];
	wsprintf(szText, "myV[마지막] : %c", storeLast);
	TextOut(hdc, 10, 2, szText, strlen(szText));
	if (!myV.empty())
	{
		for (int i = 0; i < myV.size(); i++)	//벡터 안에 있는 값 확인 용 코드
		{
			wsprintf(szText, "myV[ %d ] : %c", i, myV[i]);
			TextOut(hdc, 10, 20 * (i + 1), szText, strlen(szText));
		}
	}

	//모션 렌더
	if (kim_SidePosition == 1)
	{
		switch (kimState)
		{
		case State::STAND:
			standing->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::FRONT:
			front->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::BACK:
			back->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::SHAND:
			sHand->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::SFOOT:
			sFoot->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::COMBO:
			combo->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WHAND:
			wHand->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WFOOT:
			wFoot->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::DOWN:
			down->Render(hdc, pos.x, pos.y, frameCount);
			break;
		}
	}
	else if (kim_SidePosition == 2)
	{
		switch (kimState)
		{
		case State::STAND:
			standing->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::FRONT:
			front->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::BACK:
			back->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::SHAND:
			sHand->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::SFOOT:
			sFoot->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::COMBO:
			combo->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WHAND:
			wHand->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WFOOT:
			wFoot->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::DOWN:
			down->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		}
	}
}

void KimKaphwan_1P::Release()
{
	if (standing)
	{
		standing->Release();
		delete standing;
		standing = nullptr;
	}

	if (sHand)
	{
		sHand->Release();
		delete sHand;
		sHand = nullptr;
	}

	if (wHand)
	{
		wHand->Release();
		delete wHand;
		wHand = nullptr;
	}

	if (sFoot)
	{
		sFoot->Release();
		delete sFoot;
		sFoot = nullptr;
	}

	if (wFoot)
	{
		wFoot->Release();
		delete wFoot;
		wFoot = nullptr;
	}

	if (front)
	{
		front->Release();
		delete front;
		front = nullptr;
	}

	if (back)
	{
		back->Release();
		delete back;
		back = nullptr;
	}

	if (combo)
	{
		combo->Release();
		delete combo;
		combo = nullptr;
	}
}
