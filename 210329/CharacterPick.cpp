#include "CharacterPick.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT CharacterPick::Init()
{
	KeyManager::GetSingleton()->Init();

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	backGround = new Image();
	backGround->Init("Image/mapImage.bmp", WINSIZE_X, WINSIZE_Y);

	//1P ���� ĳ���� â
	shape1P = new RECT[3];
	for(int i=0; i<3; i++)
		shape1P[i] = GetRect(150 + 100*i, WINSIZE_Y - 150, 70, 70);	//��ġ �̸� ���

	small_1p = new Image[3];
	small_1p[0].Init("Image/kyo_pick.bmp", 70, 70);
	small_1p[1].Init("Image/iori_pick.bmp", 70, 70);
	small_1p[2].Init("Image/kim_pick.bmp", 70, 70);


	//2P ���� ĳ���� â
	shape2P = new RECT[3];
	for (int i = 0; i < 3; i++)
		shape2P[i] = GetRect(970 + 100 * i, WINSIZE_Y - 150, 70, 70);

	small_2p = new Image[3];
	small_2p[0].Init("Image/kyo_pick.bmp", 70, 70);
	small_2p[1].Init("Image/iori_pick.bmp", 70, 70);
	small_2p[2].Init("Image/kim_pick.bmp", 70, 70);

	//1P ū ĳ���� â
	big_1p = new Image[3];
	big_1p[0].Init("Image/kyo_pick.bmp", 500, 500);
	big_1p[1].Init("Image/iori_pick.bmp", 500, 500);
	big_1p[2].Init("Image/kim_pick.bmp", 500, 500);

	//2P ū ĳ���� â
	big_2p = new Image[3];
	big_2p[0].Init("Image/kyo_pick.bmp", 500, 500);
	big_2p[1].Init("Image/iori_pick.bmp", 500, 500);
	big_2p[2].Init("Image/kim_pick.bmp", 500, 500);

	//ĳ���� ����
	nameCheck[0] = "kyo";	nameCheck[1] = "iori";	nameCheck[2] = "kim";
	curPick = false;											//false: 1P true:2p
	curSmall_1P = 0; curSmall_2P = 0;							//����ڰ� ���� â�� ����Ű�� �ִ� ĳ����(0:�� 2:�̿��� 3:��)

	//���� �� üũ
	nextScene = false;
	isInited = true;

	return S_OK;
}

void CharacterPick::Update()
{
	if (!curPick)	//1P ����
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))
		{
			curSmall_1P--;
			if (curSmall_1P < 0)
				curSmall_1P = 2;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('N'))
		{
			curSmall_1P = (curSmall_1P + 1) % 3;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))	//1p ���� �Ϸ�
		{
			curPick = true;
		}
	}
	else if (curPick)	//2P ����
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			curSmall_2P--;
			if (curSmall_2P < 0)
				curSmall_2P = 2;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			curSmall_2P = (curSmall_2P + 1) % 3;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))	//2p ���� �Ϸ� �� ��Ʋ ������
		{
			//Sleep();
			nextScene = true;
		}
	}

	InvalidateRect(g_hWnd, NULL, false);
}

void CharacterPick::Release()
{
	KeyManager::GetSingleton()->Release();

	backBuffer->Release();
	delete backBuffer;
	backBuffer = nullptr;

	backGround->Release();
	delete backGround;
	backGround = nullptr;

	for (int i = 0; i < 3; i++)
	{
		big_1p[i].Release();
		small_1p[i].Release();
		big_2p[i].Release();
		small_2p[i].Release();
	}
	delete big_1p;
	big_1p = nullptr;
	delete small_1p;
	small_1p = nullptr;
	delete big_2p;
	big_2p = nullptr;
	delete small_2p;
	small_2p = nullptr;

	KillTimer(g_hWnd, 0);
}

void CharacterPick::Render(HDC hdc)
{
	HDC hBack = backBuffer->GetMemDC();

	//���
	if (backGround)
		backGround->Render(hBack);

	//1P �������� Ȯ�ο�
	wsprintf(text1P, "1P %s", nameCheck[curSmall_1P]);
	TextOut(hBack, 150, 10, text1P, strlen(text1P));

	//2p �������� Ȯ�ο�
	wsprintf(text2P, "2P %s", nameCheck[curSmall_2P]);
	TextOut(hBack, 970, 10, text2P, strlen(text2P));

	//���� ĳ���� â
	for (int i = 0; i < 3; i++)
	{
		if (small_1p)
			small_1p[i].Render(hBack, shape1P[i].left, shape1P[i].top);
		if (small_2p)
			small_2p[i].Render(hBack, shape2P[i].left, shape2P[i].top);
	}

	//ū ĳ���� â
	if (big_1p)
		big_1p[curSmall_1P].Render(hBack, 100, 50);

	if (big_2p)
		big_2p[curSmall_2P].Render(hBack, 900, 50);

	backBuffer->Render(hdc);
}

LRESULT CharacterPick::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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

CharacterPick::CharacterPick()
{
	isInited = false;
}

CharacterPick::~CharacterPick()
{
}
