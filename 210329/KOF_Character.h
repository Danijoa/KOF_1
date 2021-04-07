#pragma once
#pragma once
#include "GameNode.h"
#include <vector>

class Image;

class KOF_Character : public GameNode
{
public:
	//상태
	enum class State { STAND, FRONT, BACK, WHAND, SHAND, WFOOT, SFOOT, COMBO, DOWN, WIN };
protected:
	//캐릭터 정보
	const char* name;		//이름
	FPOINT pos;				//위치
	int hp;					//체력

	//상태
	State curState;
	
	//위치가 왼쪽을 바라보는지, 오른쪽으로 바라보는지
	int curSidePosition;
	
	//모션에 따른
	int characterFrame;		//프레임 총 개수
	int frameCount;			//프레임 인덱스

	//모션 프레임 업데이트 시간 제어
	int elapsedTime;

	//공격력
	int attackValue;

	//키 입력 제어
	bool canInput;

	//스킬 저장
	vector<int> myV;

	//충돌 박스
	RECT rcHit;
	RECT rcAttack;

	//배경 좌우 변경
	bool moveback_R;
	bool moveback_L;

public:
	//
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	//위치
	inline int getPosX() { return pos.x; }
	inline void setSidePos(int sidePos) { this->curSidePosition = sidePos; }

	//배경
	inline int getBackMove_R() { return moveback_R; }
	inline void setBackMove_R(bool b) { this->moveback_R = b; }
	inline int getBackMove_L() { return moveback_L; }
	inline void setBackMove_L(bool b) { this->moveback_L = b; }

	//HP
	inline int getAttackValue() { return attackValue; }
	inline int getHP() { return hp; }
	inline void setHP(int enemyAttackValue) { this->hp -= enemyAttackValue; }

	//충돌
	inline RECT getRcHit() { return rcHit; }
	inline RECT getRcAttack() { return rcAttack; }

	//우승 상태
	inline void setWin() { this->curState = State::WIN; }

};

