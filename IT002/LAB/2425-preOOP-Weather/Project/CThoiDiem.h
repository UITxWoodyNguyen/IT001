#pragma once
#include <iostream>
using namespace std;

class CThoiDiem {
	private:
		float NhietDo;
		float DoAm;
		float TocDoGio;
		float BucXaMT;
		float LuongMua;

	public:
		void Nhap();
		void Xuat();
		float getNhietDo();
		int KieuThoiTiet();
};

