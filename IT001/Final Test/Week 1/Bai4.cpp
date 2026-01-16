#include <bits/stdc++.h>
using namespace std;

typedef short int16; // so nguyen co dau 2 byte = 16 bit
typedef long int32; // so nguyen co dau 4 byte = 32 bit
typedef unsigned short uint16; // so nguyen ko dau 2 byte
typedef unsigned long uint32; // so nguyen ko dau 4 byte
typedef long long uint64; // so nguyen ko dau 8 byte

typedef struct {
    int type; // = 0/1 (kieu so nguyen khong/co dau; = 2/3 int16/uint1; 4/5 = int32/uint32
    int mode; // gia tri xuat hien nhieu nhat
    int avr; // gia tri trung binh
    int dr; // ty le % lech chuan
    int n; // so phan tu
} FEATURE;

const int MAXN = 32768;

FEATURE Cau_4 (short Arr[], int n) {
    FEATURE ans;
    ans.n = n;

    int sum = 0;
    for(int i = 0; i < n; i++) sum += Arr[i];
    double average = (double)(sum / n);
    ans.avr = (int)average;

    int freq[MAXN][2]; // freq[i][0] dem i, freq[i][1] dem -i
    for(int i = 0; i < n; i++) {
        int type = (Arr[i] >= 0) ? 0 : 1;
        freq[abs(Arr[i])][type]++;
    }

    int maxFreq = 0, numMost = 0, numType = 0; // so lan xuat hien - so tuong ung - dau cua so do
    for(int type = 0; type < 2; type++) {
        for(int i = 0; i < n; i++) {
            int curFreq = freq[abs(Arr[i])][type];
            if (curFreq > maxFreq) {
                maxFreq = curFreq;
                numMost = abs(Arr[i]);
                numType = type;
            }
        }
    }
    ans.mode = (numType == 0) ? numMost : -numMost;

    double DiffTarget = average / 4.0;
    double cnt = 0;
    for(int i = 0; i < n; i++) {
        double curDiff = abs(Arr[i] - average);
        if (curDiff > DiffTarget) cnt++;
    }
    double rateDist = (double)(cnt / n) * 100.0;
    ans.dr = (int)rateDist;
    return ans;
}

void print (FEATURE u) {
    cout << u.mode << " " << u.avr << " " <<  u.dr << " " << u.n << endl;
}

int main () {
    short Arr[6] = {-2, -2, 3, 5, 7, 9};
    int n = 6;
    FEATURE ans = Cau_4(Arr,n);
    print(ans);
}
