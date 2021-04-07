#pragma once
#include "GameNode.h"

class Image;
class Kyo_1P;
class Kyo_2P;
class Iori_1P;
class Iori_2P;
class KimKaphwan_1P;
class KimKaphwan_2P;

class MainGame : public GameNode
{
public:
	enum class Character {Kyo, Iori, Kim};

private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;

	FPOINT backPos;

	//배경 변수
	Image* backBuffer;
	Image* backGround;
	int character_1P_backR, character_1P_backL;			
	int character_2P_backR, character_2P_backL;
	int backgroundCount;
	int backgroundFrame;
	
	//캐릭터 변수
	Kyo_1P* kyo1P;
	Kyo_2P* kyo2P;
	Iori_1P* iori1P;
	Iori_2P* iori2P;
	KimKaphwan_1P* kim1P;
	KimKaphwan_2P* kim2P;
	int character_1P, character_2P;										//0: 쿄 1: 이오리 3: 김갑환
	int character_1P_posX, character_2P_posX;							//1P 2P (x)위치

	//hp 조절 변수
	Image* hpBar;
	Image* hp1PBar;
	Image* hp2PBar;
	int sizeX1P, sizeX2P;
	int barPosX;														//1P일 때 만
	int character_1P_HP, character_2P_HP;								//1P 2P HP
	int character_1P_AttackValue, character_2P_AttackValue;				//1P 2P AttackValue
	int elapsedTime;

	//충돌관련 변수
	RECT RectHit_1P, RectHit_2P;
	RECT RectAttack_1P, RectAttack_2P;
	RECT rcTemp1, rcTemp2;												//교차 영역을 저장할 RECT
	const char* whoHitted;
	const char* whoAttack;

	//게임 종료 변수
	bool checkGameOver;
	Image* gameOver;

	//타이버 변수
	Image* timer;
	int timerCount;
	int timeFrame;

public:
	HRESULT Init();
	void Manager1P();
	void Manager2P();
	void Update();
	void Release();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	inline void setCharater(int c_1P, int c_2P)	//선택된 1p 2p 캐릭터 받아오기
	{ 
		this->character_1P = c_1P; 
		this->character_2P = c_2P;
	};

	MainGame();
	~MainGame();
};