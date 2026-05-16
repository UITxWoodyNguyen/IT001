#include "CNghienCuu.h"

void CNghienCuu::Nhap() {
	CHopDong::Nhap();
	cout << "Nhap chi phi nhan su: ";
	cin >> ChiPhiNhanSu;
}

int CNghienCuu::getLoai() {
	return 1;
}

float CNghienCuu::getLoiNhuan() {
	return (ChiPhiNhanSu - TongLuongNgay - ChiPhiChung) * ThoiGianDuKien - ChiPhiBanDau;
}