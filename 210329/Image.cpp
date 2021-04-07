#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);	//윈도우가 총괄하는 hwnd 가져오자

	imageInfo = new IMAGE_INFO;
	//imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);	//메모리 dc(Device Context/핸들)를 통해 bitmap에 있는 이미지 정보에 접근
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;	//빈 파일

	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hBitmap2);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)	// 예외처리
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
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;	//이미지 파일

	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hBitmap2);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)	// 예외처리
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
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;	//이미지 파일

	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap2 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hBitmap2);

	imageInfo->maxFrameX = maxFrameX;							//이오리 standig.bmp경우 9
	imageInfo->maxFrameY = maxFrameY;							//1
	imageInfo->frameWidth = imageInfo->width / maxFrameX;		//612 / 9
	imageInfo->frameHeight = imageInfo->height / maxFrameY;		//104 / 1
	imageInfo->curFrameX = 0;
	imageInfo->curFrameY = 0;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)	// 예외처리
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
	if (imageInfo)	//생성되어 있는 상태면
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

//윈도우 상 x,y 좌표
void Image::Render(HDC hdc, int winX, int winY)
{
	if (isTransparent == true)	//특정(마젠타) 색을 빼고 싶을 때, 해당 색상을 빼고 복사하는 함수
	{
		GdiTransparentBlt(
			hdc,				
			winX, winY,
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC,						//이 친구가 관리하고 있는 비트맵 DC에(원본 출발지 DC)
			0,0,									//여기 시작
			imageInfo->width, imageInfo->height,	//이 크기로 복사하는데 
			transColor								//빼고 싶은 색상이 이것이다
			);
	}
	else
	{
		//bitmap에 있는 이미지 정보를 다른 비트맵에 복사
		BitBlt(
			hdc,									//복사가 될 목적지 DC
			winX, winY,								//복사판에서 복사가 시작될 위치
			imageInfo->width, imageInfo->height,	//원본에서 복사될 이미지의 가로, 세로 크기
			imageInfo->hMemDC,						//원본 출발지 DC
			0, 0,									//원본에서 복사 시작될 위치
			SRCCOPY									//복사 옵션(그대로 복사로 선택)
		);
	}
}

//윈도우 상 x,y 좌표 / 프레임인덱스
void Image::Render(HDC hdc, int winX, int winY, int frame)
{
	imageInfo->curFrameX = frame;

	if (isTransparent == true)	//특정(마젠타) 색을 빼고 싶을 때, 해당 색상을 빼고 복사하는 함수
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

//애니메이션 좌우 반전 출력
void Image::RenderFlip(HDC hdc, int destX, int destY, int frameIndex)
{
	imageInfo->curFrameX = frameIndex;
	//frameIndex는 나뉘어진 프레임 중 몇번째 위치한 프레임을 가져와서 반전시키려는지 확인을 위한 변수,
	//frameCount는 총 나뉘어진 프레임 개수?? 예를들어 이오리 서있는 이미지는 9개로 나뉘어 져 있으니까 frameCount=9 인가요? 

	if (isTransparent)
	{
		StretchBlt(
			imageInfo->hTempDC,										//임이의 비어있는 hTempDC로 복사를 한다 
			0, 0,													//0,0 부터 복사를 시작한다
			imageInfo->frameWidth,									//복사하는 이미지의 가로 크기
			imageInfo->frameHeight,									//복사하는 이미지의 세로 크기
			imageInfo->hMemDC,										//hMemDC에서 이미지를 가져온다
			imageInfo->frameWidth * imageInfo->curFrameX,			//복사가 시작되는 원본 이미지의 x 위치
			imageInfo->frameHeight * imageInfo->curFrameY,			//복사가 시작되는 원본 이미지의 y 위치
			-1 * (imageInfo->frameWidth),							//가져오는 이미지의 가로 크기(-1은 음의 방향으로 읽어온다..?)
			imageInfo->frameHeight,									//가져오는 이미지의 세로 크기
			SRCCOPY													//복사할때 원본으로 복사
		);
		GdiTransparentBlt(
			hdc,													
			destX, destY,											//윈도우 창 위에 그려주고 싶은 x,y 위치 									
			imageInfo->frameWidth,
			imageInfo->frameHeight,							
			imageInfo->hTempDC,										//hTempDC로 부터 이미지를 가져와서 복사를 한다                    
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

//바 출력
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