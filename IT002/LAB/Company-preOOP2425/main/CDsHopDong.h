#pragma once
#include <iostream>
#include <vector>
#include "CHopDong.h"

using namespace std;

class CDsHopDong {
	private:
		int n;
		vector<CHopDong*> data;

public:
	void Nhap();
	float getLoiNhuan();
	int LoiNhuanCaoNhat();
};

