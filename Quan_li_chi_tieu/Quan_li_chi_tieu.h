#pragma once

#include "resource.h"
#include <vector>
HWND hwnd;
HWND loai_chi_tieu;
HWND noi_dung;
HWND so_tien;
HWND them;
HWND hWnd;
//HWND thoat;
HWND danh_sach;
int tien[7] = { 0 };
int soLuong = 0;
int cap = 0;
bool veLai = true;
Graphics *grap;
vector <wchar_t*> danhSachchiTieu;
HFONT hfont;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;