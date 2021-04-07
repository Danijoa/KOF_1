#pragma once
#include "KOF_Character.h"
#include <vector>

class Image;
class KimKaphwan_1P : public KOF_Character
{
public:
	enum class State { STAND, FRONT, BACK, WHAND, SHAND, WFOOT, SFOOT, COMBO, DOWN, WIN };
private:
	const char* name;
	FPOINT pos;
	int hp;

	int attackValue;
	int elapsedTime;
	int characterFrame;
	int frameCount;

	State kimState;
	int kim_SidePosition;

	Image* standing;
	Image* front;
	Image* back;
	Image* wHand;
	Image* sHand;
	Image* wFoot;
	Image* sFoot;
	Image* down;
	Image* combo;
	//////////////
	Image* kim_win;
	Image* kim_bar_1P;

	bool canInput;

	vector<int> myV;		//���� ��ų ����		
	int* comboStore;		//�޺� ��ų ����
	int elapsedTime2;		//�޺� �Է� �ð�
	int elapsedTime3;		//���� ������ ��ų ���� �ð�
	int storeLast;			//���� ������ ��ų ����
	bool checkCombo;		//�޺� �߻� ����

	//Ÿ�� �ǰ�
	RECT rcHit;				//�ǰ�
	RECT rcAttack;			//Ÿ��

	bool moveback_R;
	bool moveback_L;

	//////////////////////
	bool isOnce;

public:
	HRESULT Init();
	void Motion1P();		//V N A D Q E
	void ComboBox();
	void HitBox();
	void FrameCheck();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline int getPosX() { return pos.x; }
	inline void setSidePos(int sidePos) { this->kim_SidePosition = sidePos; }
	inline int getBackMove_R() { return moveback_R; }
	inline void setBackMove_R(bool b) { this->moveback_R = b; }
	inline int getBackMove_L() { return moveback_L; }
	inline void setBackMove_L(bool b) { this->moveback_L = b; }

	inline int getAttackValue() { return attackValue; }
	inline int getHP() { return hp; }
	inline void setHP(int enemyAttackValue) { this->hp -= enemyAttackValue; }

	inline RECT getRcHit() { return rcHit; }
	inline RECT getRcAttack() { return rcAttack; }

	//////////////////
	inline void setWin() { this->kimState = State::WIN; }
};

