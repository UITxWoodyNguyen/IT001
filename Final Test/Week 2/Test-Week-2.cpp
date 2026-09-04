#include <bits/stdc++.h>
using namespace std;

typedef unsigned char uint8;
typedef short int16; // so nguyen co dau 2 byte = 16 bit
typedef long int32; // so nguyen co dau 4 byte = 32 bit
typedef unsigned short uint16; // so nguyen ko dau 2 byte
typedef unsigned long uint32; // so nguyen ko dau 4 byte
typedef long long uint64; // so nguyen ko dau 8 byte

typedef  struct {
   uint8  day;
   uint8  month;
   int16  year;
} DATE ;
typedef  struct {
   char  name [15]; //  tên của chân IC (“VCC” / “GND” / “I01” /…
   char  type [10]; //  Input / Output / Power
   int  number; //  số thứ tự chân
} PIN ;

// CAU 1
bool is_prime(int n) {
    if (n <= 1) return false;  // Số <= 1 không phải số nguyên tố
    if (n == 2 || n == 3) return true;  // 2 và 3 là số nguyên tố
    if (n % 2 == 0 || n % 3 == 0) return false; // Loại bỏ các số chia hết cho 2 & 3

    int limit = sqrt(n);
    // Bắt đầu kiểm tra từ 5 và bỏ qua các số chẵn
    for (int i = 5; i <= limit; i += 2)
        if (n % i == 0) return false;
    return true;
}

int count_prime(int a[ ], int n) {
    int count = 0;
    int i = 0;
    while (i < n) {
        while (is_prime(a[i])) {
            count++;
            break;
        }
        i++;
    }
    return count;

}

void b1() {
    cout << "--- CAU 1 ---" << endl;
    int a[5] = {1,2,3,4,5};
    cout << "Cac phan tu trong mang a la: ";
    for(int i = 0; i < 5; i++) cout << a[i] << ' ';
    cout << endl;
    cout << "So luong snt trong mang a la: " << count_prime(a,5) << endl;
    cout << endl;
}

// CAU 2
double pow10 (int m) { // ham tinh 10^m
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

int Cau_2 (int N, int m, int huong = 0) {
    double targetRounding = pow10(-m);
    double shifted = (double)N * targetRounding; // giu lai m chu so dau tien --> *10^-m

    long long nguyen = (long long)shifted;
    double thap_phan = shifted - nguyen;

    bool ok = (shifted >= 0 ? true : false); // F duong ok = 1, am ok = 0
    long long temp; // gia tri tam de thuc hien lam tron

    if (huong == 0) { // lam tron dung
        if (ok) temp = (long long)(shifted + 0.5);
        else temp = (long long)(shifted - 0.5);
    } else if (huong < 0) { // lam tron xuong
        if (thap_phan == 0) temp = nguyen;
        else temp = ok ? nguyen : nguyen - 1;
    } else { // lam tron len
        if (thap_phan == 0) temp == nguyen;
        else temp = ok ? nguyen + 1 : nguyen;
    }

    return temp / targetRounding;
}

void b2() {
    cout << "--- CAU 2 ---" << endl;
    int n = 1234;
    int m = 2; // so sau khi lam tron dung den 10^2 la 1230 --> lam tron len la 1300
    int huong = 1; // lam tron len
    cout << "n = " << n << ", m = " << m << ", huong = " << huong << endl;
    cout << "So sau khi lam tron: "<< Cau_2(n, m, huong) << endl;
    cout << endl;
}

// CAU 3
int collatz_length(long n, long & t) {
    int cntElement = 1;
    // cout << n << " "; --> check the sequence
    t++;
    while (n != 1) {
        cntElement++;
        t++;
        if (n % 2 == 1) n = 3*n + 1;
        else n /= 2;
        // cout << n << " "; --> check the sequence
    }

    return cntElement;
}

void b3() {
    cout << "--- CAU 3 ---" << endl;
    long n = 6, t;
    int res = collatz_length(n,t);

    cout << "So phan tu cua day la: " << res << endl;
    cout << "Thoi gian chay la: " << t*1000 << " ms" << endl;
    cout << endl;
}

// CAU 10
void Cau_10 (double inp[], int out[], int n) {
    double sum = 0.0;
    for(int i = 0; i < n; i++) sum += inp[i];
    double average = sum / n;
    for(int i = 0; i < n; i++) {
        inp[i] = round((inp[i] - average) * 100.0) / 100.0;
        out[i] = inp[i] * 100;
    }
}

void b10 () {
    cout << "--- CAU 10 ---" << endl;
    double a[5] = {1.2, 2.3, 3.4, 4.5, 5.6};
    int res[100];
    Cau_10(a, res, 5);
    cout << "Mang sau khi bien doi la: " << endl;
    for(int i = 0; i < 5; i++) cout << res[i] << " ";
}

// CAU 9
bool compare (DATE u, DATE v) {
    return ((u.year < v.year) || (u.year == v.year && u.month < v.month) || (u.year == v.year && u.month == v.month && u.day < v.day));
}

// CAU 5
void AddChar (char* s, char added) { // Them ki tu added vao cuoi xau s
    int N = strlen(s);
    s[N] = added;
    s[N + 1] = '\0';
}

void decode (char* s, char* result) {
    int n = strlen(s);

    for (int i = 0; i < n; i++) {
        char ch = s[i];
        int cnt = 0;

        // Đọc các chữ số phía sau (nếu có)
        while (i + 1 < n && isdigit(s[i + 1])) {
            cnt = cnt * 10 + (s[i + 1] - '0');
            i++;
        }

        // Nếu không có số nào thì mặc định lặp 1 lần
        if (cnt == 0) cnt = 1;

        for(int i = 0; i < cnt; i++) AddChar(result, ch);
    }
}

void b5() {
    cout << "--- CAU 5 ---" << endl;
    char s[] = "HA2HA10";
    char res[100] = "";
    decode(s, res);
    puts(res);
    cout << endl;
}

int main () {
    b1();
    b2();
    b3();
    b5();
    b10();
}