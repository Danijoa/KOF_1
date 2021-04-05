#include "SceneManager.h"
#include "MainGame.h"

HRESULT SceneManager::Init()
{
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	
	currentScene = Scene::Opening;	//�������� ù ȭ������ �ʱ�ȭ
	
	if (FAILED(g_opening.Init()))
	{
		MessageBox(g_hWnd, "������ �ʱ�ȭ ����!!", "���", MB_OK);
	}
	if (FAILED(g_characterpick.Init()))
	{
		MessageBox(g_hWnd, "�ɸ���â �ʱ�ȭ ����!!", "���", MB_OK);
	}
	if (FAILED(g_mainGame.Init()))
	{
		MessageBox(g_hWnd, "���� ����(��Ʋ) �ʱ�ȭ ����!!", "���", MB_OK);
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
		g_mainGame.setCharater(g_characterpick.get1P(), g_characterpick.get2P());	//1P 2P �������� �Ѱ��ֱ�
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
			this->Update();	//�� ���� ������Ʈ
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	switch (currentScene)	//�ݹ� �Լ��� �Ѱ��� ��� ��
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
