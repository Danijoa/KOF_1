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
	Scene currentScene;				//����_�� ����ϴ� ����
	Opening g_opening;				//������_��
	CharacterPick g_characterpick;	//ĳ������_��
	MainGame g_mainGame;			//��Ʋ_��

public:
	HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();			// �޸� ����
	void Update();			// ������ ������ ���� ���� ���� (������ ����)
	void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	SceneManager();
	~SceneManager();
};

