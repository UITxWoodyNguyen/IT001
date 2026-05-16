#include "CHiv.h"

void CHiv::getTrieuChung(int mucDo) {
	switch (mucDo) {
	case 1:	// Trieu chung nhe
		cout << "Trieu chung NHE: Cam, sot" << endl;
		break;
	case 2:	// Trieu chung nang
		cout << "Trieu chung NANG: Met moi, sung hach keo dai, lo loet, viem phoi, tieu chay nang" << endl;
		break;
	default:	// Khong trieu chung
		cout << "Khong trieu chung !" << endl;
	};
}

float CHiv::getTiLeTuVong() {
	return 0.9f;
}

int CHiv::getLoai() {
	return 2;
}