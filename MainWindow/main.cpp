#include<Windows.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";

INT WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	//инициализируем размеры и стиль:
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	//инициализируем внешний вид окон:
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	return 0;
}