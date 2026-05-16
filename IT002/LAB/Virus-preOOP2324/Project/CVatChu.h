#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CVirus.h"
#include "CMienDich.h"

class CVatChu {
	private:
		string MaSo;	// ma so vat chu
		vector<CVirus*> DsVirus;	// Ds Virus bi nhiem
		CMienDich* MienDich;	// Muc do mien dich
		bool isVaccine[3];	// tiem vaccine cho loai virus thu i ? (0: Covid; 1: Ebola; 2: Hiv)

	public:
		CVatChu() : MienDich(nullptr) {}
		~CVatChu();
		int Random(int, int);

		void Nhap();
		void Xuat();
		CMienDich* getMucDo();
		void setVaccine(bool);
		void getTrieuChung(CVirus*);	// Trieu chung theo muc do 
		int getLoaiTrieuChung(CVirus*);	// Trieu chung theo muc do (0: Khong TC; 1: Nhe; 2: Nang)
		float XSTuVong(CVirus*, CMienDich*) const;	// XS tu vong khi nhiem loai virus... voi do mien dich..
		bool isTuVong(CVirus*, CMienDich*);
};

