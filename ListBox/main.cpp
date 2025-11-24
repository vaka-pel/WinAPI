#include<Windows.h>
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hinstance - экзэмпляр исполняемого файла программы, загруженного в память (*.exe)
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_DBLCLK)
				//GetModuleHandle(NULL) - Возвращает "hinstance" нашей программе
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, (DLGPROC) DlgProcEdit, 0);
			break;
		case IDC_BUTTON_ADD:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, (DLGPROC) DlgProcAdd, 0);
		}
    	break;
		case IDC_BUTTON_DELETE:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
		}
		break;
		case IDOK:
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SetFocus(GetDlgItem(hwnd, IDC_EDIT));
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hParent = GetParent(hwnd);
			HWND hList = GetDlgItem(hParent, IDC_LIST1);
			if (SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			else
			{
				MessageBox(hwnd, "Такой элемент уже существует", "Warning", MB_OK | MB_ICONWARNING);
				break;
			}
		}
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CONST INT SIZE = 256;
	CHAR sz_buffer[SIZE] = {};
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"Изменить");
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		HWND hParent = GetParent(hwnd);
		HWND hList = GetDlgItem(hParent, IDC_LIST1);
		INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
		SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hList, WM_SETTEXT, i, (LPARAM)sz_buffer);
		SetFocus(hEdit);
		SendMessage(hEdit, EM_SETSEL, 256, -1);
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

		    HWND hParent = GetParent(hwnd);
		    HWND hList = GetDlgItem(hParent, IDC_LIST1);
		    INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR)
			{
		        SendMessage(hList, LB_DELETESTRING, i, NULL);
				SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)sz_buffer);

			}
			
		}
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}