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

	Image* backBuffer;
	Image* backGround;

	int character_1P;	//0: Äì 1: ÀÌ¿À¸® 3: ±è°©È¯
	int character_2P;
	int character_1P_posX;
	int character_2P_posX;
	int character_1P_backR;
	int character_1P_backL;
	int character_2P_backR;
	int character_2P_backL;

	Kyo_1P* kyo1P;
	Kyo_2P* kyo2P;

	Iori_1P* iori1P;
	Iori_2P* iori2P;

	KimKaphwan_1P* kim1P;
	KimKaphwan_2P* kim2P;

public:
	HRESULT Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	inline void setCharater(int c_1P, int c_2P)	//¼±ÅÃµÈ 1p 2p Ä³¸¯ ¹Þ¾Æ¿À±â
	{ 
		this->character_1P = c_1P; 
		this->character_2P = c_2P;
	};

	MainGame();
	~MainGame();
};