#pragma once
#include <iostream>
#include <vector>
#include "CVact.h"
using namespace std;

class CThiSinh {
    private:
        int STTThiSinh;
        vector<int> u; // u[i] = 1 (cau i dung), u[i] = 0 (cau i sai)

    public:
        CThiSinh();

        void Nhap();
        void Xuat();

        void setSTT(int);
        int getSTT();

        float TinhNangLuc(const CVact&, int);
        float TinhNangLucMax(const CVact&, int);
        float TinhNangLucMin(const CVact&, int);

        float TinhDiemThiTungPhan(const CVact&, int);
        int SoCauDung(const CVact&, int);

        float TinhDiemTong(const CVact&);

        void XuatDiem(const CVact&);
};