#include "CEbola.h"

void CEbola::getTrieuChung(int mucDo) {
	switch (mucDo) {
	case 1:	// Trieu chung nhe
		cout << "Trieu chung NHE: Sot, dau hong, dau co, dau dau" << endl;
		break;
	case 2:	// Trieu chung nang
		cout << "Trieu chung NANG: Non mua, tieu chay, xuat huyet trong va ngoai" << endl;
		break;
	default:	// Khong trieu chung
		cout << "Khong trieu chung !" << endl;
	};
}

float CEbola::getTiLeTuVong() {
	return 0.5f;
}

int CEbola::getLoai() {
	return 1;
}