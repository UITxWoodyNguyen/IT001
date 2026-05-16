#include "CDsVatChu.h"

CDsVatChu::~CDsVatChu() {
	for (int i = 0; i < n; i++) {
		delete data[i];
	}
	data.clear();
}

void CDsVatChu::Nhap() {
	cout << "Nhap so luong vat chu: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "Nhap thong tin vat chu thu " << i + 1 << " : " << endl;
		CVatChu* temp = new CVatChu();
		temp->Nhap();

		data.push_back(temp);
	}
}

void CDsVatChu::Xuat() {
	for (int i = 0; i < n; i++) {
		cout << "Thong tin vat chu thu " << i + 1 << " : " << endl;
		data[i]->Xuat();
	}
}

int CDsVatChu::SoLuong(int loaiVirus, int mucDo) {
	int kq = 0;
	CVirus* tempType = nullptr;
	switch (loaiVirus) {
		case 1:
			tempType = new CEbola();
			break;
		case 2:
			tempType = new CHiv();
			break;
		default:
			tempType = new CCovid19();
	}

	for (int i = 0; i < n; i++) {
		if (data[i]->getLoaiTrieuChung(tempType) == mucDo) kq++;
	}

	delete tempType;
	return kq;
}

int CDsVatChu::cntDead() const {
	int kq = 0;
	
	for (int type = 0; type < 3; type++) {
		CVirus* tempType = nullptr;
		switch (type) {
		case 1:
			tempType = new CEbola();
			break;
		case 2:
			tempType = new CHiv();
			break;
		default:
			tempType = new CCovid19();
		}

		for (int i = 0; i < n; i++) {
			CMienDich* md = data[i]->getMucDo();
			if (data[i]->isTuVong(tempType, md)) kq++;
		}

		delete tempType;
	}

	return kq;
}