// Given an integer array nums, handle multiple queries of the following type:

// Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
// Implement the NumArray class:

// NumArray(int[] nums) Initializes the object with the integer array nums.
// int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 

// Example 1:

// Input
// ["NumArray", "sumRange", "sumRange", "sumRange"]
// [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
// Output
// [null, 1, -1, -3]

// Explanation
// NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
// numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
// numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
// numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3

/**
 * @param {number[]} nums
 */
var NumArray = function(nums) {
    this.size = nums.length;// lưu trữ độ dài của mảng
    this.prefixSum = Array(nums.length).fill(0);// trống mảng
    this.prefixSum[0] = nums[0];//Giá trị đầu tiên của tổng tiền tố tương tự với giá trị đầu tiên của các số tử tử
    for(let i = 1; i < this.size; i++) {//duyệt từ trái qua phải của mảng
        this.prefixSum[i] = this.prefixSum[i - 1] + nums[i];
        /*lưu trữ tổng giá trị hiện tại (số) + tổng giá trị trước đó
        tại chỉ mục trước nó(prefixsum)*/
    }
};

/** 
 * @param {number} left 
 * @param {number} right
 * @return {number}
 */
NumArray.prototype.sumRange = function(left, right) {
    if(left == 0) {
        /* nếu chỉ mục bên trái không được đề cập thì 
        chúng tôi sẽ trả về tổng cho đến chỉ mục bên phải từ mảng tổng tiền tố */
        return this.prefixSum[right];
    } else {
        // if if left left only được đưa ra thì sẽ trả về tổng
        // cho đến khi bên phải chỉ số trừ đi giá trị của tổng tiền tố tại
        // chỉ mục trước bên trái chỉ mục, tức là giá trị
        // tại chỉ mục (trái - 1)
        return this.prefixSum[right] - this.prefixSum[left - 1];
    }
};

/** 
 * Your NumArray object will be instantiated and called as such:
 * var obj = new NumArray(nums)
 * var param_1 = obj.sumRange(left,right)
 */