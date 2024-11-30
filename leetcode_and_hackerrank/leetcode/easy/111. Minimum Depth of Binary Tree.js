// Given a binary tree, find its minimum depth.
// The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
// Note: A leaf is a node with no children.

// Example 1:
// Input: root = [3,9,20,null,null,15,7]
// Output: 2

// Example 2:
// Input: root = [2,null,3,null,4,null,5,null,6]
// Output: 5

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
 * @return {number}
 */
var minDepth = function(root) {
    //Nếu cây yên tĩnh, tức là gốc là NULL, trả về độ sâu là 0
    if(root == null) return 0;
    //nếu cả hai cây đều trống trả về 1
    if(root.left == null && root.right == null) return 1;
    //Nếu cây bên trái trống, hãy trả về độ sâu của cây bên phải sau khi thêm 1 vào nó
    if(root.left == null)
        return 1 + minDepth(root.right);
    //nếu cây bên phải trống, hãy trả về độ sâu của cây bên trái sau khi thêm 1 vào nó
    if(root.right == null) 
        return 1 + minDepth(root.left);
    //khi hàm hai con trả về độ sâu của nó
    //Chọn giá trị tối thiểu trong hai cây con này và trả về giá trị này sau khi thêm 1 vào nó
    return Math.min(minDepth(root.left), minDepth(root.right)) + 1;
};