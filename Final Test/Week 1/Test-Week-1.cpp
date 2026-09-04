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

typedef struct {
    char name[15]; // ten chan IC
    char type[10];
    int number; // stt chan
} PIN;

// Cau 1
bool is_prime (int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    int limit = sqrt(n);
    int i = 3;
    do {
        if (n % i == 0) return false;
        i += 2;
    } while (i + 2 <= limit);
    return true;
}

int count_prime (int a[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++)
        if (is_prime(a[i])) count++;
    return count;
}

// Cau 2
double pow10 (int m) {
    double res = 1.0;
    if (m == 0) return 1.0;
    if (m > 0) {
        for(int i = 0; i < m; i++) res *= 10.0;
    } else {
        m = -m;
        for(int i = 0; i < m; i++) res /= 10.0;
    }

    return res;
}

double Cau_2 (double F, int m, int huong = 0) {
    double targetRounding = pow10(-m);
    double shifted = F * targetRounding;

    long long nguyen = (long long)shifted;
    double thap_phan = shifted - nguyen;

    bool ok = (shifted >= 0 ? true : false); // F duong ok = 1, am ok = 0
    long long temp;

    if (huong == 0) {
        if (ok) temp = (long long)(shifted + 0.5);
        else temp = (long long)(shifted - 0.5);
    } else if (huong < 0) {
        if (thap_phan == 0) temp = nguyen;
        else temp = ok ? nguyen : nguyen - 1;
    } else {
        if (thap_phan == 0) temp == nguyen;
        else temp = ok ? nguyen + 1 : nguyen;
    }

    return (double)temp / targetRounding;
}

// Cau 3
const double MAX_VALUE = 65535.0; // = 2^16 - 1

void Cau_3 (double inArr[], uint16 outArr[], int n) {
    double minVal = inArr[0], maxVal = inArr[0];
    for(int i = 0; i < n; i++) {
        double value = inArr[i];
        if (value < minVal) minVal = value;
        if (value > maxVal) maxVal = value;
    }

    double range = maxVal - minVal; // [a;b]
    for(int i = 0; i < n; i++) {
        if (range == 0) outArr[i] = 0;
        else {
            double current = ((inArr[i] - minVal) / range) * MAX_VALUE;
            outArr[i] = round(current);
        }
    }
}

void printArray (uint16 a[], int n) {
    for(int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}

// Cau 4
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

// Cau 7
int getMax (int a[], int n) {
    if (n == 1) return a[0];
    return max(getMax(a, n-1), a[n-1]);
}

int getSum (int a[], int n) {
    if (n == 1) return a[0];
    return getSum(a, n-1) + a[n-1];
}

// Cau 8
#define BIT(mask,i) ((mask >> i) & 1)

uint32 BinToDec (char s[]) {
    int n = strlen(s);
    uint32 res = 0;
    for(int i = 0; i < n; i++) {
        if (s[n - 1 - i] == '1') {
            res += pow(2, i);
        }
    }

    return res;
}

void addChar(char str[], char c) {
    int len = strlen(str);

    str[len] = c;
    str[len + 1] = '\0';
}

uint32 encodeManchester (uint16 X) {
    char s[100] = {0};

    int pos = 0;
    for(int i = 15; i >= 0; i--) {
        if (BIT(X,i)==1) {
            pos = i;
            break;
        }
    }

    for(int i = pos; i >= 0; i--) {
        int curBit = BIT(X, i);
        if (curBit == 0) {
            addChar(s,'0');
            addChar(s, '1');
        } else {
            addChar(s, '1');
            addChar(s,'0');
        }
    }
    uint32 res = BinToDec(s);
    return res;
}

void Bai_1 () {
    int num = 5;
    int a[6] = {5,7,9,11,13};
    int n = 6;
    cout << is_prime(num) << endl;
    cout << count_prime(a,n) << endl;
}

void Bai_2 () {
    double F = 123.4655;
    int m = -2;
    cout << fixed << setprecision(abs(m)) << Cau_2(F,m,-1);
}

void Bai_3 () {
    double inArr[5] = {66.9, 77.25, 88.88848, 89.5, 10000.24};
    int n = 5;
    uint16 out[100005];
    Cau_3(inArr, out, 5);
    printArray(out, 5);
}

void Bai_4 () {
    short Arr[6] = {-2, -2, 3, 5, 7, 9};
    int n = 6;
    FEATURE ans = Cau_4(Arr,n);
    print(ans);
}

void Bai_7() {
    int a[] = {2,3,4,5};
    int n = 4;
    cout << getMax(a,n) << ' ' << getSum(a,n) << endl;
}

void Bai_8() {
    uint16 x = 16;
    uint32 new_x = encodeManchester(x);
    cout << new_x;
}

void RunOption (int n) {
    if (n==1) Bai_1();
    if (n==2) Bai_2();
    if (n==3) Bai_3();
    if (n==4) Bai_4();
    if (n==7) Bai_7();
    if (n==8) Bai_8();
}

int main() {
    cout << "List option: 1, 2, 3, 4, 7, 8" << endl;
    int option;
    cin >> option;
    RunOption(option);
}
