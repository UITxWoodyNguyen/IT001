#include <bits/stdc++.h>
using namespace std;
#define ll long long

mt19937 rd(time(0));

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+36;
const int priceWon[] = {0,0,0,30,300,10000,12000000};

// --- hàm sinh ngẫu nhiên trong [l, r] ---
int Rand (int l, int r) { 
    assert(l <= r);
    uniform_int_distribution<int> dis(l, r);
    return dis(rd);
}

// --- hàm sắp xếp nhanh ---
void QuickSort (int a[], int n) {
    if (n <= 1) return;
    int pivot = a[n / 2];
    int i = 0, j = n - 1;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++; j--;
        }
    }
    QuickSort(a, j + 1);
    QuickSort(a + i, n - i);
}

/*
// --- hàm sinh vé số ngẫu nhiên có ít nhất 1 số trúng ---
void RandomTicket (int ticket[], int win[], int n) {
    bool used[46];
    memset(used, 0, sizeof(used));
    int cnt = 0;

    // đảm bảo có 1 số trúng
    int idx = rand() % 6;
    ticket[cnt++] = win[idx];
    used[win[idx]] = true;

    // điền các số còn lại
    while (cnt < n) {
        int num = Rand(1,45);
        if (!used[num]) {
            ticket[cnt++] = num;
            used[num] = true;
        }
    }
    QuickSort(ticket, n);
}
*/

// --- hàm lấy vé số ngẫu nhiên ---
void getTicket (int ticket[], int n) {
    bool used[46];
    memset(used, 0, sizeof(used));
    int cnt = 0;
    while (cnt < n) {
        int num = Rand(1,45);
        if (!used[num]) {
            ticket[cnt++] = num;
            used[num] = true;
        }
    }
    QuickSort(ticket, n);
}

int countMatch (int ticket[], int win[], int n) {
    int cnt = 0, i = 0, j = 0;
    while (i < n && j < n) {
        if (ticket[i] == win[j]) {
            cnt++;
            i++; j++;
        } else if (ticket[i] < win[j]) i++;
        else j++;
    }
    return cnt;
}

void printArray (int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main() {
    int n,win[6];
    cout << "Nhap 6 so ket qua trung thuong: ";
    for(int i=0; i<6; i++) cin >> win[i];
    QuickSort(win, 6);
    cout << "Nhap so lan mua ve: ";
    cin >> n;
    ll total_spend = 10 * n, total_win = 0;

    int ticket[6];
    while (n--) {
        getTicket(ticket, 6);
        int matches = countMatch(ticket, win, 6);
        total_win += priceWon[matches];
    }

    double rate = 100 * (double)total_win / (double)total_spend;
    cout << fixed << setprecision(3);
    cout << "Ti le giua so tien trung va so tien mua ve: " << rate << "%\n";

    return 0;
}
