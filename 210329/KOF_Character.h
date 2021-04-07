#pragma once
#pragma once
#include "GameNode.h"
#include <vector>

class Image;

class KOF_Character : public GameNode
{
public:
	//����
	enum class State { STAND, FRONT, BACK, WHAND, SHAND, WFOOT, SFOOT, COMBO, DOWN, WIN };
protected:
	//ĳ���� ����
	const char* name;		//�̸�
	FPOINT pos;				//��ġ
	int hp;					//ü��

	//����
	State curState;
	
	//��ġ�� ������ �ٶ󺸴���, ���������� �ٶ󺸴���
	int curSidePosition;
	
	//��ǿ� ����
	int characterFrame;		//������ �� ����
	int frameCount;			//������ �ε���

	//��� ������ ������Ʈ �ð� ����
	int elapsedTime;

	//���ݷ�
	int attackValue;

	//Ű �Է� ����
	bool canInput;

	//��ų ����
	vector<int> myV;

	//�浹 �ڽ�
	RECT rcHit;
	RECT rcAttack;

	//��� �¿� ����
	bool moveback_R;
	bool moveback_L;

public:
	//
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	//��ġ
	inline int getPosX() { return pos.x; }
	inline void setSidePos(int sidePos) { this->curSidePosition = sidePos; }

	//���
	inline int getBackMove_R() { return moveback_R; }
	inline void setBackMove_R(bool b) { this->moveback_R = b; }
	inline int getBackMove_L() { return moveback_L; }
	inline void setBackMove_L(bool b) { this->moveback_L = b; }

	//HP
	inline int getAttackValue() { return attackValue; }
	inline int getHP() { return hp; }
	inline void setHP(int enemyAttackValue) { this->hp -= enemyAttackValue; }

	//�浹
	inline RECT getRcHit() { return rcHit; }
	inline RECT getRcAttack() { return rcAttack; }

	//��� ����
	inline void setWin() { this->curState = State::WIN; }

};

