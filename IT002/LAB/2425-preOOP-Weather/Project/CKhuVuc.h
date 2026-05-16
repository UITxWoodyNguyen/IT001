#pragma once
#include <iostream>
#include <vector>
#include "CVung.h"
using namespace std;

class CKhuVuc {
private:
	int n;
	vector<CVung*> data;

public:
	void Nhap();
	void Xuat();
	vector<CVung*> TimKiem(int, int);
	CVung* maxDeltaT();
};

