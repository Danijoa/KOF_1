#pragma once
#pragma once
#include "GameNode.h"

class Image;

class KOF_Character : public GameNode
{
//protected:
//	const char* name;
//	Image* img;			//이미지 경로를 알려주기
//	FPOINT pos;			//이미지 가 윈도우 상에서 어디에 위치 할 것인가
//	int chracterFrame;			//몇 프레임으로 나눌 것인가
//	int frameCount;		//나눈 프레임을 하나씩 보여주기
//	int elapsedTime;	//몇 초 후에 다음 프레임으로 넘어 갈 것인가
//	int hp;
//	int attackValue;	//기술 마다 공격력

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

