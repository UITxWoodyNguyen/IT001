#pragma once
#include "CTapChi.h"

class CIsi : public CTapChi {
public:
	void setType(bool);
	bool getType();
	int getLoaiHoiNghi();

	int getSoTiet();
	int getLoaiDM();
	int getLoaiTapChi();
};

