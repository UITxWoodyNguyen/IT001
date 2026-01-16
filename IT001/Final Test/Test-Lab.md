# IT001 Review

## Kiểu dữ liệu và phép toán

### Kiểu dữ liệu

- Kiểu dữ liệu số nguyên:
    | Kiểu dữ liệu | Kích thước lưu trữ (bytes) | Miền giá trị (value range) | define - `<(u)int> + <num_bit>` |
    | :---: | :---: | :---: | :---: |
    | `short` | 2 | `[-32.768, 32.767]` | `int16` |
    | `unsigned short` | 2 | `[0, 65.535]` | `uint16` |
    | `int` | 4 | `[-2.147.483.648, 2.147.483.647]` | `int/int32` |
    | `unsigned` | 4 | `[0, 4.294.967.295]` | `uint32` |
    | `long` | 4 | `[-2.147.483.648, 2.147.483.647]` | `int32` |
    | `unsigned long` | 4 | `[0, 4.294.967.295]` | `uint32` |
    | `long long` | 8 | `[-9.223.372.036.854.775.807, 9.223.372.036.854.775.807]` | `int64` |
    | `unsigned long long` | 8 | `[0, 18.446.744.073.709.551.615]` | `uint64` |

- Kiểu dữ liệu số thực:
    | Kiểu dữ liệu | Kích thước lưu trữ (bytes) | Miền giá trị (value range) | Precision |
    | :---: | :---: | :---: | :---: |
    | `float` | 4 | `[1.2e-38, 3.4e+38]` | 6 chữ số |
    | `double` | 8 | `[2.3e-308, 1.7e+308]` | 15 chữ số |
    | `long double` | 12 | `[3.4e-4932, 1.1e+4932]` | 19 chữ số |

- Phép toán (Bitwise Template):
    ```c++
    #define MASK(n) (1 << (n)) // 2^n
    #define BIT(x,i) (((x) >> (i)) & 1) // BIT thu i cua x
    #define N_BIT(x,i,n) (((x) >> (i)) & (MASK(n) - 1)) // Lay N bit lien tiep tu bit thu i

    template<class T> T OnBit (T s, int i) { return s | (T(1) << i); }
    template<class T> T OffBit (T s, int i) { return s & (~(T(1) << i));}
    template<class T> T TurrnBit (T s, int i) { return s ^ (1 << i); }
    ```

