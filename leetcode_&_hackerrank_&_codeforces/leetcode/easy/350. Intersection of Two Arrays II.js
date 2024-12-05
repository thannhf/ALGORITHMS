// Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.

 

// Example 1:

// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2,2]
// Example 2:

// Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
// Output: [4,9]
// Explanation: [9,4] is also accepted.

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number[]}
 */
var intersect = function(nums1, nums2) {
    //sắp xếp 2 mảng theo thứ tự tăng dần
    nums1.sort((a, b) => a - b);
    nums2.sort((a,b) => a - b);
    //Khởi tạo hai con trỏ i và j thành 0
    // và một mảng trống để lưu trữ kết quả
    let i = 0;
    let j = 0;
    let result = [];
    // Lặp lại cả hai mảng cho đến khi hết một mảng
    while(i < nums1.length && j < nums2.length) {
        // Nếu các phần tử hiện tại trong cả hai mảng đều bằng nhau,
        // thêm nó vào kết quả mảng và tăng cả hai con trỏ
        if(nums1[i] === nums2[j]) {
            result.push(nums1[i]);
            i++;
            j++;
            // nếu phần tử hiện tại trong nums1 < phần tử hiện tại trong nums2 thì tăng i lên 1
        } else if(nums1[i] < nums2[j]) {
            i++;
            // ngược lại thì tăng j
        } else {
            j++;
        }
    }
    return result;
};