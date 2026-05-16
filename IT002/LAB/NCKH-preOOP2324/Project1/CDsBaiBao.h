#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "CBaiBao.h"
using namespace std;

class CDsBaiBao {
	private:
		int n;
		vector<CBaiBao*> data;

	public:
		void Nhap();
		void Xuat();
		int getSoTietGV(const string);
		int DemSoTapChi();
		int DemSoHoiNghi();
};

