#include <bits/stdc++.h>

using namespace std;

#define ll long long

int st = 1, en = 20;
mt19937 rd(time(0));

ll rng(ll l, ll r){
    assert(l <= r);
    uniform_int_distribution<ll> dis(l, r);
    return dis(rd);
}

void gen0 (string id) {
    ofstream cout((id + ".inp").c_str());
    ll n = rng(1,1e3);
    cout << n << endl;
    for(int i=1; i<=n; i++) {
        cout << 9999 % 7777 << " ";
    }
}

void gen_spec (string id) {
    ofstream cout((id + ".inp").c_str());
    int n = rng(1,10);
    for(int i=1; i<=n; i++) {
        int tmp = rng(97,122);
        cout << char(tmp);
    }
}

void gen(string id){
    ofstream cout((id + ".inp").c_str());
    
}

int main(){
    srand(time(0));
    for(int i = st; i <= en; i++){
        string id = to_string(i);
        if(i < 10) id = '0' + id;
        // if (i <= 2) gen_spec(id);
        // else if (i % 10 == 9) gen0(id);
        gen(id);
       // gen(id);
        system(("copy " + id + ".inp main.inp").c_str());
        system("main.exe < main.inp > main.out");
    }
}
