#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);	//�����찡 �Ѱ��ϴ� hwnd ��������

	imageInfo = new IMAGE_INFO;
	//imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//�޸� dc(Device Context/�ڵ�)�� ���� bitmap�� �ִ� �̹��� ������ ����
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;	//�� ����

	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hBitmap2);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)	// ����ó��
	{
		Release();
		return E_FAIL;
	}

	this->isTransparent = FALSE;
	this->transColor = FALSE;

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, 
	bool isTransparent, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;	//�̹��� ����

	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hBitmap2);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)	// ����ó��
	{
		Release();
		return E_FAIL;
	}

	this->isTransparent = isTransparent;
	this->transColor = transColor;

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, 
	int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;	//�̹��� ����

	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hBitmap2);

	imageInfo->maxFrameX = maxFrameX;							//�̿��� standig.bmp��� 9
	imageInfo->maxFrameY = maxFrameY;							//1
	imageInfo->frameWidth = imageInfo->width / maxFrameX;		//612 / 9
	imageInfo->frameHeight = imageInfo->height / maxFrameY;		//104 / 1
	imageInfo->curFrameX = 0;
	imageInfo->curFrameY = 0;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)	// ����ó��
	{
		Release();
		return E_FAIL;
	}

	this->isTransparent = isTransparent;
	this->transColor = transColor;

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)	//�����Ǿ� �ִ� ���¸�
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
		DeleteObject(imageInfo->hBitmap);
		SelectObject(imageInfo->hMemDC, imageInfo->hBitmap2);
		DeleteObject(imageInfo->hBitmap2);
		DeleteDC(imageInfo->hMemDC);
		DeleteDC(imageInfo->hTempDC);

		delete imageInfo;
		imageInfo = nullptr;
	}
}

//������ �� x,y ��ǥ
void Image::Render(HDC hdc, int winX, int winY)
{
	if (isTransparent == true)	//Ư��(����Ÿ) ���� ���� ���� ��, �ش� ������ ���� �����ϴ� �Լ�
	{
		GdiTransparentBlt(
			hdc,				
			winX, winY,
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC,						//�� ģ���� �����ϰ� �ִ� ��Ʈ�� DC��(���� ����� DC)
			0,0,									//���� ����
			imageInfo->width, imageInfo->height,	//�� ũ��� �����ϴµ� 
			transColor								//���� ���� ������ �̰��̴�
			);
	}
	else
	{
		//bitmap�� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
		BitBlt(
			hdc,									//���簡 �� ������ DC
			winX, winY,								//�����ǿ��� ���簡 ���۵� ��ġ
			imageInfo->width, imageInfo->height,	//�������� ����� �̹����� ����, ���� ũ��
			imageInfo->hMemDC,						//���� ����� DC
			0, 0,									//�������� ���� ���۵� ��ġ
			SRCCOPY									//���� �ɼ�(�״�� ����� ����)
		);
	}
}

//������ �� x,y ��ǥ / �������ε���
void Image::Render(HDC hdc, int winX, int winY, int frame)
{
	imageInfo->curFrameX = frame;

	if (isTransparent == true)	//Ư��(����Ÿ) ���� ���� ���� ��, �ش� ������ ���� �����ϴ� �Լ�
	{
		GdiTransparentBlt(
			hdc, winX, winY, 
			imageInfo->frameWidth, imageInfo->frameHeight,
			imageInfo->hMemDC, 
			imageInfo->frameWidth * imageInfo->curFrameX, imageInfo->frameHeight * imageInfo->curFrameY,
			imageInfo->frameWidth, imageInfo->frameHeight, 
			transColor);
	}
	else
	{
		BitBlt(
			hdc, winX, winY, 
			imageInfo->frameWidth, imageInfo->frameHeight, 
			imageInfo->hMemDC, 
			imageInfo->frameWidth * imageInfo->curFrameX, 
			imageInfo->frameHeight * imageInfo->curFrameY, 
			SRCCOPY);
	}
}

//�ִϸ��̼� �¿� ���� ���
void Image::RenderFlip(HDC hdc, int destX, int destY, int frameIndex)
{
	imageInfo->curFrameX = frameIndex;
	//frameIndex�� �������� ������ �� ���° ��ġ�� �������� �����ͼ� ������Ű������ Ȯ���� ���� ����,
	//frameCount�� �� �������� ������ ����?? ������� �̿��� ���ִ� �̹����� 9���� ������ �� �����ϱ� frameCount=9 �ΰ���? 

	if (isTransparent)
	{
		StretchBlt(
			imageInfo->hTempDC,										//������ ����ִ� hTempDC�� ���縦 �Ѵ� 
			0, 0,													//0,0 ���� ���縦 �����Ѵ�
			imageInfo->frameWidth,									//�����ϴ� �̹����� ���� ũ��
			imageInfo->frameHeight,									//�����ϴ� �̹����� ���� ũ��
			imageInfo->hMemDC,										//hMemDC���� �̹����� �����´�
			imageInfo->frameWidth * imageInfo->curFrameX,			//���簡 ���۵Ǵ� ���� �̹����� x ��ġ
			imageInfo->frameHeight * imageInfo->curFrameY,			//���簡 ���۵Ǵ� ���� �̹����� y ��ġ
			-1 * (imageInfo->frameWidth),							//�������� �̹����� ���� ũ��(-1�� ���� �������� �о�´�..?)
			imageInfo->frameHeight,									//�������� �̹����� ���� ũ��
			SRCCOPY													//�����Ҷ� �������� ����
		);
		GdiTransparentBlt(
			hdc,													
			destX, destY,											//������ â ���� �׷��ְ� ���� x,y ��ġ 									
			imageInfo->frameWidth,
			imageInfo->frameHeight,							
			imageInfo->hTempDC,										//hTempDC�� ���� �̹����� �����ͼ� ���縦 �Ѵ�                    
			0,
			0,
			imageInfo->frameWidth, imageInfo->frameHeight,
			transColor             
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			imageInfo->frameWidth,					
			imageInfo->frameHeight,						
			imageInfo->hMemDC,
			imageInfo->frameWidth * imageInfo->curFrameX, 0,
			SRCCOPY
		);
	}
}

//�� ���
void Image::RenderBar(HDC hdc, int winX, int winY, int width, int height)
{
	BitBlt(
		hdc,
		winX, winY,
		width, height,
		imageInfo->hMemDC,
		0, 0,
		SRCCOPY
	);
}