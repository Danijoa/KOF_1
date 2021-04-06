#include "Kyo_2P.h"
#include "Image.h"
#include "CommonFunction.h"
#include <vector>

HRESULT Kyo_2P::Init()
{
	kyo_SidePosition = 2;

	name = "KYO";
	pos.x = WINSIZE_X - 700;
	pos.y = 300;
	hp = 100;

	characterFrame = 10;
	frameCount = 0;
	elapsedTime = 0;
	attackValue = 10;

	kyoState = State::STAND;

	kyo_stand = new Image();
	if (FAILED(kyo_stand->Init("Image/kyo_stand.bmp", 750 * 2, 190 * 2, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "stand �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	kyo_walkFront = new Image();
	if (FAILED(kyo_walkFront->Init("Image/kyo_walkfront.bmp", 460 * 2, 190 * 2, 5, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "������ �ȱ� �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	kyo_walkBack = new Image();
	if (FAILED(kyo_walkBack->Init("Image/kyo_walkback.bmp", 522 * 2, 190 * 2, 6, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "�ڰ� �ȱ� �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	kyo_gangson = new Image();
	if (FAILED(kyo_gangson->Init("Image/kyo_gangson.bmp", 952 * 2, 190 * 2, 7, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "���� �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	kyo_gangbal = new Image();
	if (FAILED(kyo_gangbal->Init("Image/kyo_gangbal.bmp", 1593 * 2, 190 * 2, 9, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "���� �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	kyo_combo = new Image();
	if (FAILED(kyo_combo->Init("Image/kyo_combo_motion.bmp", 2420 * 2, 190 * 2, 19, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "�޺� �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	kyo_yakson = new Image();
	if (FAILED(kyo_yakson->Init("Image/kyo_yakson.bmp", 630 * 2, 190 * 2, 5, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "��� �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	kyo_yakbal = new Image();
	if (FAILED(kyo_yakbal->Init("Image/kyo_yakbal.bmp", 1113 * 2, 190 * 2, 7, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "��� �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	kyo_hitted = new Image();
	if (FAILED(kyo_hitted->Init("Image/kyo_hitted.bmp", 3189 * 2, 190 * 2, 17, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "�޺� �ε� ����", "���", MB_OK);
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

void Kyo_2P::Motion2P()
{
	//������ �ȱ�
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

	//�ڷ� �ȱ�
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
		if (pos.x + 522 / 5 < WINSIZE_X - 10)
			pos.x += 3;
		if (pos.x + 522 / 5 > WINSIZE_X - 200)
			moveback_R = true;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT) && canInput)
	{
		kyoState = State::STAND;
		characterFrame = 10;
		frameCount = 0;
	}

	//����
	if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
	{
		myV.push_back('U');
		if (canInput)
		{
			canInput = false;
			kyoState = State::SHAND;
			characterFrame = 7 + 1;
			frameCount = 0;
		}
	}

	//����
	if (KeyManager::GetSingleton()->IsOnceKeyDown('O'))
	{
		myV.push_back('O');
		if (canInput)
		{
			canInput = false;
			kyoState = State::SFOOT;
			characterFrame = 9 + 1;
			frameCount = 0;
		}
	}

	//�޺�
	if (checkCombo)
	{
		canInput = false;
		kyoState = State::COMBO;
		characterFrame = 19 + 1;
		frameCount = 0;
		checkCombo = false;
	}

	//���
	if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
	{
		myV.push_back('J');
		if (canInput)
		{
			canInput = false;
			kyoState = State::WHAND;
			characterFrame = 5 + 1;
			frameCount = 0;
		}
	}

	//���
	if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
	{
		myV.push_back('L');
		if (canInput)
		{
			canInput = false;
			kyoState = State::WFOOT;
			characterFrame = 7 + 1;
			frameCount = 0;
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
	//���̶� ��ġ �ٲ�� kyo_SidePosition�� ���� �� ����

	//��ų ���� ����
	elapsedTime2++;
	if (elapsedTime2 >= 9 * 10)	//������ ������Ʈ�� 10�� �Ͼ�� ���͸� �����ش�
	{
		if (!myV.empty())
		{
			storeLast = myV[myV.size() - 1];	//�����ֱ� ���� ������ ������ ���� �������� ���������
		}
		myV.clear();
		elapsedTime2 = 0;
	}
	else
	{
		if (myV.size() > 2)		//���Ͱ� �������� �� �޺� �Է��� �Ͼ� ���°� Ȯ��
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
		if (myV.size() == 2)	//���Ͱ� �������� ������ �޺��� ���� ��츦 ����� �ڵ�
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
		storeLast = 0 - '0';	//����� ������ ������ ���� ���� �ð��� �帣�� ��������
		elapsedTime3 = 0;
	}

	//��ų ����
	Motion2P();

	//������ ����
	if (!canInput && (kyoState == State::SHAND || kyoState == State::SFOOT || kyoState == State::COMBO
		|| kyoState == State::WFOOT || kyoState == State::WHAND))
	{
		FrameCheck();

		if (frameCount + 1 == characterFrame)
		{
			kyoState = State::STAND;
			characterFrame = 10;
			frameCount = 0;
			canInput = true;
		}
	}
	else
	{
		FrameCheck();
	}
}

void Kyo_2P::Render(HDC hdc)
{
	char szText[100];
	wsprintf(szText, "myV[������] : %c", storeLast);
	TextOut(hdc, 900, 2, szText, strlen(szText));
	if (!myV.empty())
	{
		for (int i = 0; i < myV.size(); i++)	//���� �ȿ� �ִ� �� Ȯ�� �� �ڵ�
		{
			wsprintf(szText, "myV[ %d ] : %c", i, myV[i]);
			TextOut(hdc, 900, 20 * (i + 1), szText, strlen(szText));
		}
	}

	//��� ����
	if (kyo_SidePosition == 1)
	{
		switch (kyoState)
		{
		case State::STAND:
			kyo_stand->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::FRONT:
			kyo_walkFront->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::BACK:
			kyo_walkBack->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::SHAND:
			kyo_gangson->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::SFOOT:
			kyo_gangbal->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::COMBO:
			kyo_combo->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WHAND:
			kyo_yakson->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WFOOT:
			kyo_yakbal->Render(hdc, pos.x, pos.y, frameCount);
			break;
		case State::DOWN:
			kyo_hitted->Render(hdc, pos.x, pos.y, frameCount);
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
			kyo_gangson->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::SFOOT:
			kyo_gangbal->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::COMBO:
			kyo_combo->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WHAND:
			kyo_yakson->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::WFOOT:
			kyo_yakbal->RenderFlip(hdc, pos.x, pos.y, frameCount);
			break;
		case State::DOWN:
			kyo_hitted->RenderFlip(hdc, pos.x, pos.y, frameCount);
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