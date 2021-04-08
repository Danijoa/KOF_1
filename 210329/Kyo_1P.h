#pragma once
#include "KOF_Character.h"
#include <vector>

class Image;
class Kyo_1P : public KOF_Character
{
public:
	enum class State { STAND, FRONT, BACK, WHAND, SHAND, WFOOT, SFOOT, COMBO, HIT, DOWN, INIT, WIN };
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

	//�̹��� ����(�������� �׳� Image* kyo_image[11]; �̷������� ����)
	int imageSizeY;
	int imageSize[11];
	Image* kyo_stand;		
	Image* kyo_walkFront;	//N
	Image* kyo_walkBack;	//V 
	Image* kyo_gangson;		//Q
	Image* kyo_gangbal;		//E
	Image* kyo_combo;		//QQE
	Image* kyo_yakson;		//A
	Image* kyo_yakbal;		//D
	Image* kyo_hitted;		
	Image* kyo_hit;
	Image* kyo_init;
	Image* kyo_win;
	Image* kyo_bar_1P;

	//�浹 �ڽ�
	FPOINT rcHIT_pos;
	FPOINT rcHit_Size;
	RECT rcHit;
	RECT rcHit_temp;
	FPOINT rcAttack_pos;
	FPOINT rcAttack_Size;
	RECT rcAttack;
	RECT rcAttack_temp;

	//Ű �Է� ����
	bool canInput;			//���� �׼����� �Ѿ� �� ��  �ִ���

	//�޺� ���� ����
	vector<int> myV;		//���� ��ų ����		
	int* comboStore;		//�޺� ��ų ����
	int elapsedTime2;		//�޺� �Է� �ð�
	int elapsedTime3;		//���� ������ ��ų ���� �ð�
	int storeLast;			//���� ������ ��ų ����
	bool checkCombo;		//�޺� �߻� ����

	//���
	bool moveback_R;
	bool moveback_L;

	//down ���� �϶� ���
	bool isOnce;

	//�浹 ����
	bool hitCheck;
	bool isOnceHit;

public:
	HRESULT Init();
	void Motion1P();		//V N A D Q E
	void CollisionRect();
	void FrameCheck();
	void Update();
	void Render(HDC hdc);
	void Release();

	//��ġ
	inline int getPosX() { return pos.x; }
	inline void setSidePos(int sidePos) { this->kyo_SidePosition = sidePos; }

	//���
	inline int getBackMove_R() { return moveback_R; }
	inline void setBackMove_R(bool b) { this->moveback_R = b; }
	inline int getBackMove_L() { return moveback_L; }
	inline void setBackMove_L(bool b) { this->moveback_L = b; }

	//hp
	inline int getAttackValue() { return attackValue; }
	inline int getHP() { return hp; }
	inline void setHP(int enemyAttackValue) { this->hp -= enemyAttackValue; }

	//�浹
	inline RECT getRcHit() { return rcHit_temp; }
	inline RECT getRcAttack() { return rcAttack_temp; }
	inline void SetHitCheck(bool hitCheck) { this->hitCheck = hitCheck; }

	//��� ���·� ����
	inline void setWin() { this->kyoState = State::WIN; }
};
