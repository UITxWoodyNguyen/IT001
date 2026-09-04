#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = a, _b = (b); i <= _b; ++i)
#define REP(i, a, b) for (int i = a, _b = (b); i < _b; ++i)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; --i)
#define nl cout << endl
#define endl '\n'

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }

struct Time {
    int day, month, year, hour, min, sec;
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

    int getDay () {
        int n;
        int low = 1, high = 31;
        do {
            cout << "Nhap so ngay trong khoang [" << low << ", " << high << "]: ";
            cin >> n;
        } while (n < low || n > high);
        return n;
    }

    int getMonth () {
        int n;
        int low = 1, high = 12;
        do {
            cout << "Nhap so thang trong khoang [" << low << ", " << high << "]: ";
            cin >> n;
        } while (n < low || n > high);
        return n;
    }

    int getYear () {
        int n;
        int low = 2000, high = 2099;
        do {
            cout << "Nhap so nam trong khoang [" << low << ", " << high << "]: ";
            cin >> n;
        } while (n < low || n > high);
        return n;
    }
} getData;

bool isValidTime (Time t) {
    if (t.hour < 0 || t.hour > 23) return 0;
    if (t.min < 0 || t.min > 59) return 0;
    if (t.sec < 0 || t.sec > 59) return 0;
    return 1;
}

bool isValidDate (Time t) {
    if (t.month < 1 || t.month > 12) return 0;
    if (t.day < 1) return 0;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (t.month == 2) {
        // Kiem tra nam nhuan
        bool isLeap = (t.year % 4 == 0 && t.year % 100 != 0) || (t.year % 400 == 0);
        if (isLeap) {
            if (t.day > 29) return 0;
        } else {
            if (t.day > 28) return 0;
        }
    } else {
        if (t.day > daysInMonth[t.month - 1]) return 0;
    }
    return 1;
}

void sortTime (Time& t1, Time& t2) {
    if (t1.year > t2.year) swap(t1, t2);
    else if (t1.year == t2.year) {
        if (t1.month > t2.month) swap(t1, t2);
        else if (t1.month == t2.month) {
            if (t1.day > t2.day) swap(t1, t2);
            else if (t1.day == t2.day) {
                if (t1.hour > t2.hour) swap(t1, t2);
                else if (t1.hour == t2.hour) {
                    if (t1.min > t2.min) swap(t1, t2);
                    else if (t1.min == t2.min) {
                        if (t1.sec > t2.sec) swap(t1, t2);
                    }
                }
            }
        }
    }
}

int countSec (Time t1, Time t2) {  
    sortTime(t1, t2);
    int totalSec = 0;

    // Tinh so giay trong cac nam hoan toan giua
    for (int year = t1.year + 1; year < t2.year; year++) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        totalSec += isLeap ? 366 * 86400 : 365 * 86400;
    }

    // Tinh so giay trong nam dau tien
    bool isLeapStart = (t1.year % 4 == 0 && t1.year % 100 != 0) || (t1.year % 400 == 0);
    int daysInMonthStart[] = {31, isLeapStart ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int month = t1.month + 1; month <= 12; month++) {
        totalSec += daysInMonthStart[month - 1] * 86400;
    }
    totalSec += (daysInMonthStart[t1.month - 1] - t1.day) * 86400;
    totalSec += t1.hour * 3600 + t1.min * 60 + t1.sec;

    // Tinh so giay trong nam cuoi cung
    bool isLeapEnd = (t2.year % 4 == 0 && t2.year % 100 != 0) || (t2.year % 400 == 0);
    int daysInMonthEnd[] = {31, isLeapEnd ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int month = 1; month < t2.month; month++) {
        totalSec += daysInMonthEnd[month - 1] * 86400;
    }
    totalSec += (t2.day - 1) * 86400;
    totalSec += t2.hour * 3600 + t2.min * 60 + t2.sec;

    return totalSec;
}

int countHour (Time t1, Time t2) {
    int totalSec = countSec(t1, t2);
    return totalSec / 3600;
}

void solve() {
    Time time_1, time_2;
    cout << "Nhap thoi gian thu nhat:" << endl;
    do {
        time_1.day = getData.getDay();
        time_1.month = getData.getMonth();
        time_1.year = getData.getYear();
    } while (!isValidDate(time_1));
    do {
        time_1.hour = getData.getHour();
        time_1.min = getData.getMinute();
        time_1.sec = getData.getSecond();
    } while (!isValidTime(time_1));
    nl;
    cout << "Nhap thoi gian thu hai:" << endl;
    do {
        time_2.day = getData.getDay();
        time_2.month = getData.getMonth();
        time_2.year = getData.getYear();
    } while (!isValidDate(time_2));
    do {
        time_2.hour = getData.getHour();
        time_2.min = getData.getMinute();
        time_2.sec = getData.getSecond();
    } while (!isValidTime(time_2));

    sortTime(time_1, time_2);
    cout << "So gio giua hai thoi gian la: " << countHour(time_1, time_2) << " gio." << endl;
}

int main () {
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    // JUDGE("filename");
    
    solve();
}
