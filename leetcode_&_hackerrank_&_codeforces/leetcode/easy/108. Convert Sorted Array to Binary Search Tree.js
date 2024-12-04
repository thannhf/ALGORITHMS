// Given an integer array nums where the elements are sorted in ascending order, convert it to a 
// height-balanced binary search tree.

// Example 1:
// Input: nums = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]
// Explanation: [0,-10,5,null,-3,null,9] is also accepted:

// Example 2:
// Input: nums = [1,3]
// Output: [3,1]
// Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {number[]} nums
 * @return {TreeNode}
 */
var sortedArrayToBST = function(nums) {
    //Gọi hàm đệ quy
    return ConvToBST(nums, 0, nums.length - 1);
};
//Tạo một hàm sẽ chuyển đổi bất kỳ phạm vi cụ thể nào của mảng số đã chọn...
// và trả về BST gốc của nút tương ứng
var ConvToBST = function(nums, beg, end) {
    //Nếu bắt đầu > kết thúc, hãy trả về NULL, vì chúng tôi nhận được phạm vi sai
    if(beg > end) return null;
    //đặt nút giữa
    var mid = Math.ceil((beg + end) / 2);
    //Khởi tạo nút gốc có giá trị giống như nums[mid]
    var root = new TreeNode(nums[mid]);
    //Gán các cây bên trái giống như các hàm được gọi trên các dãy bên trái
    root.left = ConvToBST(nums, beg, mid - 1);
    //Các cây bên phải giống như hàm được gọi trên các chuỗi bên phải
    root.right = ConvToBST(nums, mid + 1, end);
    //trả về root node
    return root;
}