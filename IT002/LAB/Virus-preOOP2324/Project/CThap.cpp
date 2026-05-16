#include "CThap.h"

float CThap::getXSKhongTrieuChung(bool isVaccine) {
	if (isVaccine) return 0.1f;
	return 0.05f;
}

float CThap::getXSNhe(bool isVaccine) {
	if (isVaccine) return 0.4f;
	return 0.15f;
}

float CThap::getXSNang(bool isVaccine) {
	if (isVaccine) return 0.5f;
	return 0.8f;
}

float CThap::getXSTuVong(bool isVaccine) {
	if (isVaccine) return 0.8f;
	return 1;
}