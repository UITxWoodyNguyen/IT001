#include "CDsBaiBao.h"

void CDsBaiBao::Nhap() {
	cout << "Nhap so luong bai bao: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "Nhap thong tin bai bao thu " << i + 1 << " : " << endl;
		CBaiBao* temp = new CBaiBao();
		temp->Nhap();
		data.push_back(temp);
	}
}

void CDsBaiBao::Xuat() {
	for (int i = 0; i < n; i++) {
		cout << "Thong tin bai bao thu " << i + 1 << " : " << endl;
		data[i]->Xuat();
	}
}

int CDsBaiBao::getSoTietGV(const string MaSo) {
	int tongTiet = 0;
	for (int i = 0; i < n; i++) tongTiet += data[i]->getSoTietChoGV(MaSo);
	return tongTiet;
}

int CDsBaiBao::DemSoTapChi() {
	int dem = 0;
	for (int i = 0; i < n; i++) {
		if (data[i]->getDanhMuc() == 0) dem++;
	}

	return dem;
}

int CDsBaiBao::DemSoHoiNghi() {
	int dem = 0;
	for (int i = 0; i < n; i++) {
		if (data[i]->getDanhMuc() == 1) dem++;
	}

	return dem;
}