#include <iostream>
#include "CVact.h"
#include "CThiSinh.h"
#include "CDSThiSinh.h"
using namespace std;

template <typename T>
void XuatDanhSach(const vector<T*>& danhSach) {
    for (size_t i = 0; i < danhSach.size(); i++) {
        cout << "Cau hoi thu " << i + 1 << ":" << endl;
        danhSach[i]->Xuat();
        cout << endl;
    }
}

int main () {
    /* Cau 2: Nhap de thi + phan loai cau hoi */
    CVact vact;
    vact.Nhap();
    
    vector<CCauHoi*> DSCauHoiKem = vact.PhanLoaiCauHoi(0); // 0 là loại câu hỏi kém
    vector<CCauHoi*> DSCauHoiDe = vact.PhanLoaiDoKho(0); // 0 là loại câu hỏi dễ

    vector<CCauHoi*> DSCauHoiThuong = vact.PhanLoaiCauHoi(1); // 1 là loại câu hỏi thường
    vector<CCauHoi*> DSCauHoiTrungBinh = vact.PhanLoaiDoKho(1); // 1 là loại câu hỏi trung bình

    vector<CCauHoi*> DSCauHoiTot = vact.PhanLoaiCauHoi(2); // 2 là loại câu hỏi tốt
    vector<CCauHoi*> DSCauHoiKho = vact.PhanLoaiDoKho(2); // 2 là loại câu hỏi khó

    cout << "Danh sach cau hoi kem: " << endl;
    XuatDanhSach(DSCauHoiKem);

    cout << "Danh sach cau hoi thuong: " << endl;
    XuatDanhSach(DSCauHoiThuong);

    cout << "Danh sach cau hoi tot: " << endl;
    XuatDanhSach(DSCauHoiTot);

    cout << "Danh sach cau hoi de: " << endl;
    XuatDanhSach(DSCauHoiDe);

    cout << "Danh sach cau hoi trung binh: " << endl;
    XuatDanhSach(DSCauHoiTrungBinh);

    cout << "Danh sach cau hoi kho: " << endl;
    XuatDanhSach(DSCauHoiKho);

    /* Cau 3: Nhap ds thi sinh + tim so cau dung nhieu/it nhat moi phan thi */
    CDSThiSinh ds;
    ds.Nhap();
    ds.Xuat(vact);

    string phanThi[] = {"Tieng Viet", "Tieng Anh", "Toan", "Khoa Hoc"};
    for(int part = 1; part <= 4; part++) {
        CThiSinh* maxThiSinh = ds.DungNhieuNhat(vact, part);
        CThiSinh* minThiSinh = ds.DungItNhat(vact, part);

        cout << "Phan thi: " << phanThi[part - 1] << endl;
        cout << "Thi sinh co so cau dung nhieu nhat: " << endl;
        maxThiSinh->Xuat();

        cout << "Thi sinh co so cau dung it nhat: " << endl;
        minThiSinh->Xuat();
    }

    /* Cau 4: Xuat diem + so diem cao/thap nhat moi phan thi */
    cout << "Danh sach diem thi sinh: " << endl;
    ds.XuatDiem(vact);

    for(int part = 1; part <= 4; part++) {
        float diemCaoNhat = ds.DiemCaoNhat(vact, part);
        float diemThapNhat = ds.DiemThapNhat(vact, part);

        cout << "Phan thi: " << phanThi[part - 1] << endl;
        cout << "Diem cao nhat: " << diemCaoNhat << endl;
        cout << "Diem thap nhat: " << diemThapNhat << endl;
    }

    return 0;
}