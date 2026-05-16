#include "CVatChu.h"
#include "CVirus.h"
#include "CCovid19.h"
#include "CEbola.h"
#include "CHiv.h"
#include "CMienDich.h"
#include "CCao.h"
#include "CThap.h"
#include "CTrungBinh.h"

CVatChu::~CVatChu() {
	for(auto v : DsVirus) {
		delete v;
	}
	DsVirus.clear();
	delete MienDich;
}

int CVatChu::Random(int a, int b) {
	return rand() % (b - a + 1) + a;
}

void CVatChu::Nhap() {
	cout << "Nhap ma so vat chu: ";
	cin >> MaSo;

	DsVirus.push_back(new CCovid19());
	DsVirus.push_back(new CEbola());
	DsVirus.push_back(new CHiv());
	
	int level;
	cout << "Nhap muc do mien dich cua vat chu (0: Thap; 1: Trung Binh; 2: Cao): ";
	cin >> level;
	switch (level) {
		case 1:
			MienDich = new CTrungBinh();
			break;
		case 2:
			MienDich = new CCao();
			break;
		default:
			MienDich = new CThap();
	}

	int vaccine;
	cout << "Da tiem vaccine hay chua? (0: chua; 1: roi): ";
	cin >> vaccine;

	if (vaccine == 1) setVaccine(true);
	else setVaccine(false);
}

void CVatChu::Xuat() {
	cout << "Ma so vat chu: " << MaSo << endl;

	const string nameVirus[] = { "SARS-Cov-2", "Ebola", "HIV" };
	for (int i = 0; i < 3; i++) {
		cout << "Trieu chung khi nhiem virus " << nameVirus[i] << " :" << endl;
		getTrieuChung(DsVirus[i]);

		if (isTuVong(DsVirus[i], MienDich)) cout << "Vat chu da tu vong !" << endl;
	}
}

void CVatChu::setVaccine(bool DaTiem) {
	for (int i = 0; i < 3; i++) isVaccine[i] = DaTiem;
}

CMienDich* CVatChu::getMucDo() {
	return MienDich;
}

void CVatChu::getTrieuChung(CVirus* virus) {
	int loaiVirus = virus->getLoai();
	CMienDich* md = getMucDo();
	float r = Random(0, 100) / 100.f;
	
	float nguongMienDich = md->getXSKhongTrieuChung(isVaccine[loaiVirus]);
	if (r < nguongMienDich) {
		virus->getTrieuChung(0);
		return;
	}

	r -= nguongMienDich;
	nguongMienDich = md->getXSNhe(isVaccine[loaiVirus]);
	if (r < nguongMienDich) {
		virus->getTrieuChung(1);
		return;
	}

	virus->getTrieuChung(2);
}

int CVatChu::getLoaiTrieuChung(CVirus* virus) {
	int loaiVirus = virus->getLoai();
	CMienDich* md = getMucDo();
	float r = Random(0, 100) / 100.f;

	float nguongMienDich = md->getXSKhongTrieuChung(isVaccine[loaiVirus]);
	if (r < nguongMienDich) return 0;

	r -= nguongMienDich;
	nguongMienDich = md->getXSNhe(isVaccine[loaiVirus]);
	if (r < nguongMienDich) return 1;

	return 2;
}

float CVatChu::XSTuVong(CVirus* vr, CMienDich* md) const {
	float XSTuVongDoVirus = vr->getTiLeTuVong();
	int loaiVirus = vr->getLoai();
	float KhaNangMienDich = md->getXSTuVong(isVaccine[loaiVirus]);

	return XSTuVongDoVirus * KhaNangMienDich;
}

bool CVatChu::isTuVong(CVirus* vr, CMienDich* md) {
	float rate = Random(0, 100);
	return rate < XSTuVong(vr, md);
}