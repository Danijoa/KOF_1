#include "Iori_2P.h"
#include "CommonFunction.h"
#include "Image.h"
#include <vector>


HRESULT Iori_2P::Init()
{
	iori_SidePosition = 2;

	name = "Iori";
	pos.x = WINSIZE_X-700;
	pos.y = 300;
	hp = 100;

	chracterFrame = 7;
	frameCount = 0;
	elapsedTime = 0;	//������ ������ 100�� �� ������ �ִϸ��̼� ������ 1�� ����

	ioriState = Chractor_STATE::STAND;

	stateCount = 9;
	img = new Image[stateCount];

	if (FAILED(img[0].Init("Image/iori_walk_front.bmp", 1020 * 3, 138 * 3, 12, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_walk_front.bmp �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[1].Init("Image/iori_walk_back.bmp", 1020 * 3, 138 * 3, 12, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_walk_back.bmp �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[2].Init("Image/iori_standing.bmp", 539 * 3, 138 * 3, 7, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Iori_standing.bmp �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[3].Init("Image/iori_weak_hand.bmp", 812 * 3, 138 * 3, 7, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_weak_hand.bmp �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[4].Init("Image/iori_strong_hand.bmp", 1088 * 3, 138 * 3, 8, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_strong_hand �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[5].Init("Image/iori_weak_foot.bmp", 896 * 3, 138 * 3, 7, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_weak_foot.bmp �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[6].Init("Image/iori_strong_foot.bmp", 1694 * 3, 138 * 3, 11, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_strong_foot.bmp �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[7].Init("Image/iori_combo.bmp", 5016 * 3, 138 * 3, 19, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_combo �ε� ����", "���", MB_OK);
		return E_FAIL;
	}

	if (FAILED(img[8].Init("Image/iori_down_up.bmp", 2160 * 3, 138 * 3, 16, 1, TRUE, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/iori_down_up.bmp �ε� ����", "���", MB_OK);
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
	//������ �ȱ�
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

	//�ڷ� �ȱ�
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

	//����
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

	//����
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

	//�޺�
	if (checkCombo)
	{
		canInput = false;
		ioriState = Chractor_STATE::COMBO;
		chracterFrame = 19 + 1;
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
			ioriState = Chractor_STATE::WHAND;
			chracterFrame = 7 + 1;
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
}

void Iori_2P::Render(HDC hdc)
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
	if (iori_SidePosition == 1)
	{
		if (ioriState == Chractor_STATE::FRONT)
		{
			img[0].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::BACK)
		{
			img[1].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::STAND)
		{
			img[2].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WHAND)
		{
			img[3].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SHAND)
		{
			img[4].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WFOOT)
		{
			img[5].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SFOOT)
		{
			img[6].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::COMBO)
		{
			img[7].Render(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::DOWN)
		{
			img[8].Render(hdc, pos.x, pos.y, frameCount);
		}
	}

	if (iori_SidePosition == 2)
	{
		if (ioriState == Chractor_STATE::FRONT)
		{
			img[0].RenderFlip(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::BACK)
		{
			img[1].RenderFlip(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::STAND)
		{
			img[2].RenderFlip(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WHAND)
		{
			img[3].RenderFlip(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SHAND)
		{
			img[4].RenderFlip(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::WFOOT)
		{
			img[5].RenderFlip(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::SFOOT)
		{
			img[6].RenderFlip(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::COMBO)
		{
			img[7].RenderFlip(hdc, pos.x, pos.y, frameCount);
		}

		if (ioriState == Chractor_STATE::DOWN)
		{
			img[8].RenderFlip(hdc, pos.x, pos.y, frameCount);
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

Iori_2P::Iori_2P()
{
}

Iori_2P::~Iori_2P()
{
}
