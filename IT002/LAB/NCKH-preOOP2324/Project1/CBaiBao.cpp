#include "CBaiBao.h"
#include "CTapChi.h"
#include "CIsi.h"
#include "CScopus.h"
#include "CNonIdx.h"
#include "CHoiNghi.h"

void CBaiBao::Nhap() {
	cout << "Nhap ma bai bao: ";
	cin >> MaBB;

	cout << "Nhap ten bai bao: ";
	cin.ignore();
	getline(cin, TenBB);

	cout << "Nhap lien ket tham chieu (DOI): ";
	cin >> DOI_Link;

	cout << "Nhap nam xuat ban: ";
	cin >> namXuatBan;

	cout << "Nhap thong tin TAC GIA CHINH: " << endl;
	mainTacGia = new CGiangVien();
	mainTacGia->Nhap();

	int n;
	cout << "Nhap so luong DONG TAC GIA: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "Nhap thong tin DONG TAC GIA thu " << i + 1 << " : " << endl;
		CGiangVien* temp = new CGiangVien();
		temp->Nhap();

		DsDongTG.push_back(temp);
	}

	int loaiDM;
	cout << "Nhap loai danh muc cua bai bao (0: Tap chi; 1: Hoi nghi): ";
	cin >> loaiDM;

	if (loaiDM == 0) {
		int loaiTapChi;
		cout << "Nhap loai tap chi (0: ISI; 1: Scopus; 2: Non-Index) : ";
		cin >> loaiTapChi;

		switch (loaiTapChi) {
			case 1:
				DanhMuc = new CScopus();
				break;
			case 2:
				DanhMuc = new CNonIdx();
				break;
			default:
				DanhMuc = new CIsi();
		}
	}
	else {
		DanhMuc = new CHoiNghi();
		int loaiHoiNghi;
		cout << "Bai bao co thuoc Core Ranking hay khong ? (1: Co; 0: Khong): ";
		cin >> loaiHoiNghi;

		if (loaiHoiNghi == 1) DanhMuc->setType(true);
		else DanhMuc->setType(false);
	}

	int DaDangKi;
	cout << "Bai bao da dang ki cho de tai hay chua? (1: Roi; 0: Chua): ";
	cin >> DaDangKi;
	isRegister = DaDangKi;
}

void CBaiBao::Xuat() {
	cout << "Ma bai bao: " << MaBB << endl;
	cout << "Ten bai bao: " << TenBB << endl;
	cout << "Lien ket dan xuat (DOI): " << DOI_Link << endl;
	cout << "Nam xuat ban: " << namXuatBan << endl;
	cout << "Thong tin tac gia chinh: " << endl;
	mainTacGia->Xuat();

	cout << "Thong tin cac dong tac gia: " << endl;
	for (int i = 0; i < DsDongTG.size(); i++) {
		cout << "Thong tin dong tac gia thu " << i + 1 << " : " << endl;
		DsDongTG[i]->Xuat();
	}

	int loaiDanhMuc = DanhMuc->getLoaiDM();
	if (loaiDanhMuc == 0) {
		cout << "Bai bao thuoc danh muc Tap Chi" << endl;
		int loaiTC = DanhMuc->getLoaiTapChi();
		switch (loaiTC) {
			case 1:
				cout << "Bai bao thuoc Tap Chi Scopus" << endl;
				break;
			case 2:
				cout << "Bai bao thuoc Tap Chi Non-Index" << endl;
				break;
			default:
				cout << "Bai bao thuoc Tap Chi ISI" << endl;
		}
	}
	else {
		cout << "Bai bao thuoc danh muc Hoi Nghi" << endl;
		bool loaiHN = DanhMuc->getLoaiHoiNghi();
		if (loaiHN) cout << "Bai bao thuoc Core Ranking" << endl;
		else cout << "Bai bao KHONG thuoc Core Ranking" << endl;
	}

	if (isRegister) cout << "Bai bao duoc dang ky vao de tai NCKH" << endl;
	else cout << "Bai bao KHONG duoc dang ky vao de tai NCKH" << endl;

	cout << endl;
}

int CBaiBao::getSoTiet() {
	int soTiet = DanhMuc->getSoTiet();
	if (isRegister) return (soTiet * 65) / 100;

	return soTiet;
}

int CBaiBao::getSoTietChoGV(const string MaSo) {
	int TongSoTiet = getSoTiet();
	TongSoTiet /= 2;
	string MSChinh = mainTacGia->getMaSo();

	if (MaSo.compare(MSChinh) == 0) return TongSoTiet;
	else {
		int cntDongTG = DsDongTG.size();
		if (cntDongTG > 0) {
			TongSoTiet /= cntDongTG;

			for (auto gv : DsDongTG) {
				if (gv->getMaSo().compare(MaSo) == 0)
					return TongSoTiet;
			}
		}
	}

	return 0;
}

int CBaiBao::getDanhMuc() {
	return DanhMuc->getLoaiDM();
}