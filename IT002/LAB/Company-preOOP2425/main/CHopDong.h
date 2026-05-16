#pragma once
#include<iostream>
#include<string>
#include "CNgay.h"
using namespace std;

class CHopDong {
	protected:
		string DoiTac;
		string projectName;
		CNgay NgayHoanThanh;
		string LinhVuc;
		string YeuCauKT;
	
		float ChiPhiChung;
		float ChiPhiBanDau;
		int ThoiGianDuKien;

		float TongLuongNgay;

	public:
		virtual int getLoai() = 0;
		virtual void Nhap() = 0;
		virtual float getLoiNhuan() = 0;
};

