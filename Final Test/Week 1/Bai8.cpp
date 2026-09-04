#include <bits/stdc++.h>
using namespace std;

typedef short int16; // so nguyen co dau 2 byte = 16 bit
typedef long int32; // so nguyen co dau 4 byte = 32 bit
typedef unsigned short uint16; // so nguyen ko dau 2 byte
typedef unsigned long uint32; // so nguyen ko dau 4 byte
typedef long long uint64; // so nguyen ko dau 8 byte

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
    cout << s << endl;
    uint32 res = BinToDec(s);
    return res;
}

int main () {
    uint16 x = 16;
    cout << BinToDec("10000") << endl;
    uint32 new_x = encodeManchester(x);
    cout << new_x;
}
