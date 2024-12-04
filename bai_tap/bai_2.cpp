// Bài tập 1.3. Cho A là tập hợp con của tập số thực, cận dưới đúng x0 của A kí hiệu Inf(A) = x0 có thể xác định bởi mệnh đề sau: 
// “ Với mọi x trong A có x0 ≤ x và với x1 có tính chất là x1 ≤ x với mọi x trong A thì suy ra x1 ≤ x0 ”. Hãy dùng các kí hiệu để 
// diễn tả mệnh đề trên và mệnh đề phủ định của nó. Từ đó đưa ra cách chứng minh một số không phải là Inf(A).

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Hàm kiểm tra nếu x0 là cận dưới đúng (Inf(A))
bool isInf(const vector<double>& A, double x0) {
    // Kiểm tra x0 có là cận dưới không
    for (double x : A) {
        if (x0 > x) {
            return false; // x0 không phải cận dưới
        }
    }

    // Kiểm tra nếu tồn tại x1 > x0 mà vẫn là cận dưới
    for (double x1 = x0 + 0.01; ; x1 += 0.01) { // Duyệt x1 > x0
        bool isLowerBound = true;
        for (double x : A) {
            if (x1 > x) {
                isLowerBound = false;
                break;
            }
        }
        if (isLowerBound) return false; // Tồn tại x1 > x0 mà vẫn là cận dưới
        if (x1 > *min_element(A.begin(), A.end())) break; // Dừng nếu x1 vượt qua min(A)
    }
    return true; // x0 là Inf(A)
}

int main() {
    vector<double> A = {1.0, 2.0, 3.0, 4.0}; // Tập hợp A
    double x0;

    cout << "Nhap x0: ";
    cin >> x0;

    if (isInf(A, x0)) {
        cout << x0 << " la Inf(A)." << endl;
    } else {
        cout << x0 << " khong phai la Inf(A)." << endl;
    }

    return 0;
}
