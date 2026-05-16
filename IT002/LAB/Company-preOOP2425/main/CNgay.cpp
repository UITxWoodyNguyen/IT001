#include "CNgay.h"
#include <cmath>

istream& operator>> (istream& inp, CNgay& T) {
	char tmp1, tmp2;
	inp >> T.ngay >> tmp1 >> T.thang >> tmp2 >> T.nam;
	return inp;
}

ostream& operator<< (ostream& out, const CNgay& T) {
	out << T.ngay << "/" << T.thang << "/" << T.nam << endl;
	return out;
}

bool CNgay::isLeap() const {
	return ((nam % 4 == 0) || (nam % 400 == 0));
}

int CNgay::operator- (CNgay other) {
	int cntD1 = ngay;
	for (int i = 1; i <= nam; i++) {
		cntD1 += 365;
		if (isLeap()) cntD1++;
	}

	int soNgay[] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	for (int i = 1; i <= thang; i++) {
		cntD1 += soNgay[i];
		if (isLeap()) cntD1++;
	}

	int cntD2 = other.ngay;
	for (int i = 1; i <= other.nam; i++) {
		cntD2 += 365;
		if (other.isLeap()) cntD2++;
	}
	for (int i = 1; i <= thang; i++) {
		cntD2 += soNgay[i];
		if (other.isLeap()) cntD2++;
	}

	int diff = cntD2 - cntD1;
	return diff;
}