#pragma once
#include "GameNode.h"

class Image;

class Chracter : public GameNode
{
private:
	Image* chracImage;
	FPOINT pos; 
	int elapedTime;	
	int chracFrame;			

public:
	//������â���� �̹�����  ��� ��ġ x, y, 
	//�̹��� ���, ���� ũ��, ���� ũ��, ���� ������, ���� ������
	//����ȭ �� r, g, b
	HRESULT Init(
		int winX, int winY,																			
		const char* imageName, int imageWidth, int imageHeight, int imageFrameX, int imageFrameY, 
		int r, int g, int b
	);
	void Release();			
	void Update(int frameX);
	void Render(HDC hdc);	
};

