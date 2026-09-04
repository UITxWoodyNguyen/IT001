#include <bits/stdc++.h>
using namespace std;
#define ll long long

mt19937 rd(time(0));

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+36;
char letter[] = {'F', 'O', 'R', 'T', 'Y', 'E', 'N', 'S', 'I', 'X'};

int main() {
    int perm[10], d[30];
    for(int i=0; i<10; i++) perm[i] = i;

    do {
        for(int i=0; i<10; i++) d[(int)letter[i] - 'A'] = perm[i];
        if(d['F' - 'A'] == 0 || d['S' - 'A'] == 0 || d['T' - 'A'] == 0 || d['O' - 'A'] == 0) continue;

        int ten = d['T' - 'A'] * 100 + d['E' - 'A'] * 10 + d['N' - 'A'];
        int forty = d['F' - 'A'] * 10000 + d['O' - 'A'] * 1000 + d['R' - 'A'] * 100 + d['T' - 'A'] * 10 + d['Y' - 'A'];
        int sixty = d['S' - 'A'] * 10000 + d['I' - 'A'] * 1000 + d['X' - 'A'] * 100 + d['T' - 'A'] * 10 + d['Y' - 'A'];

        if (ten + ten + forty == sixty) {
            for(int i=0; i<10; i++) {
                cout << letter[i] << " " << perm[i] << endl;
            }

            cout << "TEN = " << ten << endl;
            cout << "FORTY = " << forty << endl;
            cout << "SIXTY = " << sixty << endl;

            int one = d['O' - 'A'] * 100 + d['N' - 'A'] * 10 + d['E' - 'A'];
            int six = d['S' - 'A'] * 100 + d['I' - 'A'] * 10 + d['X' - 'A'];
            cout << "ONE = " << one << endl;
            cout << "SIX = " << six << endl;
            break;
        }
    } while(next_permutation(perm, perm + 10));

    return 0;
}