#pragma once
#pragma once
#include "GameNode.h"

class Image;

class KOF_Character : public GameNode
{
//protected:
//	const char* name;
//	Image* img;			//�̹��� ��θ� �˷��ֱ�
//	FPOINT pos;			//�̹��� �� ������ �󿡼� ��� ��ġ �� ���ΰ�
//	int chracterFrame;			//�� ���������� ���� ���ΰ�
//	int frameCount;		//���� �������� �ϳ��� �����ֱ�
//	int elapsedTime;	//�� �� �Ŀ� ���� ���������� �Ѿ� �� ���ΰ�
//	int hp;
//	int attackValue;	//��� ���� ���ݷ�

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

