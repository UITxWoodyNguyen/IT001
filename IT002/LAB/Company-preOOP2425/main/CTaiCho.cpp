#include "CTaiCho.h"

void CTaiCho::Nhap() {
	CHopDong::Nhap();
	cout << "Nhap chi phi sinh hoat: ";
	cin >> ChiPhiSinhHoat;
}

int CTaiCho::getLoai() {
	return 2;
}

float CTaiCho::getLoiNhuan() {
	return CTronGoi::getLoiNhuan() - ChiPhiSinhHoat * ThoiGianDuKien;
}