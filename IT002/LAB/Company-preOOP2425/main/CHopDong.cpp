#include "CHopDong.h"

void CHopDong::Nhap() {
	cout << "Nhap ten doi tac: ";
	cin >> DoiTac;

	cout << "Nhap ten du an: ";
	cin >> projectName;

	cout << "Nhap ngay hoan thanh du kien (DD/MM/YY): ";
	cin >> NgayHoanThanh;

	cout << "Nhap linh vuc cua du an: ";
	cin >> LinhVuc;

	cout << "Nhap yeu cau ki thuat: ";
	cin >> YeuCauKT;

	cout << "Nhap chi phi ho tro chung: ";
	cin >> ChiPhiChung;

	cout << "Nhap chi phi ban dau: ";
	cin >> ChiPhiBanDau;

	cout << "Nhap tong luong cua nhan vien trong ngay: ";
	cin >> TongLuongNgay;

	cout << "Nhap thoi gian thi cong du kien (Ngay): ";
	cin >> ThoiGianDuKien;
}

float CHopDong::getLoiNhuan() {
	return 0;
}

int CHopDong::getLoai() {
	return -1;
}