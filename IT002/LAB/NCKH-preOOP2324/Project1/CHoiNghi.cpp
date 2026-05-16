#include "CHoiNghi.h"

void CHoiNghi::setType(bool isCR) {
	isCoreRanking = isCR;
}

bool CHoiNghi::getType() {
	return isCoreRanking;
}

int CHoiNghi::getSoTiet() {
	if (isCoreRanking) return 1000;
	return 500;
}
int CHoiNghi::getLoaiDM() {
	return 1;
}
int CHoiNghi::getLoaiHoiNghi() {
	if (isCoreRanking) return 1;
	return 0;
}

int CHoiNghi::getLoaiTapChi() {
	return -1;
}