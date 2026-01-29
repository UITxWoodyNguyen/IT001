/*
                        _
                       ooOoo
                      o8888888o
                      88" . "88
                      (| 😑 |)
                      O\  =  /O
                   __/`---'\__
                 .'  \\|     |//  `.
                /  \\|||  :  |||//  \
               /  ||||| -:- |||||  \
               |   | \\\  -  /'| |   |
               | \_|  `\`---'//  |_/ |
               \  .-\__ `-. -'__/-.  /
             _. .'  /--.--\  . .'_
          ."" '<  `.___\_<|>_/___.' _> \"".
         | | :  - \. ;`. _/; .'/ /  .' ; |
         \  \ -.   \_\_. _.'_/_/  -' _.' /
===========`-.`___`-.__\ \___  /__.-'.'.-'================

  █▀▀ █ █ █▀█   █▀▀ █▀▄▀█   █▀█ █ █ ▄▀█   █▀▄▀█ █▀█ █▄ █
  █▄▄ █▀█ █▄█   ██▄ █ ▀ █   ▀▀█ █▄█ █▀█   █ ▀ █ █▄█ █ ▀█

*/

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 0;

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

}