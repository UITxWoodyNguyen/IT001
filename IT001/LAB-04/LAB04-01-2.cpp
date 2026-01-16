#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+5;

/* This is the declaration of constants */
const int numDaysInMonth[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const string DayName[] = {"Thu bay", "Chu Nhat", "Thu Hai", "Thu Ba", "Thu Tu", "Thu Nam", "Thu Sau"};
/*
    0 : "Saturday",
    1 : "Sunday",
    2 : "Monday",
    3 : "Tuesday",
    4 : "Wednesday",
    5 : "Thursday",
    6 : "Friday",
*/

/* This is the definition of the Time structure */
struct Time {
    int day, month, year, dayOfWeek;
};

const Time root_time = {1, 1, 2000, 0}; // Saturday

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

/* This is end of declaration*/
/*---------------------------------------------------------*/

// Hàm kiểm tra năm nhuận
bool isLeapYear (int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Hàm kiểm tra tính hợp lệ của ngày tháng năm
bool isValidDate (int day, int month, int year) {
    if (month < 1 || month > 12) return 0;
    int daysInMonth = numDaysInMonth[month];
    if (month == 2 && isLeapYear(year)) daysInMonth++;
    return day >= 1 && day <= daysInMonth;
}

// Hàm tính số ngày giữa hai thời điểm
int countDays (Time t1, Time t2) {
    int total_days = 0;
    for(int i=t1.year; i<t2.year; i++) total_days += (isLeapYear(i) ? 366 : 365);
    for(int m=1; m<t2.month; m++) {
        total_days += numDaysInMonth[m];
        if (m == 2 && isLeapYear(t2.year)) total_days++;
    }
    total_days += t2.day;

    for(int m=1; m<t1.month; m++) {
        total_days -= numDaysInMonth[m];
        if (m == 2 && isLeapYear(t1.year)) total_days--;
    }
    total_days -= t1.day;

    return total_days;
}

// Hàm sắp xếp thời gian theo thứ tự tăng dần (t1 trước t2)
bool timeSort (Time& t1, Time& t2) {
    if (t1.year != t2.year) {
        if (t1.year > t2.year) {
            swap(t1.day, t2.day);
            swap(t1.month, t2.month);
            swap(t1.year, t2.year);
        }
    } else {
        if (t1.month != t2.month) {
            if (t1.month > t2.month) {
                swap(t1.day, t2.day);
                swap(t1.month, t2.month);
            }
        } else {
            if (t1.day > t2.day) swap(t1.day, t2.day);
        }
    }
}

// Hàm tính ngày trong tuần của một thời điểm dựa trên thời điểm gốc
int getDayOfWeek (Time root, Time t) {
    // get Day of week of a time base on root time
    int total_days = countDays(root, t);
    return (total_days % 7 + 1) % 7;
}

int main () {
    Time time_1, time_2;
    // get input
    do {
        cout << "*NHAP THOI DIEM T1*" << endl;
        time_1.day = getData.getDay();
        time_1.month = getData.getMonth();
        time_1.year = getData.getYear();
    } while (!isValidDate(time_1.day, time_1.month, time_1.year));

    cout << endl;

    do {
        cout << "*NHAP THOI DIEM T2*" << endl;
        time_2.day = getData.getDay();
        time_2.month = getData.getMonth();
        time_2.year = getData.getYear();
    } while (!isValidDate(time_2.day, time_2.month, time_2.year));

    // (a) Tinh so ngay giua T1 va T2 va in ra thu cua T1 va T2
    timeSort(time_1, time_2);
    int total_days = countDays(time_1, time_2);
    cout << "So ngay giua " << time_1.day << "/" << time_1.month << "/" << time_1.year << " va " << time_2.day << "/" << time_2.month << "/" << time_2.year << ": " << total_days << " ngay\n";

    time_1.dayOfWeek = getDayOfWeek(root_time, time_1);
    time_2.dayOfWeek = getDayOfWeek(root_time, time_2);
    if (timeSort(time_1, time_2)) swap(time_1, time_2); // dam bao 2 thoi diem khong bi doi cho
    cout << "Neu " << root_time.day << "/" << root_time.month << "/" << root_time.year << " la " << DayName[root_time.dayOfWeek] << ": " << endl;
    cout << time_1.day << "/" << time_1.month << "/" << time_1.year << " la: " << DayName[time_1.dayOfWeek] << endl;
    cout << time_2.day << "/" << time_2.month << "/" << time_2.year << " la: " << DayName[time_2.dayOfWeek] << endl;

    return 0;
}  