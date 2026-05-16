# Kiểm Tra Tính Hợp Lệ Của BFS (Valid BFS)

## Tóm Tắt Bài Toán

Cho một cây vô hướng có `n` đỉnh được đánh số từ 1 đến n. Cần kiểm tra xem một dãy cho trước có thể là kết quả của một phép BFS bắt đầu từ đỉnh 1 hay không.

**Đặc điểm của BFS:**
- Khởi tạo hàng đợi chỉ chứa đỉnh 1, đánh dấu đỉnh 1 đã duyệt
- Lặp lại: lấy một đỉnh từ đầu hàng đợi, in ra, sau đó thêm tất cả các đỉnh kề chưa duyệt vào cuối hàng đợi
- Vì thứ tự duyệt các đỉnh kề có thể thay đổi, nên có thể có nhiều dãy BFS khác nhau

## Input/Output

**Input:**
- Dòng 1: số nguyên `n` (1 ≤ n ≤ 2×10⁵)
- `n-1` dòng tiếp theo: các cạnh `u v` của cây
- Dòng cuối: `n` số nguyên là dãy cần kiểm tra

**Output:**
- In "Yes" nếu dãy hợp lệ, "No" nếu không

## Thuật Toán Giải Quyết

### Ý Tưởng Chính

Để kiểm tra xem một dãy có phải là kết quả BFS hợp lệ:

1. **Xây dựng danh sách kề:** Lưu tất cả các cạnh của cây
2. **Sắp xếp các hàng xóm:** Với mỗi đỉnh, sắp xếp danh sách hàng xóm theo thứ tự xuất hiện trong dãy cho trước
   - Sử dụng mảng `pos[]` để lưu vị trí của mỗi đỉnh trong dãy
   - Sắp xếp các hàng xóm dựa trên vị trí này
3. **Thực hiện BFS với thứ tự sắp xếp này** và kiểm tra:
   - Dãy kết quả BFS có giống với dãy đầu vào không?
   - Nếu giống → "Yes", ngược lại → "No"

### Lý Do Thuật Toán Đúng

- Nếu một dãy là kết quả hợp lệ của BFS, thì khi sắp xếp các hàng xóm theo thứ tự xuất hiện trong dãy đó, BFS sẽ phải sinh ra đúng dãy đó
- Nếu dãy không hợp lệ, thì không có cách sắp xếp hàng xóm nào có thể sinh ra dãy đó theo BFS

## Các Bug Được Tìm Và Sửa

### Bug 1: Queue::resize() - Sao chép sai số lượng phần tử

**Vị trí:** Hàm `resize()` của lớp Queue, dòng ~19

**Vấn đề:**
```cpp
for(int i = 0; i < size; i++)  // ❌ Sai!
    newData[i] = data[(head + i) % size];
```

Hàm sao chép tất cả các slot `size` thay vì chỉ sao chép `currentSize` phần tử có giá trị.

**Hậu quả:** Khi hàng đợi không được điền đầy, sẽ sao chép vùng nhớ chưa khởi tạo, làm hỏng dữ liệu.

**Sửa:**
```cpp
for(int i = 0; i < currentSize; i++)  // ✅ Đúng!
    newData[i] = data[(head + i) % size];
```

### Bug 2: Vector() - Cấp phát mảng kích thước 0

**Vị trí:** Constructor mặc định của lớp Vector, dòng ~101

**Vấn đề:**
```cpp
Vector() {
    size = 0;
    capacity = 0;
    data = new T[capacity];  // ❌ new T[0] là undefined behavior!
}
```

Cấp phát mảng với kích thước 0 là hành vi không xác định trong C++. Điều này gây hỏng dữ liệu vì đối tượng `bfsResult` sử dụng constructor này.

**Sửa:**
```cpp
Vector() {
    size = 0;
    capacity = 1;  // ✅ Cấp phát tối thiểu 1 phần tử
    data = new T[capacity];
}
```

## Code Chính

```cpp
int main () {
    // Đọc input
    cin >> numNodes;
    for(int i = 1; i < numNodes; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Đọc dãy cần kiểm tra
    for(int i = 0; i < numNodes; i++) {
        cin >> path[i];
        pos[path[i]] = i;  // Lưu vị trí của mỗi đỉnh
    }

    // Kiểm tra bắt đầu từ đỉnh 1
    if (path[0] != 1) {
        cout << "No" << endl;
        return 0;
    }

    // Sắp xếp các hàng xóm theo thứ tự xuất hiện trong dãy
    for(int i = 1; i <= numNodes; i++) {
        sort(adj[i].begin(), adj[i].end(), compare);
    }

    // Thực hiện BFS và kiểm tra
    Queue<int> q;
    bool visited[MAXN] = {false};
    int currentIdx = 0;

    q.push(1);
    visited[1] = true;

    while (!q.isEmpty() && currentIdx < numNodes) {
        int node = q.front();
        q.pop();

        if (path[currentIdx] != node) {
            cout << "No" << endl;
            return 0;
        }
        currentIdx++;

        for(int i = 0; i < adj[node].getSize(); i++) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    if (currentIdx == numNodes) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}
```

## Độ Phức Tạp

- **Thời gian:** O(n log n) - do sắp xếp các cạnh cho mỗi đỉnh
- **Không gian:** O(n) - cho danh sách kề và mảng visited

## Kết Luận

Bài toán yêu cầu:
1. Hiểu rõ cơ chế BFS
2. Nhận thấy rằng thứ tự duyệt hàng xóm ảnh hưởng đến kết quả
3. Sử dụng sắp xếp để tìm thứ tự hàng xóm phù hợp (nếu có)
4. Kiểm tra xem BFS với thứ tự đó có sinh ra dãy đầu vào

Hai bug trong implementation Queue và Vector là những lỗi phổ biến khi cài đặt cấu trúc dữ liệu custom, cần được chú ý đặc biệt.
