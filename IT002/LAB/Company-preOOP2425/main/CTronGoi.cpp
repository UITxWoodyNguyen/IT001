#include "CTronGoi.h"

void CTronGoi::Nhap() {
	CHopDong::Nhap();

	cout << "Nhap ngay hoan thanh thuc te (DD/MM/YYYY): ";
	cin >> NgayThucTe;

	cout << "Nhap gia tri hop dong: ";
	cin >> GiaTriHopDong;
}

int CTronGoi::getLoai() {
	return 0;
}

float CTronGoi::getLoiNhuan() {
	float LoiNhuan = GiaTriHopDong - ((TongLuongNgay + ChiPhiChung) * ThoiGianDuKien) - ChiPhiBanDau;
	int diff = NgayThucTe - NgayHoanThanh;
	diff -= ThoiGianDuKien;

	if (diff >= 15 && diff < 90) LoiNhuan -= (GiaTriHopDong * 0.1f);
	else if (diff >= 90) LoiNhuan -= (GiaTriHopDong * 0.3f);

	return LoiNhuan;
}