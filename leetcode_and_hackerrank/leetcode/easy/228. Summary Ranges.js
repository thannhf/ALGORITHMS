// You are given a sorted unique integer array nums.

// A range [a,b] is the set of all integers from a to b (inclusive).

// Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That is, each element of nums is covered by exactly one of the ranges, and there is no integer x such that x is in one of the ranges but not in nums.

// Each range [a,b] in the list should be output as:

// "a->b" if a != b
// "a" if a == b
 

// Example 1:

// Input: nums = [0,1,2,4,5,7]
// Output: ["0->2","4->5","7"]
// Explanation: The ranges are:
// [0,2] --> "0->2"
// [4,5] --> "4->5"
// [7,7] --> "7"
// Example 2:

// Input: nums = [0,2,3,4,6,8,9]
// Output: ["0","2->4","6","8->9"]
// Explanation: The ranges are:
// [0,0] --> "0"
// [2,4] --> "2->4"
// [6,6] --> "6"
// [8,9] --> "8->9"

/**
 * @param {number[]} nums
 * @return {string[]}
 */
var summaryRanges = function(nums) {
    //Tạo danh sách chuỗi để lưu trữ kết quả đầu ra
    const output = [];
    //Bắt đầu duyệt mảng từ idx = 0 cho đến idx < sizeofarray trong vòng lặp while
    let idx = 0;
    while(idx < nums.length) {
        //Khởi tạo chỉ số đầu tiên và cuối cùng để xác định liên kết phần tử trong mảng
        let beg, last;
        // Đánh dấu tại hiện tại chỉ mục là phần tử bắt đầu của phạm vi
        beg = nums[idx];
        // Duyệt mảng bắt đầu từ hiện tại chỉ mục và tìm phần tử cuối cùng có độ chênh lệch so với phần tử trước chính xác là 1, tức là nums[idx + 1] == nums[idx] + 1
        while(idx + 1 < nums.length && nums[idx + 1] === nums[idx] + 1)
            idx++;
        // Đặt phần tử này làm phần tử cuối cùng của phạm vi
        last = nums[idx];
        //neu không có phần tử liên tục
        if(beg == last)
            output.push(beg + "");
        //ngược lại
        else
            output.push(beg + "->" + last);
        idx++;
    }
    return output;
};