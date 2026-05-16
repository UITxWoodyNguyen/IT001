#pragma once
#include "CTronGoi.h"

class CTaiCho : public CTronGoi {
private:
	float ChiPhiSinhHoat;

public:
	int getLoai();
	void Nhap();
	float getLoiNhuan();
};

