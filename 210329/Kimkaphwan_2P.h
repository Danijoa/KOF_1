#pragma once
#include "KOF_Character.h"
#include <vector>

class Image;
class KimKaphwan_2P : public KOF_Character
{
public:
	enum class State { STAND, FRONT, BACK, WHAND, SHAND, WFOOT, SFOOT, COMBO, DOWN };

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

	bool canInput;

	vector<int> myV;		//공격 스킬 저장		
	int* comboStore;		//콤보 스킬 저장
	int elapsedTime2;		//콤보 입력 시간
	int elapsedTime3;		//벡터 마지막 스킬 저장 시간
	int storeLast;			//벡터 마지막 스킬 저장
	bool checkCombo;		//콤보 발생 여부

	bool moveback_R;
	bool moveback_L;

public:
	HRESULT Init();
	void Motion2P();		//← → J L U O
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
};

