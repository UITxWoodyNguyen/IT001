#include "CGiangVien.h"

void CGiangVien::Nhap() {
	cout << "Nhap ma giang vien: ";
	cin >> MaGV;

	cout << "Nhap ten giang vien: ";
	cin.ignore();
	getline(cin, TenGV);

	cout << "Nhap chuyen nganh cua giang vien: ";
	cin >> ChuyenNganh;

	cout << "Nhap so dien thoai: ";
	cin >> SDT;
}

void CGiangVien::Xuat() {
	cout << "Ma giang vien: " << MaGV << endl;
	cout << "Ten giang vien: " << TenGV << endl;
	cout << "Chuyen nganh: " << ChuyenNganh << endl;
	cout << "So dien thoai: " << SDT << endl;

	cout << endl;
}

string CGiangVien::getMaSo() {
	return MaGV;
}