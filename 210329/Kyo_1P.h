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
	int kyo_SidePosition;	//1p로 선택되었는지 2p로 선택 되었는지 받아와서 위치 지정(1: 왼 / 2: 오른) 

	//이미지 변수(다음에는 그냥 Image* kyo_image[11]; 이런식으로 하자)
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

	//충돌 박스
	FPOINT rcHIT_pos;
	FPOINT rcHit_Size;
	RECT rcHit;
	RECT rcHit_temp;
	FPOINT rcAttack_pos;
	FPOINT rcAttack_Size;
	RECT rcAttack;
	RECT rcAttack_temp;

	//키 입력 제어
	bool canInput;			//다음 액션으로 넘어 갈 수  있는지

	//콤보 관련 변수
	vector<int> myV;		//공격 스킬 저장		
	int* comboStore;		//콤보 스킬 저장
	int elapsedTime2;		//콤보 입력 시간
	int elapsedTime3;		//벡터 마지막 스킬 저장 시간
	int storeLast;			//벡터 마지막 스킬 저장
	bool checkCombo;		//콤보 발생 여부

	//배경
	bool moveback_R;
	bool moveback_L;

	//down 상태 일때 사용
	bool isOnce;

	//충돌 정보
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

	//위치
	inline int getPosX() { return pos.x; }
	inline void setSidePos(int sidePos) { this->kyo_SidePosition = sidePos; }

	//배경
	inline int getBackMove_R() { return moveback_R; }
	inline void setBackMove_R(bool b) { this->moveback_R = b; }
	inline int getBackMove_L() { return moveback_L; }
	inline void setBackMove_L(bool b) { this->moveback_L = b; }

	//hp
	inline int getAttackValue() { return attackValue; }
	inline int getHP() { return hp; }
	inline void setHP(int enemyAttackValue) { this->hp -= enemyAttackValue; }

	//충돌
	inline RECT getRcHit() { return rcHit_temp; }
	inline RECT getRcAttack() { return rcAttack_temp; }
	inline void SetHitCheck(bool hitCheck) { this->hitCheck = hitCheck; }

	//우승 상태로 변경
	inline void setWin() { this->kyoState = State::WIN; }
};