- Một số hàm với BIT:
    ```c++
    #define u8  uint8_t
    #define u16 uint16_t
    #define u32 uint32_t
    #define uint uint64_t

    /*HÀM BIT CƠ BẢN CHO 1 SỐ DUY NHẤT*/

    // --- Lấy giá trị bit thứ K của N ---
    bool get_bit (uint N, int K) {
        return (N >> K) & 1;
    }

    // --- Xuất tất cả các bit của N ---
    void out_bit (uint N) {
        for (int i = 63; i >= 0; i--) cout << get_bit(N, i);
        cout << "\n";
    }

    // --- Đếm số bit 1 trong N ---
    int count_bit (uint N) {
        int cnt = 0;
        while (N) { cnt += N & 1; N >>= 1; }
        return cnt;
    }

    // --- Đặt bit thứ K của N thành status ---
    bool set_bit (uint &N, int K, bool status) {
        bool old = get_bit(N, K);
        if (status == old) return 0;
        if (status) N |= (1ULL << K);
        else N &= ~(1ULL << K);
        return 1;
    }

    // --- Đổi chỗ bit thứ K1 và K2 của N ---
    bool swap_bit (uint &N, int K1, int K2) {
        bool bit1 = get_bit(N, K1);
        bool bit2 = get_bit(N, K2);
        if (bit1 == bit2) return 0;
        set_bit(N, K1, bit2);
        set_bit(N, K2, bit1);
        return 1;
    }

    // --- Đếm độ dài chuỗi bit 1 liên tiếp dài nhất ---
    int max_length_1 (uint N) {
        int max_len = 0, cur_len = 0;
        for (int i = 0; i < 64; i++) {
            if (get_bit(N, i)) { cur_len++; max_len = max(max_len, cur_len); }
            else cur_len = 0;
        }
        return max_len;
    }

    // --- Trả về thông tin chuỗi bit liên tiếp dài nhất của bit B ---
    u16 max_len(uint N, bool B) {
        int maxLen = 0, curLen = 0, start = 0, bestStart = 0;
        for (int i = 0; i < 64; i++) {
            if (get_bit(N, i) == B) {
                if (curLen == 0) start = i;
                curLen++;
            } else {
                if (curLen > maxLen) { maxLen = curLen; bestStart = start; }
                curLen = 0;
            }
        }
        if (curLen > maxLen) { maxLen = curLen; bestStart = start; }

        u16 result = 0;
        result |= (u16)((maxLen - 1) & 0x3F);
        result |= (u16)((bestStart & 0x3F) << 6);
        result |= (u16)((B & 1) << 12);
        return result;
    }

    // --- Xoay trái K bit ---
    uint rotate_left(uint N, int K) {
        K %= 64;
        return (N << K) | (N >> (64 - K));
    }

    // --- Xoay phải K bit ---
    uint rotate_right(uint N, int K) {
        K %= 64;
        return (N >> K) | (N << (64 - K));
    }

    // --- Đếm số lần chuyển đổi giữa 0 và 1 ---
    u8 count_transitions(uint N) {
        u8 cnt = 0;
        for (int i = 0; i < 63; i++)
            if (get_bit(N, i) != get_bit(N, i + 1))
                cnt++;
        return cnt;
    }

    // --- Tìm vị trí P sao cho cửa sổ W bit bắt đầu từ P có giá trị gần M nhất ---
    u8 Nearest_window(uint N, uint M, u8 W) {
        uint bestP = 0;
        uint bestDiff = ULLONG_MAX;
        for (int P = 0; P + W <= 64; P++) {
            uint window = (N >> P) & ((1ULL << W) - 1);
            uint diff = (window > M) ? (window - M) : (M - window);
            if (diff < bestDiff) {
                bestDiff = diff;
                bestP = P;
            }
        }
        return bestP;
    }

    /*PHẦN MỞ RỘNG CHO MẢNG BIT*/

    // ----- Hàm chung dạng template -----
    template<typename T>
    // --- Lấy giá trị bit thứ bit_index trong mảng N ---
    bool get_bit_arr(const T N[], int bit_index) {
        int bits_per_elem = sizeof(T) * 8;
        int elem_idx = bit_index / bits_per_elem;
        int offset = bit_index % bits_per_elem;
        return (N[elem_idx] >> offset) & 1;
    }

    template<typename T>
    // --- Đặt giá trị bit thứ bit_index trong mảng N thành status ---
    bool set_bit_arr(T N[], int bit_index, bool status) {
        int bits_per_elem = sizeof(T) * 8;
        int elem_idx = bit_index / bits_per_elem;
        int offset = bit_index % bits_per_elem;
        bool old = (N[elem_idx] >> offset) & 1;
        if (old == status) return 0;
        if (status) N[elem_idx] |= (1ULL << offset);
        else N[elem_idx] &= ~(1ULL << offset);
        return 1;
    }

    template<typename T>
    // --- Đổi chỗ bit thứ K1 và K2 trong mảng N ---
    bool swap_bit_arr(T N[], int K1, int K2) {
        bool b1 = get_bit_arr(N, K1);
        bool b2 = get_bit_arr(N, K2);
        if (b1 == b2) return 0;
        set_bit_arr(N, K1, b2);
        set_bit_arr(N, K2, b1);
        return 1;
    }

    template<typename T>
    //  --- Đếm số bit 1 trong mảng N ---
    int count_bit_arr(const T N[], int num_elements) {
        int cnt = 0;
        for (int i = 0; i < num_elements; i++)
            cnt += __builtin_popcountll((uint64_t)N[i]);
        return cnt;
    }

    template<typename T>
    // --- Đếm độ dài chuỗi bit 1 liên tiếp dài nhất trong mảng N ---
    int max_length_1_arr(const T N[], int num_elements) {
        int total_bits = num_elements * sizeof(T) * 8;
        int cur = 0, best = 0;
        for (int i = 0; i < total_bits; i++) {
            if (get_bit_arr(N, i)) cur++;
            else cur = 0;
            best = max(best, cur);
        }
        return best;
    }

    template<typename T>
    // --- Trả về thông tin chuỗi bit liên tiếp dài nhất của bit B trong mảng N ---
    u16 max_len_arr(const T N[], int num_elements, bool B) {
        int total_bits = num_elements * sizeof(T) * 8;
        int cur = 0, best = 0, best_pos = 0;
        for (int i = 0; i < total_bits; i++) {
            if (get_bit_arr(N, i) == B) {
                cur++;
                if (cur > best) { best = cur; best_pos = i - cur + 1; }
            } else cur = 0;
        }
        u16 result = 0;
        result |= (best - 1) & 0x3F;
        result |= ((best_pos & 0x3F) << 6);
        result |= (B ? 1 : 0) << 12;
        return result;
    }

    template<typename T>
    // --- Đếm số lần chuyển đổi giữa 0 và 1 trong mảng N ---
    u8 count_transitions_arr(const T N[], int num_elements) {
        int total_bits = num_elements * sizeof(T) * 8;
        u8 cnt = 0;
        for (int i = 1; i < total_bits; i++)
            if (get_bit_arr(N, i) != get_bit_arr(N, i - 1))
                cnt++;
        return cnt;
    }

    template<typename T>
    // --- Lấy giá trị của cửa sổ W bit bắt đầu từ vị trí P trong mảng N ---
    uint64_t get_window_val(const T N[], int P, int W) {
        uint64_t val = 0;
        for (int i = 0; i < W; i++)
            if (get_bit_arr(N, P + i)) val |= (1ULL << i);
        return val;
    }

    template<typename T>
    // --- Tìm vị trí P sao cho cửa sổ W bit bắt đầu từ P có giá trị gần M nhất trong mảng N ---
    u8 Nearest_window_arr(const T N[], int num_elements, uint64_t M, u8 W) {
        int total_bits = num_elements * sizeof(T) * 8;
        u8 bestP = 0;
        uint64_t bestDiff = ULLONG_MAX;
        for (int P = 0; P + W <= total_bits; P++) {
            uint64_t v = get_window_val(N, P, W);
            uint64_t diff = (v > M) ? v - M : M - v;
            if (diff < bestDiff) { bestDiff = diff; bestP = P; }
        }
        return bestP;
    }
    ```

