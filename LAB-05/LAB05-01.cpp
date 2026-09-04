#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define nl cout << endl

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+36;
const int SIZE = 105;
typedef int matrix[SIZE][SIZE];
typedef matrix array[SIZE][SIZE];

struct Point {
    int x, y, value;
};

bool checkMagicSquare (int a[][SIZE], int n) {
    int targetSum = 0;
    for(int i = 0; i < n; i++) targetSum += a[0][i];
     
    // Check rows
    for(int i = 1; i < n; i++) {
        int rowSum = 0;
        for(int j = 0; j < n; j++) rowSum += a[i][j];
        if(rowSum != targetSum) return false;
    }

    // Check columns
    for(int j = 0; j < n; j++) {
        int colSum = 0;
        for(int i = 0; i < n; i++) colSum += a[i][j];
        if(colSum != targetSum) return false;
    }

    // Check main diagonal
    int mainDiagonalSum = 0;
    for(int i = 0; i < n; i++) mainDiagonalSum += a[i][i];
    if(mainDiagonalSum != targetSum) return false;

    // Check secondary diagonal
    int secondaryDiagonalSum = 0;
    for(int i = 0; i < n; i++) secondaryDiagonalSum += a[i][n - 1 - i];
    if(secondaryDiagonalSum != targetSum) return false;

    return true;
}

void createMagicSquare (int a[][SIZE], int n) {
    memset(a, 0, sizeof(int) * SIZE * SIZE);
    int i = 0, j = n / 2;
    for(int num = 1; num <= n * n; ) {
        a[i][j] = num++;
        int newi = (i - 1 + n) % n; 
        int newj = (j + 1) % n;
        if(a[newi][newj] != 0) {
            i = (i + 1) % n;
        } else {
            i = newi;
            j = newj;
        }
    }
}

void listSaddlePoint (Point saddle[], int a[][SIZE], int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int current = a[i][j];
            bool isSaddle = true;

            // Check row
            for(int col = 0; col < n; col++) {
                if(a[i][col] < current) {
                    isSaddle = false;
                    break;
                }
            }
            if(!isSaddle) continue;

            // Check column
            for(int row = 0; row < n; row++) {
                if(a[row][j] > current) {
                    isSaddle = false;
                    break;
                }
            }

            if(isSaddle) saddle[count++] = {i,j,current};
        }
    }
    saddle[count] = {-1,-1,-1}; // Mark the end of the list
}

void createRandomMatrix (int a[][SIZE], int row_size, int col_size) {
    int minVal = 1, maxVal = row_size * col_size;
    for(int i = 0; i < row_size; i++) {
        for(int j = 0; j < col_size; j++) {
            a[i][j] = rand() % (maxVal - minVal + 1) + minVal;
        }
    }
}

void rotateMatrix (int a[][SIZE], int m, int n, int angle) {
    int temp[SIZE][SIZE];
    int times = (angle / 90) % 4;

    if (times & 1) { // matrix m*n become n*m
        swap(m,n);
        if (times == 1) {
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) temp[i][j] = a[n-1-j][i];
            }
        } else if (times == 3) {
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) temp[i][j] = a[j][m-1-i];
            }
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) a[i][j] = temp[i][j];
        }
    } else {
        if (times == 2) {
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) temp[i][j] = a[m-1-i][n-1-j];
            }
        } else {
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) temp[i][j] = a[i][j];
            }
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) a[i][j] = temp[i][j];
        }
    }
}

void printMatrix (int a[][SIZE], int row_size, int col_size) {
    for(int i = 0; i < row_size; i++) {
        for(int j = 0; j < col_size; j++) {
            cout << a[i][j] << " ";
        }
        nl;
    }
}

void copyMatrix (int dest[][SIZE], int src[][SIZE], int row_size, int col_size) {
    for(int i = 0; i < row_size; i++) {
        for(int j = 0; j < col_size; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    JUDGE("woody");

    int n = 2;
    /*Câu 1*/
    matrix magicSquare;
    createMagicSquare(magicSquare, 2*n+1);
    cout << "Magic Square of size " << 2*n+1 << " :" << endl;
    printMatrix(magicSquare, 2*n+1, 2*n+1);
    // cout << (checkMagicSquare(magicSquare, 2*n+1) ? "YES" : "NO") << endl;

    cout << endl;
    /*Câu 2*/
    Point listSaddle[SIZE * SIZE];
    matrix a;
    int rowSize = n, colSize = n+4;
    createRandomMatrix(a, rowSize, colSize);
    printMatrix(a, rowSize, colSize);
    listSaddlePoint(listSaddle, a, n);
    for(int i = 0; listSaddle[i].x != -1; i++) cout << "Saddle Point at (" << listSaddle[i].x << ", " << listSaddle[i].y << ") with value " << listSaddle[i].value << endl;
    
    cout << endl;
    /*Câu 3*/
    matrix b;
    copyMatrix(b, a, rowSize, colSize);
    for(int k = 1; k <= 4; k++) {
        cout << "Rotate matrix by " << k*90 << " degrees:" << endl;
        int angle = k * 90;
        int cur_rowSize = rowSize;
        int cur_colSize = colSize;
        
        rotateMatrix(b, cur_rowSize, cur_colSize, angle);
        if (k & 1) swap(cur_rowSize, cur_colSize);
        printMatrix(b, cur_rowSize, cur_colSize);

        // reset memory
        copyMatrix(b, a, rowSize, colSize);
        cur_rowSize = rowSize;
        cur_colSize = colSize;
    }
}