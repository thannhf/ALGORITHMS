// Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
// You must write an algorithm with O(log n) runtime complexity.

// Example 1:

// Input: nums = [1,3,5,6], target = 5
// Output: 2
// Example 2:

// Input: nums = [1,3,5,6], target = 2
// Output: 1
// Example 3:

// Input: nums = [1,3,5,6], target = 7
// Output: 4

/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
Tạo hai biến vị trí trái và phải bắt đầu từ 0 và độ dài mảng -1 tương ứng
tính điểm giữa của mảng, được tính bằng phép cộng (trái + phải) / 2
Tạo một biến khác InsertPosition cho vị trí đích trong trường hợp giá trị đích không phải là một phần của mảng
Sử dụng vòng lặp while, lặp qua mảng miễn là bên trái nhỏ hơn hoặc bằng bên phải
1. kiểm tra xem mảng ở điểm giữa có nhỏ hơn mục tiêu hay không, cập nhật giá trị bên phải thành điểm giữa -1 và InsertPosition thành điểm giữa
2. nếu mảng ở điểm giữa lớn hơn mục tiêu, cập nhật giá trị bên trái thành điểm giữa + 1 và chènPosition thành điểm giữa + 1
3. nếu mảng ở điểm giữa bằng mục tiêu trả về điểm giữa
nếu mảng ở điểm giữa bằng mục tiêu, trả về giá trị điểm giữa, nếu không thì trả về vị trí chèn
 */
var searchInsert = function(nums, target) {
    let leftPosition = 0;
    let rightPosition = nums.length - 1;
    let middle = Math.floor((leftPosition + rightPosition) / 2);
    let insertedPosition = 0;
    while(leftPosition <= rightPosition) {
        if(target < nums[middle]) {
            insertedPosition = middle;
            rightPosition = middle - 1;
        } else if(target > nums[middle]) {
            insertedPosition = middle + 1;
            leftPosition = middle + 1;
        } else if (target === nums[middle]) {
            return middle;
        }
        middle = Math.floor((leftPosition + rightPosition) / 2);
    }
    if(nums[middle] === target) {
        return middle;
    } else {
        return insertedPosition;
    }
};