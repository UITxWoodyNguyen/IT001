#include "CVung.h"

void CVung::Nhap() {
	cout << "Nhap ten vung: ";
	cin >> Ten;

	cout << "Nhap do cao: ";
	cin >> DoCao;

	cout << "Nhap do che phu: ";
	cin >> DoChePhu;

	cout << "Nhap thong tin thoi diem t1: " << endl;
	t1 = new CThoiDiem();
	t1->Nhap();

	cout << "Nhap thong tin thoi diem t2: " << endl;
	t2 = new CThoiDiem();
	t2->Nhap();
}

void CVung::Xuat() {
	cout << "Ten vung: " << Ten << endl;
	cout << "Do cao: " << DoCao << endl;
	cout << "Do che phu: " << DoChePhu << endl;

	cout << "Thong tin thoi tiet tai thoi diem T1: " << endl;
	t1->Xuat();

	cout << "Thong tin thoi tiet tai thoi diem T2: " << endl;
	t2->Xuat();
}

string CVung::getTen() {
	return Ten;
}

float CVung::TinhDeltaT() {
	float T1 = t1->getNhietDo();
	float T2 = t2->getNhietDo();

	float DeltaT = ((T2 - T1) * (1 - DoCao / 10000) * (1 - DoChePhu));

	if (DeltaT > 0) return DeltaT;
	else return -DeltaT;
}

int CVung::KieuThoiTiet(int TD) {
	if (TD == 1) return t1->KieuThoiTiet();
	else return t2->KieuThoiTiet();
}