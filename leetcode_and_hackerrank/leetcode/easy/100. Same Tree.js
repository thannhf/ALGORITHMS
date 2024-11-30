// Given the roots of two binary trees p and q, write a function to check if they are the same or not.
// Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

// Example 1:
// Input: p = [1,2,3], q = [1,2,3]
// Output: true

// Example 2:
// Input: p = [1,2], q = [1,null,2]
// Output: false

// Example 3:
// Input: p = [1,2,1], q = [1,1,2]
// Output: false

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} p
 * @param {TreeNode} q
 * @return {boolean}
 1. Trường hợp cơ bản:

- Mã bắt đầu với hai trường hợp cơ bản. Nếu cả hai pvà qđều là null, điều này có nghĩa là cả hai cây đều trống và chúng được coi là giống hệt nhau. Trong trường hợp này, nó trả về true.
- Nếu một trong hai cây nullcòn cây kia thì không, thì các cây đó không thể giống nhau nên trả về false.
So sánh giá trị:

- Sau khi xử lý các trường hợp cơ sở, mã so sánh giá trị của các nút hiện tại của pvà q. Nếu các giá trị không khớp, điều đó có nghĩa là các cây không giống nhau và nó trả về false.
2. Kiểm tra đệ quy cây con trái và phải:

- Nếu giá trị của các nút hiện tại khớp nhau, mã sẽ tiến hành kiểm tra đệ quy cây con bên trái và bên phải của cả hai cây.
- Lệnh gọi đệ quy cho cây con bên trái so sánh con trái của pvới con trái của q.
- Lệnh gọi đệ quy cho cây con bên phải so sánh con bên phải của pvới con bên phải của q.
3. Kết quả cuối cùng được tính toán bằng cách sử dụng &&toán tử (logic AND) để đảm bảo rằng cả cây con bên trái và bên phải đều giống nhau để toàn bộ cây giống hệt nhau.
 */
var isSameTree = function(p, q) {
    if(p === null && q === null) {
        return true;
    } else if(p === null || q === null) {
        return false;
    } else if(p.val !== q.val) {
        return false;
    }
    return isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
};