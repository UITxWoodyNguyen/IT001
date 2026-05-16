#pragma once
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

class CDsVatChu {
	private:
		int n;
		vector<CVatChu*> data;

	public:
		~CDsVatChu();
		void Nhap();
		void Xuat();
		int SoLuong(int, int);
		int cntDead() const;
};

