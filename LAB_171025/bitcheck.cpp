#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = a, _b = (b); i <= _b; ++i)
#define REP(i, a, b) for (int i = a, _b = (b); i < _b; ++i)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; --i)
#define nl cout << endl
#define endl '\n'
#define MASK(n) (1 << (n))
#define BIT(x,i) (((x) >> (i)) & 1)
#define SETBIT(x,i) (x | MASK(i))
#define LOWBIT(x) (x & (-x))
#define cntbit(x) __builtin_popcountll(x)
#define cntbit0(x) __builtin_ctzll(x)

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }

int getBit (unsigned long long& mask, int k) {
    return BIT(mask,k);
}

int OnBit (unsigned long long mask, int k) {
    return mask | (1 << k);
}

int OffBit (unsigned long long mask, int k) {
    return mask & (~(1 << k));
}

int cntBit (unsigned long long n) {
    return __builtin_popcountll(n);
}

int swap_bit (unsigned long long& mask, int k, int l) {
    int set_k = BIT(mask,l);
    int set_l = BIT(mask,k);
    if (set_k != set_l) {
        mask ^= (1 << k);
        mask ^= (1 << l);
    }
    return mask;
}


void printBinary(int n) {
    bitset<8> binary(n);
    cout << binary << endl;
}

void solve (void) {
    unsigned long long n;
    int k,l;
    cin >> n >> k >> l;
    int getbit = getBit(n,k);
    int On = OnBit(n,k);
    int Off = OffBit(n,k);
    int countBit = cntBit(n);
    int new_num = swap_bit(n,k,l);
    cout << getbit << " " << On << " " << Off << " " << countBit << " " << new_num;
    nl;
    // check
    printBinary(On);
    printBinary(Off);
    printBinary(new_num);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    JUDGE("woody");

    solve();

}
