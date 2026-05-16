#pragma once
#include "CTapChi.h"

class CScopus : public CTapChi {
	public:
		int getSoTiet();
		int getLoaiDM();
		int getLoaiTapChi();

		void setType(bool);
		bool getType();
		int getLoaiHoiNghi();
};

