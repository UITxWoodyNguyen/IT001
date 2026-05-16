#pragma once
#include "CDanhMuc.h"

class CHoiNghi : public CDanhMuc {
	public:
		void setType(bool);
		bool getType();

		int getSoTiet();
		int getLoaiDM();
		int getLoaiHoiNghi();
		int getLoaiTapChi();
};

