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
	int elapsedTime;	//100이 될 때마다 애니메이션 프레임 1씩 증가
	int chracterFrame;
	int frameCount;
	int stateCount;		//총 동작 개수 - 나중에 동작 추가하면 변경하려고

	Chractor_STATE ioriState;
	int iori_SidePosition;
	//9개 이미지
	Image* img;

	bool canInput;			//다음 액션으로 넘어 갈 수  있는지

	//콤보 관련 변수
	vector<int> myV;		//공격 스킬 저장		
	int* comboStore;		//콤보 스킬 저장
	int elapsedTime2;		//콤보 입력 시간
	int elapsedTime3;		//벡터 마지막 스킬 저장 시간
	int storeLast;			//벡터 마지막 스킬 저장
	bool checkCombo;		//콤보 발생 여부

	bool moveback_R;
	bool moveback_L;

	///////////// 추가 부분 - 충돌 /////////////////
	RECT rcHit;
	RECT rcAttack;



public:

	HRESULT Init();
	void Motion2P();		//← → J L U O
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

	///////////// 추가 부분 - 충돌 /////////////////
	void Iori_Set_HitBox(int frameCount);
	void Iori_Set_AttackBox(int frameCount);

	inline RECT getRcHit() { return rcHit; }
	inline RECT getRcAttack() { return rcAttack; }

	Iori_2P();
	~Iori_2P();

};



