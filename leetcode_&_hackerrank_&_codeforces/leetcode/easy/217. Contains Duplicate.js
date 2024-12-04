// Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
// Example 1:
// Input: nums = [1,2,3,1]
// Output: true
// Explanation:
// The element 1 occurs at the indices 0 and 3.

// Example 2:
// Input: nums = [1,2,3,4]
// Output: false
// Explanation:
// All elements are distinct.

// Example 3:
// Input: nums = [1,1,1,3,3,4,3,2,4,2]
// Output: true

/**
 * @param {number[]} nums
 * @return {boolean}
Dòng đầu tiên nums.sort((a, b) => a - b); 
sắp xếp các số mảng theo thứ tự tăng dần bằng phương pháp sắp xếp có sẵn.

Hàm mũi tên được cung cấp (a, b) => a - b 
đóng vai trò là tiêu chí so sánh sắp xếp, 
đảm bảo rằng các phần tử nhỏ hơn xuất hiện trước các phần tử lớn hơn.

Vòng lặp for lặp qua các mảng 
được sắp xếp từ chỉ số 0 đến nums.length - 2 (phần tử từ thứ hai đến cuối cùng).

Bên trong vòng lặp, điều kiện nums[i] === nums[i + 1] 
kiểm tra xem phần tử hiện tại (nums[i]) có bằng phần tử 
tiếp theo hay không (nums[i + 1]).

Nếu điều kiện này đúng, điều đó có nghĩa là đã tìm thấy 
một bản sao và hàm ngay lập tức trả về
 */
var containsDuplicate = function(nums) {
    nums.sort((a,b) => a - b);
    for(let i = 0; i <= nums.length-1; i++) {
        if(nums[i] === nums[i+1]) {
            return true;
        }
    }
    return false;
};