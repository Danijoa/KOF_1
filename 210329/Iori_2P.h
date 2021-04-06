#pragma once
#include "KOF_Character.h"
#include <vector>


class Image;
class Iori_2P : public KOF_Character
{
public:
	enum class Chractor_STATE { FRONT, BACK, STAND, WHAND, SHAND, WFOOT, SFOOT, COMBO, DOWN };

private:
	const char* name;
	FPOINT pos;
	int hp;

	int attackValue;
	int elapsedTime;	//100�� �� ������ �ִϸ��̼� ������ 1�� ����
	int chracterFrame;
	int frameCount;
	int stateCount;		//�� ���� ���� - ���߿� ���� �߰��ϸ� �����Ϸ���

	Chractor_STATE ioriState;
	int iori_SidePosition;
	//9�� �̹���
	Image* img;

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

	///////////// �߰� �κ� - �浹 /////////////////
	RECT rcHit;
	RECT rcAttack;



public:

	HRESULT Init();
	void Motion2P();		//�� �� J L U O
	void FrameCheck();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline int getPosX() { return pos.x; }
	inline void setSidePos(int sidePos) { this->iori_SidePosition = sidePos; }
	inline int getBackMove_R() { return moveback_R; }
	inline void setBackMove_R(bool b) { this->moveback_R = b; }
	inline int getBackMove_L() { return moveback_L; }
	inline void setBackMove_L(bool b) { this->moveback_L = b; }

	inline int getAttackValue() { return attackValue; }
	inline int getHP() { return hp; }
	inline void setHP(int enemyAttackValue) { this->hp -= enemyAttackValue; }

	///////////// �߰� �κ� - �浹 /////////////////
	void Iori_Set_HitBox(int frameCount);
	void Iori_Set_AttackBox(int frameCount);

	inline RECT getRcHit() { return rcHit; }
	inline RECT getRcAttack() { return rcAttack; }

	Iori_2P();
	~Iori_2P();

};



