#pragma once
#include "config.h"

class Image
{
public: 
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,	//������Ʈ ��ü�� ���� ��ų �̹���
		FILE,		//�ܺο��� �ε� �� �̹���
		EMPTY,		//��ü ���� �̹��� -> �� ��Ʈ���� ����ؼ� ������ �����Ѵ�
		END
	};

	typedef struct tagImageInfo	
	{
		DWORD resID;		//���ν��� ������ id
		HDC hMemDC;			//�׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;	//�̹��� ����
		HBITMAP hOldBit;	//�⺻ �̹��� ����
		int width;			//�̹��� ���� ũ��(y)
		int height;			//�̹��� ���� ũ��(x)
		BYTE loadType;		//�ε� Ÿ��

		HDC hTempDC;		//�ӽ÷� �̹����� ��� �� DC�ڵ�
		HBITMAP hBitmap2;
		HBITMAP hOldBit2;

		//�ִϸ��̼�(������) ���� ����
		int maxFrameX, maxFrameY;
		int frameWidth, frameHeight;
		int curFrameX, curFrameY;

		tagImageInfo()	//����ü ������(�ʱ�ȭ �ص���)
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
	IMAGE_INFO* imageInfo;	//�̹��� ���� ����ü ���� 
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;		//���� üũ
	COLORREF transColor;

public:
	//�� ��Ʈ�� �̹��� ���� �Լ�
	HRESULT Init(int width, int height);

	//���Ϸ� ���� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	//���Ϸ� ���� �̹����� �ε��ϴ� �Լ�2
	HRESULT Init(const char* fileName, int width, int height, 
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	//ȭ�鿡 ���
	void Render(HDC hdc, int winX = 0, int winY = 0);	//�ŰԺ����� x��y�� �Ѱ����� �ʴ� ��� ���õǴ� ��(���������� ���� ������ �ʱ�ȭ �Ǿ� �־�� ��)
	void Render(HDC hdc, int winX, int winY, int frame);

	//�ִϸ��̼� �¿� ���� ���
	void RenderFlip(HDC hdc, int destX, int destY, int frameIndex);

	void Release();

	//get set
	inline HDC GetMemDC() 
	{	
		if(this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	};

	///////////// �߰��κ� - �浹 ////////////
	inline IMAGE_INFO* GetImageInfo() { return this->imageInfo; }

};

