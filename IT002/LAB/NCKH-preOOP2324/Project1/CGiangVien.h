#pragma once
#include <iostream>
#include <string>
using namespace std;

class CGiangVien {
private:
	string MaGV;
	string TenGV;
	string ChuyenNganh;
	string SDT;

public:
	void Nhap();
	void Xuat();
	string getMaSo();
};

