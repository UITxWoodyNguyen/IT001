#pragma once
#include <iostream>
#include <vector>
#include "CCauHoi.h"
using namespace std;

class CVact {
    private:
        int m; // so cau hoi 1 phan
        vector<CCauHoi*> TiengViet;
        vector<CCauHoi*> TiengAnh;
        vector<CCauHoi*> Toan;
        vector<CCauHoi*> KhoaHoc;

    public:
        vector<CCauHoi*> BaiThi;

        CVact();
        ~CVact();
        
        void Nhap();
        void Xuat();

        int getSoCauHoi() const;

        vector<CCauHoi*> PhanLoaiCauHoi(int);
        vector<CCauHoi*> PhanLoaiDoKho(int);

        float TinTonghDiem();   // tong diem bai thi
        float TinhDiemMotPhan (int);   // diem cua 1 phan thi
};