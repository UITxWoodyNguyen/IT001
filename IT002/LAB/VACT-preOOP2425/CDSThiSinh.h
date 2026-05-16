#pragma once
#include <iostream>
#include "CThiSinh.h"

class CDSThiSinh {
    private:
        int n;
        vector<CThiSinh*> data;

    public:
        CDSThiSinh();
        ~CDSThiSinh();

        void Nhap();
        void Xuat(const CVact&);
        void XuatDiem(const CVact&);

        CThiSinh* DungNhieuNhat (const CVact&, int);
        CThiSinh* DungItNhat (const CVact&, int);

        float DiemCaoNhat (const CVact&, int);
        float DiemThapNhat (const CVact&, int);
};