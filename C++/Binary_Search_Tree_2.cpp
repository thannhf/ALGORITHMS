#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <class T>
class binary_search_tree{
	private:
		struct bst_node {
			T value;
			std::unique_ptr<bst_node> left;
			std::unique_ptr<bst_node> right;
			explicit bst_node(T _value) {
				value = _value;
				left = nullptr;
				right = nullptr;
			}
		};
		std::unique_ptr<bst_node> root_;
		std::size_t size_ = 0;
		bool find_max(std::unique_ptr<bst_node>& node, T& ret_value) {
			if(!node) {
				return false;
			} else if(!node->right) {
				ret_value = node->value;
				return true;
			}
			return find_max(node->right, ret_value);
		}
		bool find_min(std::unique_ptr<bst_node>& node, T& ret_value) {
			if(!node) {
				return false;
			} else if(!node->left) {
				ret_value = node->value;
				return true;
			}
			return find_min(node->left, ret_value);
		}
		bool insert(std::unique_ptr<bst_node>& node, T new_value) {
			if(root_ == node && !root_) {
				root_;
				std::unique_ptr<bst_node>(new bst_node(new_value));
				return true;
			}
			if(new_value < node->value) {
				if(!node->left) {
					node->left = std::unique_ptr<bst_node>(new bst_node(new_value));
					return true;
				} else {
					return insert(node->left, new_value);
				}
			} else if(new_value > node->value) {
				if(!node->right) {
					node->right = std::unique_ptr<bst_node>(new bst_node(new_value));
					return true;
				} else {
					return insert(node->right, new_value);
				}
			} else {
				return false;
			}
		}
		bool remove(std::unique_ptr<bst_node>& parent, std::unique_ptr<bst_node>& node, T rm_value) {
			if(!node) {
				return false;
			}
			if(node->value == rm_value) {
				if(node->left && node->right) {
					T successor_node_value{};
					find_max(node->left, successor_node_value);
					remove(root_, root_, successor_node_value);
					node->value = successor_node_value;
					return false;
				} else if(node->left || node->right) {
					std::unique_ptr<bst_node>& non_null = (node->left ? node->left : node->right);
					if(node == root_) {
						root_ = std::move(non_null);
					} else if(rm_value < parent->value) {
						parent->left = std::move(non_null);
					} else {
						parent->right = std::move(non_null);
					}
					return true;
				} else {
					if(node == root_) {
						root_.reset(nullptr);
					} else if(rm_value < parent->value) {
						parent->left.reset(nullptr);
					} else {
						parent->right.reset(nullptr);
					}
					return true;
				}
			} else if(rm_value < node->value) {
				return remove(node, node->left, rm_value);
			} else {
				return remove(node, node->right, rm_value);
			}
		}
		bool contains(std::unique_ptr<bst_node>& node, T value) {
			if(!node) {
				return false;
			}
			if(value < node->value) {
				return contains(node->left, value);
			} else if(value > node->value) {
				return contains(node->right, value);
			} else {
				return true;
			}
		}
		void traverse_inorder(std::function<void(T)> callback, std::unique_ptr<bst_node>& node) {
			if(!node) {
				return;
			}
			traverse_inorder(callback, node->left);
			callback(node->value);
			traverse_inorder(callback, node->right);
		}
		void traverse_preorder(std::function<void(T)> callback, std::unique_ptr<bst_node>& node) {
			if(!node) {
				return;
			}
			callback(node->value);
			traverse_preorder(callback, node->left);
			traverse_preorder(callback, node->right);
		}
		void traverse_postorder(std::function<void(T)> callback, std::unique_ptr<bst_node>& node) {
			if(!node) {
				return;
			}
			traverse_postorder(callback, node->left);
			traverse_postorder(callback, node->right);
			callback(node->value);
		}
	public:
		binary_search_tree() {
			root_ = nullptr;
			size_ = 0;
		}
		bool insert(T new_value) {
			bool result = insert(root_, new_value);
			if(result) {
				size_++;
			}
			return result;
		}
		bool remove(T rm_value) {
			bool result = remove(root_, root_, rm_value);
			if(result) {
				size_--;
			}
			return result;
		}
		bool contains(T value) {
			return contains(root_, value);
		}
		bool find_min(T& ret_value) {
			return find_min(root_, ret_value);
		}
		bool find_max(T& ret_value) {
			return find_max(root_, ret_value);
		}
		std::size_t size() {
			return size_;
		}
		std::vector<T> get_elements_inorder() {
			std::vector<T> result;
			traverse_inorder([&](T node_value) {
				result.push_back(node_value);
			}, root_);
			return result;
		}
		std::vector<T> get_elements_preorder() {
			std::vector<T> result;
			traverse_preorder([&](T node_value) {
				result.push_back(node_value);
			}, root_);
			return result;
		}
		std::vector<T> get_elements_postorder() {
			std::vector<T> result;
			traverse_postorder([&](T node_value) {
				result.push_back(node_value);
			}, root_);
			return result;
		}
			
};
static void test_insert() {
	std::cout << "Testing BST insert...";
	binary_search_tree<int> tree;
	bool res = tree.insert(5);
	int min = -1, max = -1;
	assert(res);
	assert(tree.find_max(max));
	assert(tree.find_min(min));
	assert(max == 5);
	assert(min == 5);
	assert(tree.size() == 1);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	assert(tree.find_max(max));
	assert(tree.find_min(min));
	assert(max == 6);
	assert(min == 3);
	assert(tree.size() == 4);
	std::cout << "ok" << std::endl;
}
static void test_remove() {
	std::cout << "Testing BST remove...";
	binary_search_tree<int> tree;
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	
	bool res = tree.remove(5);
	int min = -1, max = -1;
	assert(res);
	assert(tree.find_max(max));
	assert(tree.find_min(min));
	assert(max == 6);
	assert(min == 3);
	assert(tree.size() == 3);
	assert(tree.contains(5) == false);
	
	tree.remove(4);
	tree.remove(3);
	tree.remove(6);
	assert(tree.size() == 0);
	assert(tree.contains(6) == false);
	
	bool fail_res = tree.remove(5);
	assert(!fail_res);
	assert(tree.size() == 0);
	
	std::cout << "ok" << std::endl;
}
static void test_contains() {
	std::cout << "Testing BST contains...";
	
	binary_search_tree<int> tree;
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	
	assert(tree.contains(5));
	assert(tree.contains(4));
	assert(tree.contains(3));
	assert(tree.contains(6));
	assert(!tree.contains(999));
	
	std::cout << "ok" << std::endl;
}
static void test_find_min() {
	std::cout << "Testing BST find_min...";
	int min = 0;
	binary_search_tree<int> tree;
	assert(!tree.find_min(min));
	
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	
	assert(tree.find_min(min));
	assert(min == 3);
	
	std::cout << "ok" << std::endl;
}
static void test_find_max() {
	std::cout << "Testing BST find_max...";
	int max = 0;
	binary_search_tree<int> tree;
	assert(!tree.find_max(max));
	
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	
	assert(tree.find_max(max));
	assert(max == 6);
	
	std::cout << "ok" << std::endl;
}
static void test_get_elements_inorder() {
	std::cout << "Testing BST get_elements_inorder...";
	binary_search_tree<int> tree;
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	
	std::vector<int> expected = {3, 4, 5, 6};
	std::vector<int> actual = tree.get_elements_inorder();
	assert(actual == expected);
	
	std::cout << "ok" << std::endl;
}

static void test_get_elements_preorder(){
	std::cout << "Testing BST get_elements_preorder...";
	
	binary_search_tree<int> tree;
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	
	std::vector<int> expected = {5, 4, 3, 6};
	std::vector<int> actual = tree.get_elements_preorder();
	assert(actual == expected);
	
	std::cout << "ok" << std::endl;
}
static void test_get_elements_postorder() {
	std::cout << "Testing BST get_elements_postorder...";
	
	binary_search_tree<int> tree;
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	
	std::vector<int> expected = {3, 4, 6, 5};
	std::vector<int> actual = tree.get_elements_postorder();
	assert(actual == expected);
	
	std::cout << "ok" << std::endl;
}
int main() {
	test_insert();
	test_remove();
	test_contains();
	test_find_max();
	test_find_min();
	test_get_elements_inorder();
	test_get_elements_preorder();
	test_get_elements_postorder();
}