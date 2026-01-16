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

/* This is the definition of the getCurrentTime function */
Time getCurrentTime() {
    time_t now = time(nullptr);       // get current time
    tm *ltm = localtime(&now);        // convert to local time

    Time currentTime;
    currentTime.day = ltm->tm_mday;
    currentTime.month = ltm->tm_mon + 1;                // months since January (0–11)
    currentTime.year = ltm->tm_year + 1900;             // years since 1900

    return currentTime;
}
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

// Hàm tính ngày trong tuần của một thời điểm dựa trên thuật toán Zeller's Congruence
int getDate (Time t) {
    // Zeller's Congruence Algorithm
    int d = t.day;
    int m = t.month;
    int y = t.year;

    if (m < 3) {
        m += 12;
        y--;
    }

    int K = y % 100;      // year of the century
    int J = y / 100;      // zero-based century

    int h = (d + (13 * (m + 1)) / 5 + K + K/4 + J/4 + 5*J) % 7;
    return h;
}

int main () {
    Time root_time, time_2;
    root_time = getCurrentTime();
    do {
        cout << "*NHAP THOI DIEM T2*" << endl;
        time_2.day = getData.getDay();
        time_2.month = getData.getMonth();
        time_2.year = getData.getYear();
    } while (!isValidDate(time_2.day, time_2.month, time_2.year));

    int root_day = getDate(root_time);
    int find_day = getDayOfWeek(root_time, time_2);
    cout << "Neu " << root_time.day << "/" << root_time.month << "/" << root_time.year << " la " << DayName[root_day] << ", thi "
         << time_2.day << "/" << time_2.month << "/" << time_2.year << " la " << DayName[find_day] << "." << endl;

    return 0;
} 