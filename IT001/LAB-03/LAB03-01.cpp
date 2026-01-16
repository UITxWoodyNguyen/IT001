// LAB0301.cpp
#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const string TypeOfTriangle[] = {"thuong", "vuong", "can", "deu", "vuong can", "vuong nua deu"}; // = [0...5]
const double cos60 = 0.5;

bool isTriangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

double getMax(double a, double b, double c) {
    double maxVal = a;
    if (b > maxVal) maxVal = b;
    if (c > maxVal) maxVal = c;
    return maxVal;
}

bool checkRightAngledHalfEquilateral(double a, double b, double c) {
    double maxSide = getMax(a, b, c);
    if (maxSide == a) return (b/a == cos60 || c/a == cos60);
    else if (maxSide == b) return (a/b == cos60 || c/b == cos60);
    else return (a/c == cos60 || b/c == cos60);
}

string getTriangleType(double a, double b, double c) {
    bool isEquilateral = (a == b) && (b == c); // Deu
    bool isRightAngled = (a * a + b * b == c * c) || (a * a + c * c == b * b) || (b * b + c * c == a * a); // Vuong
    bool isIsosceles = (a == b) || (b == c) || (a == c); // Can

    if (isEquilateral) return TypeOfTriangle[3]; // Deu
    if (isRightAngled && isIsosceles) return TypeOfTriangle[4]; // Vuong Can
    if (isIsosceles) return TypeOfTriangle[2]; // Can
    if (isRightAngled) {
        if (checkRightAngledHalfEquilateral(a, b, c)) return TypeOfTriangle[5]; // Vuong nua deu
        return TypeOfTriangle[1]; // Vuong
    }
    return TypeOfTriangle[0]; // Thuong
}

void solve () {
    double a,b,c;
    cin >> a >> b >> c;
    if (isTriangle(a,b,c)) cout << "Day la tam giac " << getTriangleType(a,b,c);
    else cout << "Khong phai tam giac";
}

int main () {
    JUDGE("woody");
    solve();
}
