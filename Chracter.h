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
	//윈도우창에서 이미지가  출력 위치 x, y, 
	//이미지 경로, 가로 크기, 세로 크기, 가로 프레임, 세로 프레임
	//투명화 할 r, g, b
	HRESULT Init(
		int winX, int winY,																			
		const char* imageName, int imageWidth, int imageHeight, int imageFrameX, int imageFrameY, 
		int r, int g, int b
	);
	void Release();			
	void Update(int frameX);
	void Render(HDC hdc);	
};

