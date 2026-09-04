// LAB0303.cpp
#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e6+5;
bool isPrime[MAXN];

void Eratosthenes () { // if i is a prime number --> isPrime[i] = true
    for(int i=0; i < MAXN; i++) isPrime[i] = true;
    isPrime[0] = isPrime[1] = false;
    for(int i=2; i*i < MAXN; i++) {
        if(isPrime[i]) for(int j=i*i; j < MAXN; j+=i) isPrime[j] = false;
    }
}

int getSum (int n) {
    int sum = 0;
    while (n) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int NumwithLargestSum (int a[], int size) { // n = size of a
    int maxSum = -1;
    int num = -1;
    for(int i=0; i < size; i++) {
        int currSum = getSum(a[i]);
        if (currSum > maxSum) {
            maxSum = currSum;
            num = a[i];
        }
    }
    return num;
}

bool isPalindrome (int n) {
    int digits[10], cnt = 0;
    while (n) {
        digits[cnt++] = n % 10;
        n /= 10;
    }
    for (int i = 0; i < cnt / 2; i++) if (digits[i] != digits[cnt - 1 - i]) return false;
    return true;
}

int countAdjacentOddPairs(int arr[], int size) {
    int cnt = 0;
    for (int i = 0; i < size - 1; ++i) if (arr[i] % 2 != 0 && arr[i + 1] % 2 != 0 && abs(arr[i] - arr[i + 1]) == 2) cnt++;
    return cnt;
}

int countPairs(int arr[], int size, int m, int n) {
    int cnt = 0;
    for(int i=0; i < size; i++) for(int j=i+1; j < size; j++) {
        if (arr[i] + arr[j] == m + n) cnt++;
    }
    return cnt;
}

void solve () {
    int m,n;
    cin >> m >> n;
    int max_size = max(m,n) + 1;

    // (a) m and n are prime numbers ?
    if (isPrime[m]) cout << m << " is a prime number\n";
    else cout << m << " is not a prime number\n";
    if (isPrime[n]) cout << n << " is a prime number\n";
    else cout << n << " is not a prime number\n";

    // (b) List all prime numbers between m and n
    int primeList[max_size], index = 0;
    for (int i = m; i <= n; i++) if (isPrime[i]) primeList[index++] = i;
    cout << "Prime numbers between " << m << " and " << n << " are: ";
    for (int i = 0; i < index; i++) cout << primeList[i] << " ";
    cout << "\n";

    // (c) Find the prime number with the largest sum of digits
    int largestSum = NumwithLargestSum(primeList, index);
    cout << "The largest sum of digits among these prime numbers is: " << largestSum << "\n";

    // (d) Find out the palindromic prime numbers
    cout << "Palindromic prime numbers between " << m << " and " << n << " are: ";
    for (int i = 0; i < index; i++) if (isPalindrome(primeList[i])) cout << primeList[i] << " ";
    cout << "\n";

    // (e) Count adjacent odd pairs
    int oddPairCount = countAdjacentOddPairs(primeList, index);
    cout << "Number of adjacent odd pairs with a difference of 2: " << oddPairCount << "\n";

    // (f) Count pairs that sum to m + n
    int pairCount = countPairs(primeList, index, m, n);
    cout << "Number of pairs that sum to " << m + n << ": " << pairCount << "\n";
}

int main () {
    JUDGE("woody");
    Eratosthenes();
    solve();
}
