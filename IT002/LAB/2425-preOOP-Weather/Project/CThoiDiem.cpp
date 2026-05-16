#include "CThoiDiem.h"

void CThoiDiem::Nhap() {
	cout << "Nhiet do: ";
	cin >> NhietDo;

	cout << "Do am: ";
	cin >> DoAm;

	cout << "Toc do gio: ";
	cin >> TocDoGio;

	cout << "Buc xa mat troi: ";
	cin >> BucXaMT;

	cout << "Luong mua: ";
	cin >> LuongMua;
}

void CThoiDiem::Xuat() {
	cout << "Nhiet do: " << NhietDo << endl;
	cout << "Do am: " << DoAm << endl;
	cout << "Toc do gio: " << TocDoGio << endl;
	cout << "Buc xa mat troi: " << BucXaMT << endl;
	cout << "Luong mua: " << LuongMua << endl;
}

float CThoiDiem::getNhietDo() {
	return NhietDo;
}

int CThoiDiem::KieuThoiTiet() {
	if (LuongMua >= 15 && TocDoGio >= 12 && NhietDo < 25) return 1;		// Giong bao
	if (LuongMua > 5 && DoAm >= 70) return 2;		// Mua nhieu
	if (NhietDo >= 30 && DoAm <= 50 && BucXaMT > 800) return 3;		// Nong kho
	if (DoAm >= 80 && TocDoGio >= 8) return 4;		// Gio am

	return 0;	// on hoa
}