#include "CDsHopDong.h"
#include "CHopDong.h"
#include "CNghienCuu.h"
#include "CTaiCho.h"
#include "CTronGoi.h"

#define REP(i, a, b) for (int i = a, _b = (b); i < _b; ++i)

void CDsHopDong::Nhap() {
	cout << "Nhap so luong hop dong: ";
	cin >> n;
	data.resize(n);

	for(int i = 0; i < n; i++) {
		cout << "Nhap thong tin hop dong thu " << i + 1 << " : " << endl;
		int type;
		cout << "Nhap loai hop dong: ";
		cin >> type;
		switch (type) {
			case 1:
				data[i] = new CNghienCuu();
				break;
			case 2:
				data[i] = new CTaiCho();
				break;
			default:
				data[i] = new CTronGoi();
		}
		data[i]->Nhap();
	}
}

float CDsHopDong::getLoiNhuan() {
	float total = 0;
	for (int i = 0; i < n; i++) total += data[i]->getLoiNhuan();
	return total;
}

int CDsHopDong::LoiNhuanCaoNhat() {
	float max = -1.0;
	int type = -1;
	for (int i = 0; i < n; i++) {
		float cur = data[i]->getLoiNhuan();
		if (cur > max) {
			max = cur;
			type = data[i]->getLoai();
		}
	}

	return type;
}