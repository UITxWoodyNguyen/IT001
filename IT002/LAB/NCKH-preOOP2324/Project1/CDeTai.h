#pragma once
#include <iostream>
#include <string>
#include "CDsBaiBao.h"
using namespace std;

class CDeTai {
	private:
		string MaDT;
		string TenDT;
		string NgayDangKi;
		int TimeThucHien;
		string NgayNghiemThu;

		int RegSoTapChi;
		int RegSoHoiNghi;

	public:
		void Nhap();
		void Xuat();
		bool isNghiemThu(CDsBaiBao);
};

