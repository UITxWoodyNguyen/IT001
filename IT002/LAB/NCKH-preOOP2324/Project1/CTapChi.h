#pragma once
#include "CDanhMuc.h"

class CTapChi : public CDanhMuc {
	public:
		virtual int getSoTiet() = 0;
		virtual int getLoaiDM() = 0;
		virtual int getLoaiTapChi() = 0;

		virtual void setType(bool) = 0;
		virtual bool getType() = 0;
		virtual int getLoaiHoiNghi() = 0;	// 1: Core-R; 0: Non-Core-R
};

