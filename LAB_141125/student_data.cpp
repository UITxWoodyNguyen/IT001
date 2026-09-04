#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define nl cout << endl

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+36;

struct Date {
    int day, month, year;
};

struct student {
    int student_id;
    char name[55];
    Date date_of_birth;
    char first_letter;

    bool cmp (const student &other) const { return student_id < other.student_id; }
};
student info[MAXN];
int numStudents; 

bool is_number(const char *s) {
    if (!s || !*s) return false;
    int i = 0;
    if (s[0] == '+' || s[0] == '-') i = 1;
    for (; s[i]; ++i) if (!isdigit((unsigned char)s[i])) return false;
    return true;
}

void getData (char name[], ll buff, int &year) { 
    name[0] = '\0';
    year = 0;
    char token[50];
    while (cin >> token) {
        if (is_number(token)) {
            year = atoi(token); //  gán năm sinh
            break;
        } else {
            if (name[0] != '\0') {
                // thêm dấu cách nếu đã có phần trước đó
                strncat(name, " ", buff - strlen(name) - 1); 
            }
            strncat(name, token, buff - strlen(name) - 1); 
        }
    }
}

void printDayOfBirth (const student &s) {
    cout << s.date_of_birth.day << "/" << s.date_of_birth.month << "/" << s.date_of_birth.year << "\n";
}

void input () {
    cin >> numStudents;
    for (int i = 0; i < numStudents; i++) {
        cin >> info[i].student_id;
        getData(info[i].name, sizeof(info[i].name), info[i].date_of_birth.day);
        cin >> info[i].date_of_birth.month >> info[i].date_of_birth.year;
    }
}

int FindStudentById (int index) {
    int pos = -1;
    for(int i=0; i < numStudents; i++) if (info[i].student_id == index) {
        pos = i;
        break;
    }
    return pos;
}

bool editData (int student_id, Date new_day) {
    if (FindStudentById(student_id)==-1) return 0;
    int pos = FindStudentById(student_id);
    info[pos].date_of_birth.day = new_day.day;
    info[pos].date_of_birth.month = new_day.month;
    info[pos].date_of_birth.year = new_day.year;
    return 1;
}

int findtheOldestStudent (student info[], int numStudents) {
    int idx = 0;
    for (int i = 1; i < numStudents; i++) {
        if ( (info[i].date_of_birth.year < info[idx].date_of_birth.year) ||
             (info[i].date_of_birth.year == info[idx].date_of_birth.year && info[i].date_of_birth.month < info[idx].date_of_birth.month) ||
             (info[i].date_of_birth.year == info[idx].date_of_birth.year && info[i].date_of_birth.month == info[idx].date_of_birth.month && info[i].date_of_birth.day < info[idx].date_of_birth.day) ) {
            idx = i;
        }
    }
    return idx;
}

int FindTheSecondSpace (const char *s) {
    int length = strlen(s);
    for (int i = length-1; s[i] != '\0'; i--) if (s[i] == ' ') return i;
    return -1; // Trả về -1 nếu không tìm thấy hai dấu cách
}

void FindFirstLetter (student info[]) {
    for(int i=0; i < numStudents; i++) {
        int pos = FindTheSecondSpace(info[i].name) + 1;
        char fir = info[i].name[pos];
        info[i].first_letter = fir;
    }
}

void FindStudentsByInitial (student info[], char initial) {
    for(int i=0; i < numStudents; i++) {
        char first_let = info[i].first_letter;
        if (first_let == initial) printStudentData(i);
    }
}

void printStudentData(int i) {
    cout << "- ";
    cout << info[i].student_id << " " << info[i].name << " ";
    printDayOfBirth(info[i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    JUDGE("woody");

    input();
    /* (a) Liet ke danh sach sinh vien */
    cout << "Danh sach cac sinh vien:" << endl;
    for(int i=0; i < numStudents; i++) printStudentData(i);
    nl;
    
    /* (b) Sua ngay sinh cua sinh vien co ma X */
    int X;
    Date new_day;
    cin >> X >> new_day.day >> new_day.month >> new_day.year;
    editData(X, new_day);
    cout << "Danh sach cac sinh vien sau khi chinh sua:" << endl;
    for(int i=0; i < numStudents; i++) printStudentData(i);
    nl;

    /* (c) Tim sinh vien gia nhat */
    int oldestIndex = findtheOldestStudent(info, numStudents);
    cout << "Sinh vien gia nhat la: " << endl;
    printStudentData(oldestIndex);
    nl;

    /*(d) Liet ke SV co ten bat dau bang ki tu X*/
    char initial; 
    cin >> initial;
    FindFirstLetter(info);
    cout << "Cac sinh vien co ten bat dau bang ki tu " << initial << ":" << endl;
    FindStudentsByInitial(info, initial);
    nl;

    /* (e) Sap xep theo thu tu MSSV*/
    sort(info, info + numStudents, [](const student &a, const student &b) {
        return a.cmp(b);
    });
    cout << "Danh sach cac sinh vien sau khi sap xep:" << endl;
    for(int i=0; i < numStudents; i++) printStudentData(i);;
    nl;
}
