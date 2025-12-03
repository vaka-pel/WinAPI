#include<Windows.h>
#include"resource.h"
#include<cstdio>

#define IDC_BUTTON 1000

CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	//инициализируем размеры и стиль:
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	//инициализируем внешний вид окон:
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_BITCOIN));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_PALM));
	//wClass.hIcon = (HICON)LoadImage(hInstance, "bitcoin.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(hInstance, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hCursor = (HCURSOR)LoadImage
		(
			hInstance, 
			"starcraft-original\\Working In Background.ani",
			IMAGE_CURSOR,
			LR_DEFAULTSIZE, LR_DEFAULTSIZE,
			LR_LOADFROMFILE
		);
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	// инициализация системных переменных:
	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	// 2) Создание окна
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_heigth = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * 3 / 4;
	int window_heigth = screen_heigth * 3 / 4;
	int x_position = screen_width / 8;
	int y_position = screen_heigth / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,    //Имя класса окна
		g_sz_WINDOW_CLASS,     //Заголовок окна
		WS_OVERLAPPEDWINDOW,           // стиль окна, стили зависят от класса окна
		CW_USEDEFAULT, CW_USEDEFAULT,    //position
		640, 480,    // размер окна
		NULL,    //для главного окна это ResourseID главного меню
		NULL,    //
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windows creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); //задает режим отображения окна - развернуто на весь экран, Свернуто в окно, Свернуто на панель задач 
	UpdateWindow(hwnd); // обновляет рабочую область окна отправляя сообщение WM_PAIN, 
	                   // если клиентская область окна не пустая
					   // 
	// 3) Запуск цикла сообщений

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg); // преобразует сообщения виртуальных клавиш в символьные сообщения
		DispatchMessage(&msg);  // отправляет сообщение в процедуру окна
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{

		HWND hButton = CreateWindowEx
		(
			NULL,     //exStyle
			"Button",  //Class
			"Кнопка",  //Title
			WS_CHILD | WS_VISIBLE,  // Style
			10, 10,               // Position
			150, 80,           // Size
			hwnd,          // Parent
			(HMENU)1000,   // для главного окна - это ResourseID главного меню
			               // Для дочернего окна (элемента управления окна) - это дочернего ResourseID элемента
			GetModuleHandle(NULL), // hInstanse
			NULL

			);
	}
		break;
	case WM_MOVE:
	case WM_SIZE:
	{
		RECT window_rect = {};
		GetWindowRect(hwnd, &window_rect);
		CONST INT SIZE = 256;
		CHAR sz_title[SIZE] = {};
		wsprintf
		(
			sz_title,
			"%s, Position: %i%i, Size: %i%i",
			g_sz_WINDOW_CLASS,
			window_rect.left, window_rect.top,
			window_rect.right-window_rect.left,
			window_rect.bottom-window_rect.top
			);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
		MessageBox(hwnd, "Cursor check", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		}
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}