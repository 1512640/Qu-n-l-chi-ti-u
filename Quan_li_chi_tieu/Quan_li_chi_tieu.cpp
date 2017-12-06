// Quan_li_chi_tieu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Quan_li_chi_tieu.h"

#define MAX_LOADSTRING 100
#define IDC_Them 111
#define ID_list 222
#define IDC_Thoat 333
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_QUAN_LI_CHI_TIEU, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUAN_LI_CHI_TIEU));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

void themTien(wchar_t *s1, wchar_t *s3 )
{
	int so = _wtoi(s3);
	if (wcscmp(s1, L"Khác\r") == 0)			tien[0] += so;
	if (wcscmp(s1, L"Ăn uống") == 0)		tien[1] += so;
	if (wcscmp(s1, L"Di chuyển\r") == 0)	tien[2] += so;
	if (wcscmp(s1, L"Nhà cửa\r") == 0)		tien[3] += so;
	if (wcscmp(s1, L"Xe cộ\r") == 0)		tien[4] += so;
	if (wcscmp(s1, L"Nhu yếu phẩm\r") == 0)	tien[5] += so;
	if (wcscmp(s1, L"Dịch vụ\r") == 0)		tien[6] += so;
}
float tinh_ti_le(int so_tien)
{
	int sum = 0;
	for (int i = 0; i < 7; i++)
	{
		sum += tien[i];
	}
	return  so_tien*1.0 / sum;
}
int tong_tien()
{
	int sum = 0;
	for (int i = 0; i < 7; i++)
	{
		sum += tien[i];
	}
	return sum;
}
void VeBieuDo(Graphics *grap,int tien[])
{
	int kichThuoc = 700;
	int a = kichThuoc * tinh_ti_le(tien[1]);
	grap->FillRectangle(&SolidBrush(Color::Blue), 50, 400, a, 100);
	int b = kichThuoc * tinh_ti_le(tien[2]);
	grap->FillRectangle(&SolidBrush(Color::Brown), 50 + a, 400, b, 100);

	int c = kichThuoc *tinh_ti_le(tien[3]);
	grap->FillRectangle(&SolidBrush(Color::Yellow), 50 + a + b, 400, c, 100);

	int d = kichThuoc *tinh_ti_le(tien[4]);
	grap->FillRectangle(&SolidBrush(Color::LightGray), 50 + a + b + c, 400, d, 100);

	int e = kichThuoc *tinh_ti_le(tien[5]);
	grap->FillRectangle(&SolidBrush(Color::Red), 50 + a + b + c + d, 400, e, 100);

	int f = kichThuoc *tinh_ti_le(tien[6]);
	grap->FillRectangle(&SolidBrush(Color::DarkCyan), 50 + a + b + c + d + e, 400, f, 100);


	int g = kichThuoc *tinh_ti_le(tien[0]);
	grap->FillRectangle(&SolidBrush(Color::DarkMagenta), 50 + a + b + c + d + e + f, 400, g, 100);

}
void doc_file(WCHAR* chuoi, HWND hwnd)
{
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	wifstream readfile;
	readfile.open(chuoi, ios::in | ios::binary); // Mo file 
	readfile.imbue(loc);
	wchar_t *s;
	s = new wchar_t[100];
	if (readfile.is_open() == true)
	{
		while (!readfile.eof())
		{
			readfile.getline(s, 100);
			ComboBox_AddString(hwnd, s);
		}
	}
	readfile.close();// Dong file 
}
void viet_file(WCHAR* chuoi, HWND edit)
{
	int dodai = GetWindowTextLengthW(edit);
	WCHAR *str = new WCHAR[dodai + 1];
	GetWindowText(edit, str, dodai + 1);
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	wfstream writeFile;
	writeFile.open(chuoi, ios::out | ios::binary | ios::app); // Mo file
	writeFile.imbue(loc);
	if (writeFile.is_open())
	{
		writeFile << str;
		writeFile << L"\n";
	}
	writeFile.close();
	delete[]str;
}

