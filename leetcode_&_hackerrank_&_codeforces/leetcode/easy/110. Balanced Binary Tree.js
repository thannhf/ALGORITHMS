// Given a binary tree, determine if it is height-balanced.

// Example 1:
// Input: root = [3,9,20,null,null,15,7]
// Output: true

// Example 2:
// Input: root = [1,2,2,3,3,null,null,4,4]
// Output: false

// Example 3:
// Input: root = []
// Output: true

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {boolean}
 */
var isBalanced = function(root) {
    //Nếu cây trống, ta có thể nói nó cân bằng
    if(root == null) return true;
    //Hàm Height sẽ trả về -1, khi đó là cây không cân bằng
    if(Height(root) == -1) return false;
    return true;
};
//Tạo hàm trả về “chiều cao” của cây con hiện tại bằng cách sử dụng đệ quy
var Height = function(root) {
    //vỏ cơ sở
    if(root == null) return 0;
    //Chiều cao của cây con trái
    let leftHeight = Height(root.left);
    //Chiều cao của cây con chiều cao
    let rightHeight = Height(root.right);
    //Trường hợp cây con trái hoặc cây con phải không cân bằng thì trả về -1
    if(leftHeight == -1 || rightHeight == -1) return -1;
    //Nếu chiều cao của chúng khác nhau nhiều hơn '1', hãy trả về -1
    if(Math.abs(leftHeight - rightHeight) > 1) return -1;
    //Ngược lại, trả về chiều cao của cây con này là max(leftHeight, rightHight) + 1
    return Math.max(leftHeight, rightHeight) + 1;
}