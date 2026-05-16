#include <iostream>
#include "CKhuVuc.h"
#include "CVung.h"
#include "CThoiDiem.h"
using namespace std;

int main() {
	/*Cau 1*/
	CVung vung;
	vung.Nhap();

	int kieuThoiTiet = vung.KieuThoiTiet(2);
	switch (kieuThoiTiet) {
		case 1:
			cout << "Thoi tiet Giong bao!" << endl;
			break;
		case 2:
			cout << "Thoi tiet Mua nhieu!" << endl;
			break;
		case 3:
			cout << "Thoi tiet nong kho!" << endl;
			break;
		case 4:
			cout << "Thoi tiet Gio am!" << endl;
			break;
		default:
			cout << "Thoi tiet on hoa!" << endl;
	}

	CKhuVuc kv;
	kv.Nhap();

	CVung* ThayDoiLonNhat = kv.maxDeltaT();
	cout << "Vung co muc thay doi nhiet do lon nhat: " << ThayDoiLonNhat->getTen() << endl;

	vector<CVung*> NongKho = kv.TimKiem(3, 2);
	cout << "Danh sach cac vung co khi hau nong kho: " << endl;
	for (auto zone : NongKho) cout << zone->getTen() << endl;

	return 0;
}