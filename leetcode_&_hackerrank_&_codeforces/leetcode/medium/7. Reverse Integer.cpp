// Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.

// Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

 

// Example 1:

// Input: x = 123
// Output: 321
// Example 2:

// Input: x = -123
// Output: -321
// Example 3:

// Input: x = 120
// Output: 21
 

// Constraints:

// -231 <= x <= 231 - 1

class Solution {
public:
    int reverse(int x) {
        long r = 0;
        while(x) {
            r = r * 10 + x % 10;
            x /= 10;
        }
        if(r > INT_MAX || r < INT_MIN) return 0;
        return int(r);
    }
};
// có thể giải bài toán này bằng cách đưa từng chữ số vào một vector rồi đảo ngược thứ tự hoặc xử lý từ cuối lên đầu nhưng cách này không tối ưu về bộ nhớ, tăng độ phức tạo logic, kém hiệu quả hơn so với bài trên trong các bài cần tối ưu về tốc độ xử lý của thuật toán.

//có thể xử lý như một chuỗi ký tự: chuyển số thành chuỗi, đảo chuỗi, rồi chuyển lại thành số, nhược điểm việc chuyển qua lại giữa số và chuỗi làm giảm hiệu năng.