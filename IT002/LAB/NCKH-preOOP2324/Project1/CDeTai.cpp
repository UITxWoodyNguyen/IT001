#include "CDeTai.h"

void CDeTai::Nhap() {
	cout << "Nhap ma de tai: ";
	cin >> MaDT;

	cout << "Nhap ten de tai: ";
	cin.ignore();
	getline(cin, TenDT);

	cout << "Nhap ngay dang ki de tai (DD/MM/YYYY): ";
	cin >> NgayDangKi;

	cout << "Nhap ngay nghiem thu (DD/MM/YYYY): ";
	cin >> NgayNghiemThu;

	cout << "Nhap thoi gian thuc hien: ";
	cin >> TimeThucHien;

	cout << "Nhap so bai bao Tap chi - Hoi nghi da dang ky: ";
	cin >> RegSoTapChi >> RegSoHoiNghi;
}

void CDeTai::Xuat() {
	cout << "Ma de tai: " << MaDT << endl;
	cout << "Ten de tai: " << TenDT << endl;
	cout << "Ngay dang ky de tai: " << NgayDangKi << endl;
	cout << "Ngay nghiem thu de tai: " << NgayNghiemThu << endl;
	cout << "Thoi gian thuc hien de tai: " << TimeThucHien << " ngay" << endl;
}

bool CDeTai::isNghiemThu(CDsBaiBao list) {
	int cntTapChi = list.DemSoTapChi();
	int cntHoiNghi = list.DemSoHoiNghi();

	return (cntTapChi >= RegSoTapChi && cntHoiNghi >= RegSoHoiNghi);
}