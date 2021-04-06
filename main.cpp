// main.cpp
#include "config.h"
//#include "MainGame.h"
#include "SceneManager.h"

// ��������
// �ν��Ͻ� : ��ü �޸𸮻� �����ϴ� ��ü
HINSTANCE g_hInstance;		// ���α׷� �ν��Ͻ� �ڵ�
HWND g_hWnd;				// ������ �ڵ�
LPSTR g_lpszClass = (LPSTR)TEXT("�������� ����");
//MainGame g_mainGame;
SceneManager g_sceneManager;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;

	// �����츦 �����ϱ� ���� �⺻����
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	wndClass.cbClsExtra = 2068;
	wndClass.cbWndExtra = 2068;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIconSm = LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(IDI_SHIELD));

	// ������ Ŭ���� ���
	RegisterClassEx(&wndClass);

	// ������ ����
	g_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		10, 50, WINSIZE_X, WINSIZE_Y,
		NULL, NULL, g_hInstance, NULL);

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	//if (FAILED(g_mainGame.Init()))
	//{
	//	MessageBox(g_hWnd, "���� ���� �ʱ�ȭ ����!!", "���", MB_OK);
	//}
	if (FAILED(g_sceneManager.Init()))
	{
		MessageBox(g_hWnd, "���� ���� �ʱ�ȭ ����!!", "���", MB_OK);
	}

	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//g_mainGame.Release();
	g_sceneManager.Release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
	return g_sceneManager.MainProc(hWnd, iMessage, wParam, lParam);
}