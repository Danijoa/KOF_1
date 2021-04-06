#pragma once
#include "KOF_Character.h"
#include <vector>

class Image;
class Kyo_1P : public KOF_Character
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
	int kyo_SidePosition;	//1p로 선택되었는지 2p로 선택 되었는지 받아와서 위치 지정(1: 왼 / 2: 오른) 

	int imageSizeY;
	int imageSize[9];
	//Image* kyo_image[9];
	Image* kyo_stand;		//
	Image* kyo_walkFront;	//N
	Image* kyo_walkBack;	//V 
	Image* kyo_gangson;		//Q
	Image* kyo_gangbal;		//E
	Image* kyo_combo;		//QQE
	Image* kyo_yakson;		//A
	Image* kyo_yakbal;		//D
	Image* kyo_hitted;

	FPOINT rcHIT_pos;
	FPOINT rcHit_Size;
	RECT rcHit;
	RECT rcHit_temp;
	FPOINT rcAttack_pos;
	FPOINT rcAttack_Size;
	RECT rcAttack;
	RECT rcAttack_temp;

	bool canInput;			//다음 액션으로 넘어 갈 수  있는지

	//콤보 관련 변수
	vector<int> myV;		//공격 스킬 저장		
	int *comboStore;		//콤보 스킬 저장
	int elapsedTime2;		//콤보 입력 시간
	int elapsedTime3;		//벡터 마지막 스킬 저장 시간
	int storeLast;			//벡터 마지막 스킬 저장
	bool checkCombo;		//콤보 발생 여부

	bool moveback_R;
	bool moveback_L;

public:
	HRESULT Init();
	void Motion1P();		//V N A D Q E
	void CollisionRect();
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

	inline int getAttackValue() { return attackValue; }
	inline int getHP() { return hp; }
	inline void setHP(int enemyAttackValue) { this->hp -= enemyAttackValue; }

	//inline RECT getRcHit() { return rcHit; }
	//inline RECT getRcAttack() { return rcAttack; }
	inline RECT getRcHit() { return rcHit_temp; }
	inline RECT getRcAttack() { return rcAttack_temp; }
};
