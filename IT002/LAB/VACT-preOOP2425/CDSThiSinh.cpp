#include "CDSThiSinh.h"
#include "CThiSinh.h"
#include "CVact.h"

CDSThiSinh::CDSThiSinh() : n(0) {}

CDSThiSinh::~CDSThiSinh() {
    for (CThiSinh* thiSinh : data) {
        delete thiSinh;
    }
}

void CDSThiSinh::Nhap() {
    cout << "Nhap so luong thi sinh: ";
    cin >> n;

    for(int i = 0; i < n; i++) {
        CThiSinh* thiSinh = new CThiSinh();
        cout << "Nhap thong tin thi sinh thu: " << i + 1 << endl;
        thiSinh->setSTT(i + 1);
        thiSinh->Nhap();
        data.push_back(thiSinh);
    }
}

void CDSThiSinh::Xuat(const CVact& vact) {
    cout << "Danh sach thi sinh: " << endl;
    for(int i = 0; i < n; i++) {
        data[i]->Xuat();
        data[i]->XuatDiem(vact);
    }
}

CThiSinh* CDSThiSinh::DungNhieuNhat(const CVact& vact, int part) {
    CThiSinh* maxThiSinh = nullptr;
    int maxCauDung = -1;

    for(int i = 0; i < n; i++) {
        int cauDung = data[i]->SoCauDung(vact, part);
        if (cauDung > maxCauDung) {
            maxCauDung = cauDung;
            maxThiSinh = data[i];
        }
    }
    return maxThiSinh;
}

CThiSinh* CDSThiSinh::DungItNhat(const CVact& vact, int part) {
    CThiSinh* minThiSinh = nullptr;
    int minCauDung = 4 * vact.getSoCauHoi() + 1; // so cau hoi toi da + 1

    for(int i = 0; i < n; i++) {
        int cauDung = data[i]->SoCauDung(vact, part);
        if (cauDung < minCauDung) {
            minCauDung = cauDung;
            minThiSinh = data[i];
        }
    }
    return minThiSinh;
}

float CDSThiSinh::DiemCaoNhat(const CVact& vact, int part) {
    float maxDiem = -1.0f;

    for(int i = 0; i < n; i++) {
        float diem = data[i]->TinhDiemThiTungPhan(vact, part);
        if (diem > maxDiem) {
            maxDiem = diem;
        }
    }
    return maxDiem;
}

float CDSThiSinh::DiemThapNhat(const CVact& vact, int part) {
    float minDiem = 4.0f * vact.getSoCauHoi() * 10.0f + 1.0f; // diem toi da + 1

    for(int i = 0; i < n; i++) {
        float diem = data[i]->TinhDiemThiTungPhan(vact, part);
        if (diem < minDiem) {
            minDiem = diem;
        }
    }
    return minDiem;
}

void CDSThiSinh::XuatDiem(const CVact& vact) {
    for(int i = 0; i < n; i++) {
        cout << "Thi sinh thu: " << data[i]->getSTT() << endl;
        cout << "Diem tong: " << data[i]->TinhDiemTong(vact) << endl;
        cout << endl;
    }
}