#pragma once
#include "CHopDong.h"

class CTronGoi : public CHopDong {
	private:
		CNgay NgayThucTe;
		float GiaTriHopDong;

	public:
		int getLoai();
		void Nhap();
		float getLoiNhuan();
};

