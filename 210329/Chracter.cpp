#include "Chracter.h"
#include"Image.h"

HRESULT Chracter::Init()
{
	pos.x = WINSIZE_X / 4;
	pos.y = WINSIZE_Y - 200;

	chrac = new Image();
	if (FAILED(chrac->Init("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/Iori_walk.bmp 로드 실패", "경고", MB_OK);
			return E_FAIL;
	}
	elapedTime = 0;
	ioriFrame = 0;

	return S_OK;
}

void Chracter::Release()
{
	if (chrac)
	{
		chrac->Release();
		delete chrac;
		chrac = nullptr;
	}
}

void Chracter::Update()
{
	elapedTime++;
	if (elapedTime == 20)
	{
		ioriFrame = (ioriFrame + 1) % 9;
		elapedTime = 0;
	}
}

void Chracter::Render(HDC hdc)
{
	if (chrac)
	{
		//chrac->Render(hdc, pos.x + (612 / 9) * ioriFrame, pos.y, ioriFrame);
		chrac->Render(hdc, pos.x++, pos.y, ioriFrame);
	}
}
