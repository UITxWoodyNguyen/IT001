#pragma once
#include <iostream>
using namespace std;

class CDanhMuc {
	protected:
		bool isCoreRanking;
	public:
		virtual void setType(bool) = 0;
		virtual bool getType() = 0;

		virtual int getSoTiet() = 0;	// so tiet
		virtual int getLoaiDM() = 0;	// 0: Tap chi; 1: Hoi nghi
		virtual int getLoaiTapChi() = 0;	// 0: ISI; 1:Scopus; 2: Non-index
		virtual int getLoaiHoiNghi() = 0;	// 1: Core-R; 0: Non-Core-R
};

