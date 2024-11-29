// Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

// Example 1:
// Input: head = [1,1,2]
// Output: [1,2]

// Example 2:
// Input: head = [1,1,2,3,3]
// Output: [1,2,3]

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
 1. Hàm bắt đầu bằng cách kiểm tra xem đối số head có rỗng hay không, trong trường hợp đó nó trả về null. Kiểm tra này xử lý trường hợp danh sách liên kết trống.
2. Sau đó, hàm khai báo một biến cục bộ curr và khởi tạo nó thành head. Biến này sẽ được sử dụng để duyệt qua danh sách liên kết và xóa bất kỳ nút trùng lặp nào.
3. Sau đó, hàm sẽ đi vào một vòng lặp while tiếp tục miễn là curr.next không rỗng. Vòng lặp này sẽ lặp qua toàn bộ danh sách liên kết.
4. Trong vòng lặp, hàm sẽ kiểm tra xem giá trị được lưu trong nút hiện tại (curr.val) có bằng giá trị được lưu trong nút tiếp theo (curr.next.val) hay không. Nếu các giá trị này bằng nhau thì nút hiện tại và nút tiếp theo là trùng lặp và nút tiếp theo cần phải bị xóa.
5. Để xóa nút tiếp theo, trước tiên hàm sẽ lưu tham chiếu đến nút sau nút tiếp theo (next_next). Điều này là cần thiết vì sau khi nút tiếp theo bị xóa, chúng ta sẽ cần cập nhật Curr.next để bỏ qua nút đã xóa và trỏ đến nút sau nút tiếp theo.
6. Sau đó, hàm này khai báo một biến cục bộ nodeToDelete và khởi tạo nó thành curr.next, đây là nút cần xóa.
7. Sau đó, hàm này gọi hàm xóa tích hợp và chuyển nó sang nodeToDelete, hàm này sẽ xóa nút khỏi danh sách được liên kết.
8. Cuối cùng, hàm cập nhật Curr.next để trỏ đến nút sau nút tiếp theo (next_next), bỏ qua nút đã xóa một cách hiệu quả.
9. Nếu các giá trị được lưu trữ trong curr.val và curr.next.val không bằng nhau thì nút hiện tại và nút tiếp theo không trùng lặp và vòng lặp chỉ đơn giản chuyển Curr sang nút tiếp theo bằng cách cập nhật Curr thành Curr.next.
10. Sau khi vòng lặp hoàn tất, hàm trả về head, đây là tham chiếu đến nút head của danh sách liên kết đã loại bỏ các bản sao
 */
var deleteDuplicates = function(head) {
    if(head == null) 
    return null;
    let curr = head;
    while(curr.next != null) {//lặp cho đến khi danh sách là null
        if(curr.val == curr.next.val) {//nếu giá trị nút đầu tiên bằng giá trị nút tiếp theo
            let next_next = curr.next.next;//khai báo biến gán giá trị là nút tiếp theo của nút tiếp theo kể tử nút đầu tiên
            let nodeToDelete = curr.next;//khai báo biến gán giá trị là nút tiếp theo kể từ nút đầu tiên 
            delete(nodeToDelete);//xóa nút đó
            curr.next = next_next;//gán nút tiếp theo vào nút vừa bị xóa
        } else {
            curr = curr.next;
        }
    }
    return head;
};