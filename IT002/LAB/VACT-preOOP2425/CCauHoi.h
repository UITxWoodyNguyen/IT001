#pragma once
#include <iostream>
using namespace std;

class CCauHoi {
    protected:
        float HSPhanBiet;
        float DoKho;

    public:
        void Nhap();
        void Xuat();

        float getHSPhanBiet() const;
        float getDoKho() const;

        float getP(float);
        int PhanLoaiCauHoi();
        int PhanLoaiDoKho();
};