void Add_List(HWND list, int cap, WCHAR*s1, WCHAR*s2, WCHAR*s3)
{
	LVITEM cot = { 0 };
	cot.cchTextMax = 1000;
	cot.iItem = cap;
	cot.mask = LVIF_TEXT | LVCF_SUBITEM| LVIF_PARAM;
	ListView_InsertItem(list, &cot);
	ListView_SetItemText(list, cap, 0, s1);
	ListView_SetItemText(list, cap, 1, s2);
	ListView_SetItemText(list, cap, 2, s3);
}
void Danh_sach_CT(WCHAR* chuoi)
{
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	wifstream readfile;
	readfile.open(chuoi, ios::in | ios::binary); // Mo file 
	readfile.imbue(loc);
	wchar_t *s[4];
	for (int i = 0; i < 4; i++)
	{
		s[i] = new wchar_t[1000];
		s[i][0] = 0; // gán rỗng hết các phần tử chuỗi trong mảng
	}

	int i = 1;
	if (readfile.is_open() == true)
	{
		while (!readfile.eof())
		{
			readfile.getline(s[i], 1000);
			if (s[i][0] != '\r' && wcscmp(s[1], L"") != 0) // kiem tra chuoi rong
			{
				danhSachchiTieu.push_back(s[i]);
				if (i == 3)
				{
					themTien(s[1], s[3]);
				}
				i++;
				soLuong++;
			}
			if (i > 3)
			{
				Add_List(danh_sach, cap, danhSachchiTieu[soLuong-3], danhSachchiTieu[soLuong -2], danhSachchiTieu[soLuong-1]); //them vao danh sach
				i = 1;
				cap++;
			}
		}
	}
	readfile.close();// Dong file 
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUAN_LI_CHI_TIEU));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_QUAN_LI_CHI_TIEU);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   //HWND hWnd = CreateWindowW(szWindowClass, L"Quản lí chi tiêu", WS_OVERLAPPEDWINDOW,
     // CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	  hWnd = CreateWindowW(szWindowClass, L"Quản lí chi tiêu", WS_OVERLAPPEDWINDOW,
		 150,80,1000,600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

	

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
    {
		
	case WM_CREATE:
	{	
		InitCommonControls();
		RECT rect;
		GetClientRect(hWnd, &rect);
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		GetClientRect(hWnd, &rect);

		hfont = CreateFont(20, 0, 0, 0, FW_DONTCARE, 1, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));

		loai_chi_tieu = CreateWindow(WC_COMBOBOX, L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL
		| CBS_DROPDOWN | CBN_SELCHANGE, 50, 50, 200, 500, hWnd, 0, hInst, 0);
		hwnd = CreateWindowEx(0, WC_STATIC, L"Loại chi tiêu", WS_CHILD | WS_VISIBLE, 50, 30, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		HFONT hffont = CreateFont(20, 0, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
		noi_dung = CreateWindow(WC_EDIT, L"", WS_HSCROLL|WS_BORDER  | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_MULTILINE , 300, 50,250, 80, hWnd, 0, 0, 0, 0);
		hwnd = CreateWindowEx(0, WC_STATIC, L"Nội dung", WS_CHILD | WS_VISIBLE, 300, 30, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);
		SendMessage(noi_dung, WM_SETFONT, (WPARAM)hffont, TRUE);


		so_tien = CreateWindow(WC_EDIT, L"",  WS_HSCROLL | WS_BORDER  | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_MULTILINE|ES_NUMBER, 600, 50, 150,50, hWnd, 0, 0, 0, 0);
		hwnd = CreateWindowEx(0, WC_STATIC, L"VND", WS_CHILD | WS_VISIBLE, 760, 60, 50, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hffont, TRUE);
		SendMessage(so_tien, WM_SETFONT, (WPARAM)hffont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Số tiền chi", WS_CHILD | WS_VISIBLE, 600, 30, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);


		them = CreateWindowEx(0, WC_BUTTON, L"Thêm", BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 850,50, 80, 80, hWnd, (HMENU)IDC_Them, hInst, NULL);
		//thoat = CreateWindowEx(0, WC_BUTTON, TEXT("Thoat"), BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 850, 150, 80, 80, hWnd, (HMENU)IDC_Them, hInst, NULL);
		danh_sach = CreateWindow(WC_LISTVIEW, 0, LVS_REPORT | WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_ICON,
								50, 150, 700, 200, hWnd, (HMENU)ID_list, 0, 0);
		hwnd = CreateWindowEx(0, WC_STATIC, L"Danh sách chi tiêu", WS_CHILD | WS_VISIBLE, 50, 130, 150, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		//Viet ghi chú
		hwnd = CreateWindowEx(0, WC_STATIC, L"Biểu đồ mô tả", WS_CHILD | WS_VISIBLE, 50, 380, 150, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Chú thích", WS_CHILD | WS_VISIBLE, 780, 300, 80, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Ăn uống", WS_CHILD | WS_VISIBLE, 830, 333, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Di chuyển", WS_CHILD | WS_VISIBLE, 830, 363, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Nhà cửa", WS_CHILD | WS_VISIBLE, 830, 393, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Xe cộ", WS_CHILD | WS_VISIBLE, 830, 423, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Nhu yếu phẩm", WS_CHILD | WS_VISIBLE, 830, 453, 130, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Dịch vụ", WS_CHILD | WS_VISIBLE, 830, 483, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		hwnd = CreateWindowEx(0, WC_STATIC, L"Khác", WS_CHILD | WS_VISIBLE, 830, 513, 100, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);

		//tao khung danh sach
		LVCOLUMN cot;
		cot.cchTextMax = 100;
		cot.pszText = L"Loại chi tiêu";
		cot.cx = 200;
		cot.iSubItem = 0;
		cot.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		cot.fmt = LVCFMT_LEFT;
		ListView_InsertColumn(danh_sach, 0, &cot);

		cot.pszText = L"Nội dung";
		cot.cx = 300;
		ListView_InsertColumn(danh_sach, 1, &cot);

		cot.pszText = L"Số tiền";
		cot.cx =200;
		ListView_InsertColumn(danh_sach, 2, &cot);


		doc_file(L"loai_chi_dau.txt",loai_chi_tieu);
		Danh_sach_CT(L"xuat.txt");

		WCHAR tongTien[100] = L"Tổng tiền là: ";
		WCHAR s[100];
		_itow(tong_tien(), s, 10);
		wcsncat(s, L" VND", 20);
		wcscat(tongTien, s);
		hwnd = CreateWindowEx(0, WC_STATIC, tongTien, WS_CHILD | WS_VISIBLE, 540, 360, 200, 20, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)hffont, TRUE);


		break;
	}
    case WM_COMMAND:
        {
			hfont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
			SendMessage(loai_chi_tieu, WM_SETFONT, (WPARAM)hfont, TRUE);

			int wmId = LOWORD(wParam);
            switch (wmId)
            {		
			case IDC_Them:
			{	//Lấy chuoi từ combobox
				int dodai = ComboBox_GetTextLength(loai_chi_tieu); 
				WCHAR *str = new WCHAR[dodai + 1];
				ComboBox_GetText(loai_chi_tieu, str, dodai + 1);
				danhSachchiTieu.push_back(str);
				soLuong++;
				//Ghi dữ liệu vào file để lưu trữ
				viet_file(L"xuat.txt", loai_chi_tieu);

				dodai = GetWindowTextLengthW(noi_dung);
				WCHAR *str1 = new WCHAR[dodai + 1];
				GetWindowText(noi_dung, str1, dodai + 1);
				danhSachchiTieu.push_back(str1);
				soLuong++;
				viet_file(L"xuat.txt", noi_dung);

				dodai = GetWindowTextLengthW(so_tien);
				WCHAR *str2 = new WCHAR[dodai + 1];
				GetWindowText(so_tien, str2, dodai + 1);
				danhSachchiTieu.push_back(str2);
				soLuong++;
				viet_file(L"xuat.txt", so_tien);
				Add_List(danh_sach, cap, danhSachchiTieu[soLuong - 3], danhSachchiTieu[soLuong - 2], danhSachchiTieu[soLuong - 1]); //them vao danh sach
				themTien(danhSachchiTieu[soLuong - 3], danhSachchiTieu[soLuong - 1]);
				cap++;
				WCHAR tongTien[100] = L"Tổng tiền là: ";
				WCHAR s[100];
				_itow(tong_tien(), s, 10);
				wcsncat(s, L" VND", 20);
				wcscat(tongTien, s);
				hwnd = CreateWindowEx(0, WC_STATIC, tongTien, WS_CHILD | WS_VISIBLE, 540, 360, 200, 20, hWnd, NULL, hInst, NULL);
				SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);
				veLai = true;
				InvalidateRect(hWnd, 0, 0); //Goi ham WM_PAINT
				break;
			}
			
			case IDC_Thoat:
			{
				DestroyWindow(hWnd);
				break;
			}
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_PAINT:
	{

		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);

		grap = new Graphics(hdc);
		Pen* pen = new Pen(Color(255, 0, 0, 0), 2);
		SelectObject(hdc, pen);
		SolidBrush  mau(Color(255, 0, 255, 255));

		//Ve bieu do
		if (veLai == true)
		{
			VeBieuDo(grap, tien);
			veLai = false;
		}
		//Vẽ chú thích
		grap->FillRectangle(&SolidBrush(Color::Blue), 780, 330, 40, 20); // 1
		grap->FillRectangle(&SolidBrush(Color::Brown), 780, 360, 40, 20); //2
		grap->FillRectangle(&SolidBrush(Color::Yellow), 780, 390, 40, 20); //3
		grap->FillRectangle(&SolidBrush(Color::LightGray), 780, 420, 40, 20); //4
		grap->FillRectangle(&SolidBrush(Color::Red), 780, 450, 40, 20);//5
		grap->FillRectangle(&SolidBrush(Color::DarkCyan), 780, 480, 40, 20);//6
		grap->FillRectangle(&SolidBrush(Color::DarkMagenta), 780, 510, 40, 20); //0
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CTLCOLORSTATIC:
	{
		SetTextColor((HDC)wParam, RGB(0, 0, 255));
		SetBkMode((HDC)wParam, TRANSPARENT); // Màu nền trong suốt
		return (LRESULT)CreateSolidBrush(RGB(255,255,255));
		break;
	}
	case WM_CTLCOLORBTN:
	{
		RECT crect;
		HDC hdc = (HDC)wParam;
		HWND button_handle = (HWND)lParam;
		GetClientRect(them, &crect);
		SetBkColor(hdc, RGB(0, 255, 0));
		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, L"THÊM", -1, &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		return (LRESULT)CreateSolidBrush(RGB(0, 255, 0));
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
