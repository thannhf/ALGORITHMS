#include <cassert>
#include <iostream>
#include <new>

namespace data_structures {
	namespace linked_list{
		class Node{
			public:
				int32_t val;
				Node* next;
		};
		Node* copy_all_nodes(const Node* const node) {
			if(node) {
				Node* res = new Node();
				res->val = node->val;
				res->next = copy_all_nodes(node->next);
				return res;
			}
			return nullptr;
		}
		class list {
			private:
				Node* head = nullptr;
				void delete_all_nodes();
				void copy_all_nodes_from_list(const list& other);
			public:
				bool isEmpty() const;
				void insert(int32_t new_elem);
				void reverseList();
				void display() const;
				int32_t top() const;
				int32_t last() const;
				int32_t traverse(int32_t index) const;
				~list();
				list() = default;
				list(const list& other);
				list& operator=(const list& other);
		};
		bool list::isEmpty() const {
			return head == nullptr;
		}
		void list::insert(int32_t n) {
			try{
				Node* new_node = new Node();
				Node* temp = nullptr;
				new_node->val = n;
				new_node->next = nullptr;
				if(isEmpty()) {
					head = new_node;
				} else {
					temp = head;
					while(temp->next != nullptr) {
						temp = temp->next;
					}
					temp->next = new_node;
				}
			} catch(std::bad_alloc& exception) {
				std::cerr << "bad_alloc detected: " << exception.what() << "\n";
			}
		}
		void list::reverseList(){
			Node* curr = head;
			Node* prev = nullptr;
			Node* next_node = nullptr;
			while(curr != nullptr) {
				next_node = curr->next;
				curr->next = prev;
				prev = curr;
				curr = next_node;
			}
			head = prev;
		}
		int32_t list::top() const {
			if(!isEmpty()) {
				return head->val;
			} else {
				throw std::logic_error("List is empty");
			}
		}
		int32_t list::last() const {
			if(!isEmpty()) {
				Node* t = head;
				while(t->next != nullptr) {
					t = t->next;
				}
				return t->val;
			} else {
				throw std::logic_error("List is empty");
			}
		}
		int32_t list::traverse(int32_t index) const {
			Node* current = head;
			int count = 0;
			while(current != nullptr) {
				if(count == index) {
					return (current->val);
				}
				count++;
				current = current->next;
			}
			exit(1);
		}
		void list::delete_all_nodes() {
			while(head != nullptr) {
				const auto tmp_node = head->next;
				delete head;
				head = tmp_node;
			}
		}
		list::~list() {
			delete_all_nodes();
		}
		void list::copy_all_nodes_from_list(const list& other) {
			assert(isEmpty());
			head = copy_all_nodes(other.head);
		}
		list::list(const list& other) {
			copy_all_nodes_from_list(other);
		}
		list& list::operator=(const list& other) {
			if(this == &other) {
				return *this;
			}
			delete_all_nodes();
			copy_all_nodes_from_list(other);
			return *this;
		}
	}
}
static void test() {
	data_structures::linked_list::list L;
	// 1st test
    L.insert(11);
    L.insert(12);
    L.insert(15);
    L.insert(10);
    L.insert(-12);
    L.insert(-20);
    L.insert(18);
    assert(L.top() == 11);
    assert(L.last() == 18);
    L.reverseList();
    // Reversal Testing
    assert(L.top() == 18);
    assert(L.traverse(1) == -20);
    assert(L.traverse(2) == -12);
    assert(L.traverse(3) == 10);
    assert(L.traverse(4) == 15);
    assert(L.traverse(5) == 12);
    assert(L.last() == 11);
    std::cout << "All tests have successfully passed!" << std::endl;
}
void test_copy_constructor() {
    data_structures::linked_list::list L;
    L.insert(10);
    L.insert(20);
    L.insert(30);
    data_structures::linked_list::list otherList(L);
    otherList.insert(40);

    L.insert(400);

    assert(L.top() == 10);
    assert(otherList.top() == 10);
    assert(L.traverse(1) == 20);
    assert(otherList.traverse(1) == 20);

    assert(L.traverse(2) == 30);
    assert(otherList.traverse(2) == 30);

    assert(L.last() == 400);
    assert(otherList.last() == 40);
}

void test_assignment_operator() {
    data_structures::linked_list::list L;
    data_structures::linked_list::list otherList;
    L.insert(10);
    L.insert(20);
    L.insert(30);
    otherList = L;

    otherList.insert(40);
    L.insert(400);

    assert(L.top() == 10);
    assert(otherList.top() == 10);
    assert(L.traverse(1) == 20);
    assert(otherList.traverse(1) == 20);

    assert(L.traverse(2) == 30);
    assert(otherList.traverse(2) == 30);

    assert(L.last() == 400);
    assert(otherList.last() == 40);
}
int main() {
	test();
	test_copy_constructor();
	test_assignment_operator();
	return 0;
}