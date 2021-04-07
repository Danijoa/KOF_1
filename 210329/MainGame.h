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

	//��� ����
	Image* backBuffer;
	Image* backGround;
	int character_1P_backR, character_1P_backL;			
	int character_2P_backR, character_2P_backL;
	int backgroundCount;
	int backgroundFrame;
	
	//ĳ���� ����
	Kyo_1P* kyo1P;
	Kyo_2P* kyo2P;
	Iori_1P* iori1P;
	Iori_2P* iori2P;
	KimKaphwan_1P* kim1P;
	KimKaphwan_2P* kim2P;
	int character_1P, character_2P;										//0: �� 1: �̿��� 3: �谩ȯ
	int character_1P_posX, character_2P_posX;							//1P 2P (x)��ġ

	//hp ���� ����
	Image* hpBar;
	Image* hp1PBar;
	Image* hp2PBar;
	int sizeX1P, sizeX2P;
	int barPosX;														//1P�� �� ��
	int character_1P_HP, character_2P_HP;								//1P 2P HP
	int character_1P_AttackValue, character_2P_AttackValue;				//1P 2P AttackValue
	int elapsedTime;

	//�浹���� ����
	RECT RectHit_1P, RectHit_2P;
	RECT RectAttack_1P, RectAttack_2P;
	RECT rcTemp1, rcTemp2;												//���� ������ ������ RECT
	const char* whoHitted;
	const char* whoAttack;

	//���� ���� ����
	bool checkGameOver;
	Image* gameOver;

	//Ÿ�̹� ����
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

	inline void setCharater(int c_1P, int c_2P)	//���õ� 1p 2p ĳ���� �޾ƿ���
	{ 
		this->character_1P = c_1P; 
		this->character_2P = c_2P;
	};

	MainGame();
	~MainGame();
};