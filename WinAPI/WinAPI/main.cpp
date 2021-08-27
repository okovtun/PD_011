#include<Windows.h>
#include"resource.h"

struct Parent
{
	int a;
};

struct Child :public Parent
{

};

CONST CHAR* cb_content[] =
{
	"This","is", "my", "first","Combo","Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Child child;
	child.a = 2;
	//MessageBox(NULL, "Это мое первое окно, созданное в WinAPI", "Info MessageBox", MB_ICONWARNING | MB_YESNOCANCEL);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
		SendMessage(hwnd, WM_SETICON, 1, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(cb_content) / sizeof(cb_content[0]); i++)
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)cb_content[i]);
		SendMessage(hCombo, CB_SETCURSEL, 2, 0);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			//MessageBox(NULL, "Была нажата кнопка OK", "Info", MB_ICONINFORMATION | MB_OK); 
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CHAR sz_buffer[256]{};
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_msg[256]{};
			strcpy(sz_msg, "Вы выбрали пункт:");
			strcat(sz_msg, sz_buffer);
			MessageBox(hwnd, sz_msg, "Info", MB_ICONINFORMATION | MB_OK);
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
	break;
	case WM_CLOSE: EndDialog(hwnd, 0); break;
	}
	return FALSE;
}