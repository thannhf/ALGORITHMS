// Given the head of a singly linked list, reverse the list, and return the reversed list.

// Example 1:
// Input: head = [1,2,3,4,5]
// Output: [5,4,3,2,1]
// Example 2:
// Input: head = [1,2]
// Output: [2,1]
// Example 3:

// Input: head = []
// Output: []

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {ListNode}
 */
var reverseList = function(head) {
    // trường hợp đặc biệt
    if(head == null || head.next == null) return head;
    //Tạo một nút mới để gọi hàm đệ quy và chúng ta nhận được danh sách liên kết ngược
    var res = reverseList(head.next);
    // Đặt nút đầu là head.next.next
    head.next.next = head;
    // đặt phần đầu bên cạnh là null
    head.next = null;
    return res;// Trả về danh sách liên kết ngược
};