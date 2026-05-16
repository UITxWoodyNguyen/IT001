#include "CCao.h"

float CCao::getXSKhongTrieuChung(bool isVaccine) {
	if (isVaccine) return 0.7f;
	return 0.5f;
}

float CCao::getXSNhe(bool isVaccine) {
	if (isVaccine) return 0.25f;
	return 0.35f;
}

float CCao::getXSNang(bool isVaccine) {
	if (isVaccine) return 0.05f;
	return 0.15f;
}

float CCao::getXSTuVong(bool isVaccine) {
	if (isVaccine) return 0.4f;
	return 0.5f;
}