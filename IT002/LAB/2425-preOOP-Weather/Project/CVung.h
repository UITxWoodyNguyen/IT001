#pragma once
#include <iostream>
#include <string>
#include "CThoiDiem.h"
using namespace std;

class CVung {
	private:
		string Ten;
		float DoCao;
		float DoChePhu;
		CThoiDiem* t1;
		CThoiDiem* t2;

	public:
		void Nhap();
		void Xuat();
		string getTen();
		float TinhDeltaT();
		int KieuThoiTiet(int);
};

