#include "CCovid19.h"

void CCovid19::getTrieuChung(int mucDo) {
	switch (mucDo) {
		case 1:	// Trieu chung nhe
			cout << "Trieu chung NHE: Sot, ho, mat vi giac" << endl;
			break;
		case 2:	// Trieu chung nang
			cout << "Trieu chung NANG: Sot cao, ho khan, kho tho, dau dau du doi" << endl;
			break;
		default:	// Khong trieu chung
			cout << "Khong trieu chung !" << endl;
	};
}

float CCovid19::getTiLeTuVong() {
	return 0.05f;
}

int CCovid19::getLoai() {
	return 0;
}