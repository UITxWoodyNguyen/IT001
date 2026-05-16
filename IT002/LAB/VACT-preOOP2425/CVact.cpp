#include "CVact.h"
#include "CCauHoi.h"

CVact::CVact() : m(0) {}

CVact::~CVact() {
    for (CCauHoi* cauHoi : BaiThi) {
        delete cauHoi;
    }
}

void CVact::Nhap() {
    cout << "Nhap so cau hoi trong 1 phan thi: ";
    cin >> m;

    BaiThi.push_back(nullptr);   // them phan tu gia o vi tri 0 (do bai thi bat dau tu 1)

    for(int i = 0; i < m; i++) {
        CCauHoi* cauHoi = new CCauHoi();
        cout << "Nhap thong tin cau hoi thu: " << i + 1 << endl;
        cauHoi->Nhap();
        TiengViet.push_back(cauHoi);
        BaiThi.push_back (cauHoi);
    }

    for(int i = 0; i < m; i++) {
        CCauHoi* cauHoi = new CCauHoi();
        cout << "Nhap thong tin cau hoi thu: " << m + i + 1 << endl;
        cauHoi->Nhap();
        TiengAnh.push_back(cauHoi);
        BaiThi.push_back (cauHoi);
    }

    for(int i = 0; i < m; i++) {
        CCauHoi* cauHoi = new CCauHoi();
        cout << "Nhap thong tin cau hoi thu: " << 2 * m + i + 1 << endl;
        cauHoi->Nhap();
        Toan.push_back(cauHoi);
        BaiThi.push_back (cauHoi);
    }

    for(int i = 0; i < m; i++) {
        CCauHoi* cauHoi = new CCauHoi();
        cout << "Nhap thong tin cau hoi thu: " << 3 * m + i + 1 << endl;
        cauHoi->Nhap();
        KhoaHoc.push_back(cauHoi);
        BaiThi.push_back (cauHoi);
    }
}

void CVact::Xuat() {
    cout << "Thong tin bai thi: " << endl;
    for (int i = 1; i <= 4 * m; i++) {
        cout << "Cau hoi thu: " << i << endl;
        BaiThi[i]->Xuat();
    }
}

int CVact::getSoCauHoi() const {
    return m;
}

vector<CCauHoi*> CVact::PhanLoaiCauHoi(int loai) {
    vector<CCauHoi*> result;
    for(int i = 1; i <= 4*m; i++) {
        if (BaiThi[i]->PhanLoaiCauHoi() == loai) {
            result.push_back(BaiThi[i]);
        }
    }
    return result;
}

vector<CCauHoi*> CVact::PhanLoaiDoKho(int doKho) {
    vector<CCauHoi*> result;
    for(int i = 1; i <= 4*m; i++) {
        if (BaiThi[i]->PhanLoaiDoKho() == doKho) {
            result.push_back(BaiThi[i]);
        }
    }
    return result;
}