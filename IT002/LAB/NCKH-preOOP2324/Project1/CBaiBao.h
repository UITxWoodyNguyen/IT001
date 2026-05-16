#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CDanhMuc.h"
#include "CGiangVien.h"
using namespace std;

class CBaiBao {
private:
	string MaBB;
	string TenBB;
	string DOI_Link;
	int namXuatBan;

	CGiangVien* mainTacGia;
	vector<CGiangVien*> DsDongTG;
	CDanhMuc* DanhMuc;

	bool isRegister;

public:
	void Nhap();
	void Xuat();
	int getSoTiet();
	int getSoTietChoGV(const string);
	int getDanhMuc();
};

