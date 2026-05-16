#include <cmath>
#include "CCauHoi.h"

void CCauHoi::Nhap() {
    cout << "Nhap he so phan biet cua cau hoi: ";
    cin >> HSPhanBiet;

    cout << "Nhap do kho cua cau hoi: ";
    cin >> DoKho;
}

void CCauHoi::Xuat() {
    cout << "He so phan biet cua cau hoi: " << HSPhanBiet << endl;
    cout << "Do kho cua cau hoi: " << DoKho << endl;
}

float CCauHoi::getHSPhanBiet() const {
    return HSPhanBiet;
}

float CCauHoi::getDoKho() const {
    return DoKho;
}

float CCauHoi::getP (float NangLuc) {
    return 1 / (1 + exp(-HSPhanBiet * (NangLuc - DoKho)));
}

int CCauHoi::PhanLoaiCauHoi() {
    if (HSPhanBiet >= 0 && HSPhanBiet < 0.6) return 0;  // phan biet chua tot
    else if (HSPhanBiet >= 0.6 && HSPhanBiet <= 1.7) return 1;   // phan biet tot
    else return 2;  // phan biet qua tot
}

int CCauHoi::PhanLoaiDoKho() {
    if (DoKho >= -3 && DoKho < -1) return 0;    // cau hoi de
    else if (DoKho >= -1 && DoKho <= 1) return 1;   // cau hoi trung binh
    else return 2;  // cau hoi kho
}