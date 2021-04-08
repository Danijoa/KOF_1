#pragma once
#include "GameNode.h"
#include "Opening.h"
#include "CharacterPick.h"
#include "MainGame.h"

class SceneManager :public GameNode
{
public:
	enum class Scene {Opening, Character, Battle, End};

private:
	//bool isInited;

	HANDLE hTimer;					
	Scene currentScene;				//현재_씬 기억하는 공간
	Opening g_opening;				//오프닝_씬
	CharacterPick g_characterpick;	//캐릭터픽_씬
	MainGame g_mainGame;			//배틀_씬

public:
	HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	void Release();			// 메모리 해제
	void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	SceneManager();
	~SceneManager();
};

