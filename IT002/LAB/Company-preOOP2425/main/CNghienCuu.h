#pragma once
#include "CHopDong.h"

class CNghienCuu : public CHopDong {
	private:
		float ChiPhiNhanSu;

	public:
		int getLoai();
		void Nhap();
		float getLoiNhuan();
};