## Vòng lặp

## Mảng

### Mảng 1 chiều - Mảng 2 chiều (Array - 2D Array)
- Dynamic Array:
    ```c++
    #include <bits/stdc++.h>
    using namespace std;

    struct Vec {
        int* Arr; // mang du lieu
        int Size; // so phan tu hien tai
        int Capacity; // suc chua toi da
    };

    struct Function {
        // Khoi tao
        void init (Vec &v) {
            v.Arr = nullptr;
            v.Size = 0;
            v.Capacity = 0;
        }

        // Cap phat memory
        void reallocate (Vec &v, int val) {
            int* new_arr = new int[val];
            for(int i = 0; i < v.Size; i++) new_arr[i] = v.Arr[i];
            delete[] v.Arr;
            v.Arr = new_arr;
            v.Capacity = val;
        }

        int getCap (Vec &v) {
            int new_cap = (v.Capacity == 0) ? 1 : (v.Capacity << 1);
            return new_cap;
        }

        // Them phan tu vao sau
        void PushBack (Vec &v, int value) {
            if (v.Size >= v.Capacity) {
                int new_cap = getCap(v);
                reallocate(v, new_cap);
            }
            v.Arr[v.Size++] = value;
        }

        // Xoa phan tu cuoi cung
        void PopBack (Vec &v) {
            if (v.Size > 0) v.Size--;
        }

        // Them gia tri value vao vi tri index
        void Insert (Vec &v, int index, int value) {
            if (index < 0 || index > v.Size) return;
            if (v.Size >= v.Capacity) reallocate(v, getCap(v));

            for(int i = v.Size; i > index; i--) v.Arr[i] = v.Arr[i-1];
            v.Arr[index] = value;
            v.Size++;
        }

        // Xoa gia tri tai vi tri index
        void Erase (Vec &v, int index) {
            if (index < 0 || index >= v.Size) return;
            for(int i = index; i < v.Size - 1; i++) v.Arr[i] = v.Arr[i+1];
            v.Size--;
        }

        void swap_val (int &x, int &y) {
            int temp = x;
            x = y;
            y = temp;
        }

        // Dao nguoc gia tri cac vi tri trong khoang [a,b]
        void Reverse (Vec &v, int a, int b) {
            if (a < 0 || b >= v.Size || a >= b) return;
            while (a < b) {
                swap_val(v.Arr[a], v.Arr[b]);
                a++;
                b--;
            }
        }

        // Lay gia tri tai vi tri index
        int getValue (Vec &v, int index) {
            return v.Arr[index];
        }

        // Lay phan tu dau tien
        int getFront (Vec &v) {
            return v.Arr[0];
        }

        // Lay phan tu cuoi cung
        int getBack (Vec &v) {
            return v.Arr[v.Size - 1];
        }

        // In toan bo vector
        void PrintVector (Vec &v) {
            for(int i = 0; i < v.Size; i++) cout << getValue(v,i) << " ";
            cout << endl;
        }

        // Xoa vector
        void Clear (Vec &v) {
            v.Size = 0;
        }

        void Free (Vec &v) {
            delete[] v.Arr;
            init(v);
        }

        // Sap xep phan tu (tang dan)
        void Sort (Vec &v) {
            if (v.Size < 2) return;

            int n = v.Size;
            for(int i = 0; i < n - 1; i++) {
                for(int j = 0; j < n - i - 1; j++) {
                    if (v.Arr[j] > v.Arr[j+1]) swap_val(v.Arr[j], v.Arr[j+1]);
                }
            }
        }
    } Vector;

    int main () {
        Vec v;
        Vector.init(v);

        Vector.PushBack(v, 10);
        Vector.PushBack(v, 20);
        Vector.PushBack(v, 30);
        Vector.PushBack(v, 70);
        Vector.PushBack(v, 110);

        Vector.Insert(v, 1, 36);

        Vector.PrintVector(v);
        Vector.Sort(v);
        Vector.PrintVector(v);

        cout << v.Size << " " << v.Capacity << endl;

        Vector.Reverse(v, 2, 4);
        Vector.PrintVector(v);

        Vector.Free(v);
    }
    ```
