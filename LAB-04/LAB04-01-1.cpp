#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+5;

// declare variables here
struct Time {
    int hour, min, sec;
};

struct input {
    int getHour () {
        int n;
        int low = 0, high = 23;
        do {
            cout << "Nhap so gio trong khoang [" << low << ", " << high << "]: ";
            cin >> n;
        } while (n < low || n > high);
        return n;
    }

    int getMinute () {
        int n;
        int low = 0, high = 59;
        do {
            cout << "Nhap so phut trong khoang [" << low << ", " << high << "]: ";
            cin >> n;
        } while (n < low || n > high);
        return n;
    }

    int getSecond () {
        int n;
        int low = 0, high = 59;
        do {
            cout << "Nhap so giay trong khoang [" << low << ", " << high << "]: ";
            cin >> n;
        } while (n < low || n > high);
        return n;
    }
} getData;

// Hàm kiểm tra tính hợp lệ của thời gian
bool isValidTime (Time t) {
    if (t.hour < 0 || t.hour > 23) return 0;
    if (t.min < 0 || t.min > 59) return 0;
    if (t.sec < 0 || t.sec > 59) return 0;
    return 1;
}

// Hàm sắp xếp thời gian theo thứ tự tăng dần (t1 trước t2)
void sortTime (Time& t1, Time& t2) {
    if (t1.hour > t2.hour) swap(t1, t2);
    else if (t1.hour == t2.hour) {
        if (t1.min > t2.min) swap(t1, t2);
        else if (t1.min == t2.min) {
            if (t1.sec > t2.sec) swap(t1, t2);
        }
    }
}

// Hàm tính số giây giữa hai thời điểm
int countSec (Time t1, Time t2) {
    int total1 = t1.hour * 3600 + t1.min * 60 + t1.sec;
    int total2 = t2.hour * 3600 + t2.min * 60 + t2.sec;
    return abs(total2 - total1);
}

bool checkTime (Time t1, Time t2) {
    if (t1.hour < t2.hour) return true;
    else if (t1.hour == t2.hour) {
        if (t1.min < t2.min) return true;
        else if (t1.min == t2.min) {
            if (t1.sec < t2.sec) return true;
        }
    }
    return false;
}

int main () {
    // Get input
    Time time_1, time_2;
    do {
        cout << "Nhap thoi gian thu nhat:" << endl;
        time_1.hour = getData.getHour();
        time_1.min = getData.getMinute();
        time_1.sec = getData.getSecond();
    } while (!isValidTime(time_1));
    cout << endl;
    do {
        cout << "Nhap thoi gian thu hai:" << endl;
        time_2.hour = getData.getHour();
        time_2.min = getData.getMinute();
        time_2.sec = getData.getSecond();
    } while (!isValidTime(time_2));

    // (a) Tính khoảng cách giữa 2 thời điểm t1 và t2 theo giây
    int diff = countSec(time_1, time_2);
    cout << "So giay giua " << time_1.hour << ":" << time_1.min << ":" << time_1.sec << " va " << time_2.hour << ":" << time_2.min << ":" << time_2.sec << " la: " << diff << " giay." << endl;

    // (b) Tính khoảng cách theo giây với t1 là thời điểm trước và t2 là thời điểm sau; nếu t2 < t1 thì t2 thuộc ngày hôm sau.
    if (!checkTime(time_1, time_2)) {
        Time new_day = {0,0,0}, pre_midnight = {23,59,59};
        int sec_to_midnight = countSec(time_1, pre_midnight); // time_1 --> 23:59:59
        int sec_to_midnight2 = countSec(new_day, time_2); // 00:00:00 --> time_2
        int total_sec = sec_to_midnight + 1 + sec_to_midnight2;
        cout << "So giay giua " << time_1.hour << ":" << time_1.min << ":" << time_1.sec << " va " << time_2.hour << ":" << time_2.min << ":" << time_2.sec << " (voi t1 la ngay hom truoc, t2 la ngay hom sau) la: " << total_sec << " giay." << endl;
    } else cout << "So giay giua " << time_1.hour << ":" << time_1.min << ":" << time_1.sec << " va " << time_2.hour << ":" << time_2.min << ":" << time_2.sec << " la: " << diff << " giay." << endl;

}