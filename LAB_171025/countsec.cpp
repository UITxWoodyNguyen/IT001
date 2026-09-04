#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = a, _b = (b); i <= _b; ++i)
#define REP(i, a, b) for (int i = a, _b = (b); i < _b; ++i)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; --i)
#define nl cout << endl
#define endl '\n'

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }

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

bool isValidTime (Time t) {
    if (t.hour < 0 || t.hour > 23) return 0;
    if (t.min < 0 || t.min > 59) return 0;
    if (t.sec < 0 || t.sec > 59) return 0;
    return 1;
}

void sortTime (Time& t1, Time& t2) {
    if (t1.hour > t2.hour) swap(t1, t2);
    else if (t1.hour == t2.hour) {
        if (t1.min > t2.min) swap(t1, t2);
        else if (t1.min == t2.min) {
            if (t1.sec > t2.sec) swap(t1, t2);
        }
    }
}

int countSec (Time t1, Time t2) {
    int total1 = t1.hour * 3600 + t1.min * 60 + t1.sec;
    int total2 = t2.hour * 3600 + t2.min * 60 + t2.sec;
    return total2 - total1;
}

void solve() {
    Time time_1, time_2;
    do {
        cout << "Nhap thoi gian thu nhat:" << endl;
        time_1.hour = getData.getHour();
        time_1.min = getData.getMinute();
        time_1.sec = getData.getSecond();
    } while (!isValidTime(time_1));
    nl;
    do {
        cout << "Nhap thoi gian thu hai:" << endl;
        time_2.hour = getData.getHour();
        time_2.min = getData.getMinute();
        time_2.sec = getData.getSecond();
    } while (!isValidTime(time_2));

    sortTime(time_1, time_2);
    int diff = countSec(time_1, time_2);
    cout << diff << " giay" << endl;
}

int main () {
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    // JUDGE("filename");
    
    solve();
}