### C-String

- Một số hàm thông dụng với C-String:
    ```c++
    #include <bits/stdc++.h>
    using namespace std;

    const int MAXN = 101;

    struct Functions {
        // inp-out string
        void getString (char s[MAXN]) { gets(s); } //cin.getline(s, Size);
        void outString (char s[MAXN]) { puts(s); }


        // Usage of function in string.h library
        void Copy (char* s1, char* s2) { strcpy(s2, s1); } // sao chep s1 vao s2
        void Upper (char* s) { strupr(s); } // Viet hoa ca chuoi (aBc --> ABC)
        void Lower (char* s) { strlwr(s); } // Viet thuong ca chuoi (ABc --> abc)
        void Reverse (char* s) { strrev(s); } // Dao nguoc ca chuoi (abc --> cba)
        void AddString (char* s, char* t) { strcat(s,t); } // Noi 2 chuoi (abc + def = abcdef)
        int FindString (char* s, char* found) { // Tim chuoi found trong s
            char* temp = strstr(s, found);
            if (temp == NULL) return -1;
            return temp - s;
        }

        // Other function
        void SubString (char* s, char* sub, int index, int subSize) { // Lay chuoi con subSize ki tu tu vi tri index cua s
            strncpy(sub, s + index, subSize);
            sub[subSize] = '\0';
        }

        void Clear (char* s) { s[0] = '\0'; }

        void AddChar (char* s, char added) { // Them ki tu added vao cuoi xau s
            int N = strlen(s);
            s[N] = added;
            s[N + 1] = '\0';
        }

        void Insert (char* s, int index, char added) { // Them ki tu added vao vi tri index
            int n = strlen(s);
            if (index < 0 || index >= n) return;
            for(int i = n; i >= index; i--) s[i + 1] = s[i];
            s[index] = added;
        }

        void Remove (char* s, int index) { // Xoa ki tu tai vi tri index
            int n = strlen(s);
            if (index < 0 || index >= n) return;
            for(int i = index; i < n; i++) s[i] = s[i+1];
        }
    } String;

    int main () {
        char s[100];
        String.getString(s);
        char sub[50];
        String.SubString(s, sub, 2, 4);
        String.outString(sub);
        String.AddChar(sub, 'c');
        String.Remove(sub, 0);
        String.outString(sub);
    }
    ```

