#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox
	(
		NULL,
		"Hello WinAPI!",
		"MessageBox",
		MB_YESNOCANCEL 
		| MB_ICONERROR 
		| MB_HELP 
		| MB_DEFBUTTON3 
		| MB_SYSTEMMODAL
		| MB_RIGHT
	);*/

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC) DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: // выполн€етс€ один раз при запуске окна.
		break;
	case WM_COMMAND: //обрабатывает команды с клавиатуры и мыши.
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(NULL, "Ѕыла нажата кнопка 'OK'", "info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:   // выполн€етс€ при нажатиии "’"
		EndDialog(hwnd, 0);
	}
	return FALSE;
}