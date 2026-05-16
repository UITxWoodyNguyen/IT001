#include "CKhuVuc.h"

void CKhuVuc::Nhap() {
	cout << "Nhap so vung trong khu vuc: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "Nhap thong tin vung thu " << i + 1 << " : " << endl;
		CVung* temp = new CVung();
		temp->Nhap();

		data.push_back(temp);
	}
}

void CKhuVuc::Xuat() {
	cout << "Danh sach cac vung thuoc khu vuc: " << endl;
	for (int i = 0; i < n; i++) {
		cout << "Thong tin vung thu " << i + 1 << " : " << endl;
		data[i]->Xuat();
	}
}

vector<CVung*> CKhuVuc::TimKiem(int Loai, int thoiDiem) {
	vector<CVung*> kq;
	for (int i = 0; i < n; i++) {
		if (data[i]->KieuThoiTiet(2) == Loai)
			kq.push_back(data[i]);
	}

	return kq;
}

CVung* CKhuVuc::maxDeltaT() {
	float LonNhat = -1.0f;
	CVung* kq = nullptr;

	for (int i = 0; i < n; i++) {
		if (data[i]->TinhDeltaT() > LonNhat) {
			LonNhat = data[i]->TinhDeltaT();
			kq = data[i];
		}
	}

	return kq;
}