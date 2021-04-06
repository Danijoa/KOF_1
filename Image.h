#pragma once
#include "config.h"

class Image
{
public: 
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,	//프로젝트 자체에 포함 시킬 이미지
		FILE,		//외부에서 로드 할 이미지
		EMPTY,		//자체 생상 이미지 -> 빈 비트맵을 사용해서 사진을 조작한다
		END
	};

	typedef struct tagImageInfo	
	{
		DWORD resID;		//리로스의 고유한 id
		HDC hMemDC;			//그리기를 주관하는 핸들
		HBITMAP hBitmap;	//이미지 정보
		HBITMAP hOldBit;	//기본 이미지 정보
		int width;			//이미지 가로 크기(y)
		int height;			//이미지 세로 크기(x)
		BYTE loadType;		//로드 타입

		HDC hTempDC;		//임시로 이미지를 담아 둘 DC핸들
		HBITMAP hBitmap2;
		HBITMAP hOldBit2;

		//애니메이션(프레임) 관련 변수
		int maxFrameX, maxFrameY;
		int frameWidth, frameHeight;
		int curFrameX, curFrameY;

		tagImageInfo()	//구조체 생성자(초기화 해두자)
		{
			resID = 0;
			hMemDC = NULL;
			hTempDC = NULL;
			hBitmap = NULL;
			hBitmap2 = NULL;
			hOldBit = NULL;
			hOldBit2 = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			maxFrameX = 0;
			maxFrameY=0;
			frameWidth = 0;
			frameHeight = 0;
			curFrameX = 0; 
			curFrameY = 0;
		};
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;	//이미지 정보 구조체 변수 
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;		//투명도 체크
	COLORREF transColor;

public:
	//빈 비트맵 이미지 생성 함수
	HRESULT Init(int width, int height);

	//파일로 부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	//파일로 부터 이미지를 로드하는 함수2
	HRESULT Init(const char* fileName, int width, int height, 
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	//화면에 출력
	void Render(HDC hdc, int winX = 0, int winY = 0);	//매게변수로 x와y를 넘겨주지 않는 경우 셋팅되는 값(문법적으로 뒷쪽 값부터 초기화 되어 있어야 함)
	void Render(HDC hdc, int winX, int winY, int frame);

	//애니메이션 좌우 반전 출력
	void RenderFlip(HDC hdc, int destX, int destY, int frameIndex);

	void Release();

	//get set
	inline HDC GetMemDC() 
	{	
		if(this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	};

	///////////// 추가부분 - 충돌 ////////////
	inline IMAGE_INFO* GetImageInfo() { return this->imageInfo; }

};

