#include "CTrungBinh.h"

float CTrungBinh::getXSKhongTrieuChung(bool isVaccine) {
	if (isVaccine) return 0.2f;
	return 0.1f;
}

float CTrungBinh::getXSNhe(bool isVaccine) {
	if (isVaccine) return 0.5f;
	return 0.4f;
}

float CTrungBinh::getXSNang(bool isVaccine) {
	if (isVaccine) return 0.3f;
	return 0.5f;
}

float CTrungBinh::getXSTuVong(bool isVaccine) {
	if (isVaccine) return 0.6f;
	return 0.7f;
}