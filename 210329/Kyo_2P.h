#pragma once
#include "KOF_Character.h"
#include <vector>

class Image;
class Kyo_2P : public KOF_Character
{
public:
	enum class State { STAND, FRONT, BACK, WHAND, SHAND, WFOOT, SFOOT, COMBO, DOWN };
private:
	const char* name;
	FPOINT pos;
	int hp;

	int attackValue;
	int elapsedTime;
	int characterFrame;
	int frameCount;

	State kyoState;
	int kyo_SidePosition;	//1p�� ���õǾ����� 2p�� ���� �Ǿ����� �޾ƿͼ� ��ġ ����(1: �� / 2: ����) 

	//Image* kyo_image[9];
	Image* kyo_stand;		
	Image* kyo_walkFront;	//��
	Image* kyo_walkBack;	//�� 
	Image* kyo_gangson;		//U
	Image* kyo_gangbal;		//O
	Image* kyo_combo;		//UUO
	Image* kyo_yakson;		//J
	Image* kyo_yakbal;		//L
	Image* kyo_hitted;

	bool canInput;			//���� �׼����� �Ѿ� �� ��  �ִ���

	//�޺� ���� ����
	vector<int> myV;		//���� ��ų ����		
	int* comboStore;		//�޺� ��ų ����
	int elapsedTime2;		//�޺� �Է� �ð�
	int elapsedTime3;		//���� ������ ��ų ���� �ð�
	int storeLast;			//���� ������ ��ų ����
	bool checkCombo;		//�޺� �߻� ����

	bool moveback_R;
	bool moveback_L;

public:
	HRESULT Init();
	void Motion2P();		//�� �� J L U O
	void FrameCheck();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline int getPosX() { return pos.x; }
	inline void setSidePos(int sidePos) { this->kyo_SidePosition = sidePos; }
	inline int getBackMove_R() { return moveback_R; }
	inline void setBackMove_R(bool b) { this->moveback_R = b; }
	inline int getBackMove_L() { return moveback_L; }
	inline void setBackMove_L(bool b) { this->moveback_L = b; }
};
