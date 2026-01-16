#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = a, _b = (b); i <= _b; ++i)
#define REP(i, a, b) for (int i = a, _b = (b); i < _b; ++i)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; --i)
#define nl cout << endl
#define endl '\n'

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }

const int numDaysInMonth[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct input {
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

bool isLeapYear (int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate (int day, int month, int year) {
    if (month < 1 || month > 12) return 0;
    int daysInMonth = numDaysInMonth[month];
    if (month == 2 && isLeapYear(year)) daysInMonth++;
    return day >= 1 && day <= daysInMonth;
}

int countDays (int day_1, int month_1, int year_1, int day_2, int month_2, int year_2) {
    int total_days = 0;
    FOR(i, year_1, year_2 - 1) total_days += (isLeapYear(i) ? 366 : 365);
    FOR(m, 1, month_2 - 1) {
        total_days += numDaysInMonth[m];
        if (m == 2 && isLeapYear(year_2)) total_days++;
    }
    total_days += day_2;

    FOR(m, 1, month_1 - 1) {
        total_days -= numDaysInMonth[m];
        if (m == 2 && isLeapYear(year_1)) total_days--;
    }
    total_days -= day_1;

    return total_days;
}

void timeSort (int& day_1, int& month_1, int& year_1, int& day_2, int& month_2, int& year_2) {
    if (year_1 != year_2) {
        if (year_1 > year_2) {
            swap(day_1, day_2);
            swap(month_1, month_2);
            swap(year_1, year_2);
        }
    } else {
        if (month_1 != month_2) {
            if (month_1 > month_2) {
                swap(day_1, day_2);
                swap(month_1, month_2);
            }
        } else {
            if (day_1 > day_2) swap(day_1, day_2);
        }
    }
}

void solve() {
    // input
    int day_1, month_1, year_1;
    do {
        cout << "*NHAP THOI DIEM T1*" << endl;
        day_1 = getData.getDay();
        month_1 = getData.getMonth();
        year_1 = getData.getYear();
    } while (!isValidDate(day_1, month_1, year_1));

    nl;

    int day_2, month_2, year_2;
    do {
        cout << "*NHAP THOI DIEM T2*" << endl;
        day_2 = getData.getDay();
        month_2 = getData.getMonth();
        year_2 = getData.getYear();
    } while (!isValidDate(day_2, month_2, year_2));

    // sort time
    timeSort(day_1, month_1, year_1, day_2, month_2, year_2);
    // cerr << day_1 << "/" << month_1 << "/" << year_1 << " - " << day_2 << "/" << month_2 << "/" << year_2 << endl;
    
    // process
    int total_days = countDays(day_1, month_1, year_1, day_2, month_2, year_2);
    cout << "So ngay giua hai thoi diem la: " << total_days << " ngay." << endl;
}

int main () {
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    // JUDGE("filename");
    
    solve();
}
