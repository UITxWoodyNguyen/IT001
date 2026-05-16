#include <iostream>
#include "CDeTai.h"
#include "CDsBaiBao.h"
using namespace std;

int main() {
	CDsBaiBao ds;
	cout << "NHAP DANH SACH BAI BAO!" << endl;
	ds.Nhap();

	string MaSoGiangVien;
	cout << "Nhap ma so giang vien can tinh: ";
	cin >> MaSoGiangVien;
	
	if (ds.getSoTietGV(MaSoGiangVien) != 0)
		cout << "So tiet cua giang vien co ma so " << MaSoGiangVien << " la: " << ds.getSoTietGV(MaSoGiangVien) << endl;
	else
		cout << "Khong tim thay giang vien co ma so " << MaSoGiangVien << endl;

	CDeTai dt;
	cout << "NHAP THONG TIN DE TAI" << endl;
	dt.Nhap();

	bool DuDieuKien = dt.isNghiemThu(ds);
	if (DuDieuKien) cout << "De tai du dieu kien de nghiem thu!" << endl;
	else cout << "De tai CHUA du dieu kien de nghiem thu!" << endl;

	return 0;
}