## Làm việc với tập tin

### Text File

- Template và Ví dụ làm việc tới Text File:
    ```c++
    #include <bits/stdc++.h>
    using namespace std;

    void catData (char* filename, int a[], int n) {
        ofstream out(filename, ios::app);
        if (!out) {
            cout << "Khong the mo file " << filename << endl;
            return;
        }

        /*
            Data here
            Usage:
                - To get input from user: Using cin/getline/...
                - To cat data into the file: out << _data << endl; - with _data is what you want to write in the text file.
        */

        for(int i = 0; i < n; i++) out << a[i] << " ";

        out.close();
        cout << "File Update!" << endl;
    }

    void readData (char* filename, int b[], int n) {
        ifstream inp(filename);
        if (!inp) {
            cout << "Khong the mo file " << filename << endl;
            return;
        }

        /*
            Data here
            Usage:
                - To get data from file: Using cin/getline/...
                - To cat data into the screen: Using cout
        */

        /*
            Example:
            while (getline(in, line)) {
                cout << line << endl;
            }
        */
        for(int i = 0; i < n; i++) inp >> b[i];
        inp.close();
    }

    int main () {
    //    freopen("input.txt", "r", stdin); // read file
    //    freopen("output.txt", "w", stdout); // cat file
    /*
        Usage:
            - When using freopen, using cin/cout to input/output
            - When using readData/catData, add the data into the reference and use the usage in the function.
    */

        int a[5] = {1,2,3,5,4};
        int n = 5;
        int b[5];

        catData("test.txt", a, n);
        readData("test.txt", b, n);
        for(int i = 0; i < n; i++) cout << b[i] << ' ';
    }
    ```
### Binary File

- Template và ví dụ làm việc với binary file:
    ```c++
    #include <bits/stdc++.h>
    using namespace std;

    template <typename T>
    void readBinary (char* filename, T &data) { // doc du lieu file va luu vao data
        ifstream inp(filename, ios::binary);
        if (!inp) {
            cerr << "Khong the mo file " << filename << endl;
            return;
        }

        inp.read(reinterpret_cast<char*>(&data), sizeof(T));
        if (inp) cout << "Success!" << endl; // Hoan tat doc du lieu
        else cout << "Error!" << endl; // Loi khong doc duoc
        inp.close();
    }

    template <typename T>
    void writeBinary (char* filename, T &data) { // Ghi data vao file binary
        ofstream out(filename, ios::binary);
        if (!out) {
            cerr << "Khong the mo file " << filename << endl;
            return;
        }

        out.write(reinterpret_cast<char*>(&data), sizeof(T));
        out.close();
        cout << "Success!" << endl;
    }

    int main () {
        /*
            Usage:
                - With using if/ofstream: T can be array, struct, value,..
        */

        int a[5] = {1,2,3,5,4};
        int n = 5;
        int b[5];

        writeBinary("file.bin", a);
        readBinary("file.bin", b);
        for(int i = 0; i < n; i++) cout << b[i] << " ";

        char c[] = "Len phim 36";
        char res[] = {0};
        int m = strlen(c);
        writeBinary("file01.bin", c);
        readBinary("file01.bin", res);
        puts(res);
    }
    ```

## Các hàm khác
