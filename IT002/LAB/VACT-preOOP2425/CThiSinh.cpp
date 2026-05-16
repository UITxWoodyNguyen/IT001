#include "CThiSinh.h"
#include "CVact.h"
#include "CCauHoi.h"

namespace {
void GetPartRange(const CVact& vact, int part, int& startIdx, int& endIdx) {
    int soCau = vact.getSoCauHoi();

    startIdx = 1;
    endIdx = 4 * soCau;
    switch(part) {
        case 1:
            startIdx = 1;
            endIdx = soCau;
            break;
        case 2:
            startIdx = soCau + 1;
            endIdx = 2 * soCau;
            break;
        case 3:
            startIdx = 2 * soCau + 1;
            endIdx = 3 * soCau;
            break;
        case 4:
            startIdx = 3 * soCau + 1;
            endIdx = 4 * soCau;
            break;
    }
}
}

CThiSinh::CThiSinh() : STTThiSinh(0), u(1, 0) {}

void CThiSinh::Nhap() {
    cout << "Nhap so thu tu cac cau thi sinh lam dung (Nhap -1 de ket thuc): " << endl;
    int soCauDung = 0;
    while (true) {
        cin >> soCauDung;
        if (soCauDung == -1) {
            break;
        }
        if (soCauDung > 0) {
            if (static_cast<size_t>(soCauDung) >= u.size()) {
                u.resize(soCauDung + 1, 0);
            }
            u[soCauDung] = 1;   // danh dau cau thi sinh lam dung
        }
    }
}

void CThiSinh::Xuat() {
    cout << "So thu tu thi sinh: " << STTThiSinh << endl;
}

void CThiSinh::setSTT(int stt) {
    STTThiSinh = stt;
}

int CThiSinh::getSTT() {
    return STTThiSinh;
}

float CThiSinh::TinhNangLuc(const CVact& vact, int part) {
    int startIdx = 1;
    int endIdx = 0;
    GetPartRange(vact, part, startIdx, endIdx);

    float NangLuc = 0.0f;
    for(int i = startIdx; i <= endIdx; i++) {
        float HSPhanBiet = vact.BaiThi[i]->getHSPhanBiet();
        float TieuChuan = vact.BaiThi[i]->getP(0.0f);  // tieu chuan de tinh nang luc
        
        NangLuc += (HSPhanBiet * (u[i] - TieuChuan));
    }

    return NangLuc;
}

float CThiSinh::TinhNangLucMax(const CVact& vact, int part) {
    int startIdx = 1;
    int endIdx = 0;
    GetPartRange(vact, part, startIdx, endIdx);

    float NangLuc = 0.0f;
    for(int i = startIdx; i <= endIdx; i++) {
        float HSPhanBiet = vact.BaiThi[i]->getHSPhanBiet();
        float TieuChuan = 1.0f; // lam dung het
        
        NangLuc += (HSPhanBiet * (1.0f - TieuChuan));
    }

    return NangLuc;
}

float CThiSinh::TinhNangLucMin(const CVact& vact, int part) {
    int startIdx = 1;
    int endIdx = 0;
    GetPartRange(vact, part, startIdx, endIdx);

    float NangLuc = 0.0f;
    for(int i = startIdx; i <= endIdx; i++) {
        float HSPhanBiet = vact.BaiThi[i]->getHSPhanBiet();
        float TieuChuan = 0.0f; // lam sai het
        
        NangLuc += (HSPhanBiet * (0.0f - TieuChuan));
    }

    return NangLuc;
}

float CThiSinh::TinhDiemThiTungPhan(const CVact& vact, int part) {
    float NangLuc = TinhNangLuc(vact, part);
    float NangLucMax = TinhNangLucMax(vact, part);
    float NangLucMin = TinhNangLucMin(vact, part);

    if (NangLucMax == NangLucMin) {
        return 0.0f;
    }

    return 10.0f * (NangLuc - NangLucMin) / (NangLucMax - NangLucMin); // chuyen doi sang diem 10
}

float CThiSinh::TinhDiemTong(const CVact& vact) {
    float DiemTong = 0.0f;
    for(int part = 1; part <= 4; part++) {
        DiemTong += TinhDiemThiTungPhan(vact, part);
    }
    return DiemTong;
}

int CThiSinh::SoCauDung(const CVact& vact, int part) {
    int startIdx = 1;
    int endIdx = 0;
    GetPartRange(vact, part, startIdx, endIdx);

    int count = 0;
    for(int i = startIdx; i <= endIdx; i++) {
        if (static_cast<size_t>(i) < u.size() && u[i] == 1) {
            count++;
        }
    }
    return count;
}

void CThiSinh::XuatDiem(const CVact& vact) {
    int soCauDung = 0;
    for(int i = 1; i <= 4; i++) {
        soCauDung += SoCauDung(vact, i);
    }

    cout << "So cau dung: " << soCauDung << endl;

    string partNames[] = {"Tieng Viet", "Tieng Anh", "Toan", "Khoa Hoc"};
    for(int part = 1; part <= 4; part++) {
        cout << "Diem phan " << partNames[part - 1] << ": " << TinhDiemThiTungPhan(vact, part) << endl;
    }

    cout << "Diem tong: " << TinhDiemTong(vact) << endl;
}