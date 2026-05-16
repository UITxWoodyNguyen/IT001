#include <iostream>
#include "CVatChu.h"
#include "CVirus.h"
#include "CCovid19.h"
#include "CEbola.h"
#include "CHiv.h"
#include "CMienDich.h"
#include "CCao.h"
#include "CThap.h"
#include "CTrungBinh.h"
#include "CDsVatChu.h"
using namespace std;

int main() {
	CDsVatChu ds1;
	ds1.Nhap();
	ds1.Xuat();

	CDsVatChu ds2;
	ds2.Nhap();

	const string nameVirus[] = { "SARS-Cov-2", "Ebola", "HIV" };
	for (int i = 0; i < 3; i++) {
		cout << "So luong vat chu gap trieu chung nang do virus " << nameVirus[i] << " : " << ds2.SoLuong(i, 2) << endl;
	}

	cout << "So luong vat chu da tu vong: " << ds2.cntDead() << endl;

	return 0;
}