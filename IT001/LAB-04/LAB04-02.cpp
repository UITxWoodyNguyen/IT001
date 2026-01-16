#include <bits/stdc++.h>
using namespace std;

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define uint uint64_t

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }

/*HÀM BIT CƠ BẢN CHO 1 SỐ DUY NHẤT (CÂU 1)*/

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

/*PHẦN MỞ RỘNG CHO MẢNG BIT (CÂU 2, 3, 4)*/

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

int main() {
    // ================= Câu 1 =================
    cout << "===== Cau 1 =====\n";
    uint N = 9;
    cout << "Bits of N: "; out_bit(N);
    cout << "Bit 3 = " << get_bit(N, 3) << "\n";
    cout << "Popcount = " << count_bit(N) << "\n";
    cout << "Max 1-seq length = " << max_length_1(N) << "\n";
    cout << "Rotate left 2: "; out_bit(rotate_left(N, 2));
    cout << "Rotate right 2: "; out_bit(rotate_right(N, 2));
    cout << "Transitions: " << (int)count_transitions(N) << "\n";
    cout << "Nearest window (W=3, M=5): P=" << (int)Nearest_window(N, 5, 3) << "\n\n";

    // ================= Câu 2 =================
    cout << "===== Cau 2 =====\n";
    u8 A[1000] = {};
    set_bit_arr(A, 0, 1);
    set_bit_arr(A, 3, 1);
    set_bit_arr(A, 4, 1);
    cout << "Popcount = " << count_bit_arr(A, 1000) << "\n";
    cout << "MaxLen1 = " << max_length_1_arr(A, 1000) << "\n";
    cout << "Transitions = " << (int)count_transitions_arr(A, 1000) << "\n";

    // ================= Câu 3 =================
    cout << "\n===== Cau 3 =====\n";
    u16 B[1000] = {};
    set_bit_arr(B, 10, 1);
    set_bit_arr(B, 11, 1);
    set_bit_arr(B, 15, 1);
    cout << "Popcount = " << count_bit_arr(B, 1000) << "\n";
    cout << "MaxLen1 = " << max_length_1_arr(B, 1000) << "\n";
    cout << "Transitions = " << (int)count_transitions_arr(B, 1000) << "\n";

    // ================= Câu 4 =================
    cout << "\n===== Cau 4 =====\n";
    static u8 C[10'000'000] = {}; // static để tránh lỗi stack
    set_bit_arr(C, 123456, 1);
    set_bit_arr(C, 123457, 1);
    cout << "Popcount = " << count_bit_arr(C, 10'000'000) << "\n";
    cout << "Transitions = " << (int)count_transitions_arr(C, 10'000'000) << "\n";
    cout << "Nearest window (W=3, M=5): P=" << (int)Nearest_window_arr(C, 10'000'000, 5, 3) << "\n";

    return 0;
}