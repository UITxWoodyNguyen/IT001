#include <iostream>
#include "CDsHopDong.h"
using namespace std;

int main() {
	CDsHopDong list;
	list.Nhap();

	cout << "Tong loi nhuan: " << list.getLoiNhuan() << endl;
	cout << "Loai hop dong co loi nhuan cao nhat: ";
	int type = list.LoiNhuanCaoNhat();
	switch (type) {
		case 1:
			cout << "Hop dong nghien cuu" << endl;
			break;
		case 2:
			cout << "Hop dong tu van tai cho" << endl;
			break;
		default:
			cout << "Hop dong tron goi" << endl;
	}

	return 0;
}