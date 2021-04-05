#include "SceneManager.h"
#include "MainGame.h"

HRESULT SceneManager::Init()
{
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	
	currentScene = Scene::Opening;	//오프닝을 첫 화면으로 초기화
	
	if (FAILED(g_opening.Init()))
	{
		MessageBox(g_hWnd, "오프닝 초기화 실패!!", "경고", MB_OK);
	}
	if (FAILED(g_characterpick.Init()))
	{
		MessageBox(g_hWnd, "케릭터창 초기화 실패!!", "경고", MB_OK);
	}
	if (FAILED(g_mainGame.Init()))
	{
		MessageBox(g_hWnd, "메인 게임(배틀) 초기화 실패!!", "경고", MB_OK);
	}
	
	return S_OK;
}

void SceneManager::Release()
{
	g_opening.Release();
	g_characterpick.Release();
	g_mainGame.Release();

	KillTimer(g_hWnd, 0);
}

void SceneManager::Update()
{
	if (g_opening.getNext())
		currentScene = Scene::Character;
	if (g_characterpick.getNext())
	{
		g_mainGame.setCharater(g_characterpick.get1P(), g_characterpick.get2P());	//1P 2P 누구인지 넘겨주기
		currentScene = Scene::Battle;
	}
}

void SceneManager::Render(HDC hdc)
{
}

LRESULT SceneManager::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			this->Update();	//씬 관리 업데이트
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	switch (currentScene)	//콜백 함수에 넘겨줄 결과 값
	{
	case Scene::Opening:
		return g_opening.MainProc(hWnd, iMessage, wParam, lParam);
		break;
	case Scene::Character:
		return g_characterpick.MainProc(hWnd, iMessage, wParam, lParam);
		break;
	case Scene::Battle:
		return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
		break;
	}
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
