#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>

namespace data_structures{
	namespace tree_234{
		class Node{
			public:
				explicit Node(int64_t item)
					: count(1),
					items({{item, 0, 0}}),
					children({{nullptr, nullptr, nullptr, nullptr}})
					{}
				int8_t GetCount() {
					return count;
				}
				void SetCount(int8_t c) {
					count = c;
				}
				bool IsLeaf() {
					return children[0] == nullptr;
				}
				bool IsFull() {
					return count == 3;
				}
				bool Is2Node() {
					return count == 1;
				}
				bool Is34Node() {
					return count == 2 || count == 3;
				}
				bool Contains(int64_t item) {
					for(int8_t i = 0; i < count; i++) {
						if(item == items[i]) {
							return true;
						}
					}
					return false;
				}
				int8_t GetItemIndex(int64_t item) {
					for(int8_t i = 0; i < count; i++) {
						if(items[i] == item) {
							return i;
						}
					}
					return -1;
				}
				int64_t GetMaxItem() {
					return items[count - 1];
				}
				int64_t GetMinItem() {
					return items[0];
				}
				int64_t GetItem(int8_t index) {
					return items[index];
				}
				void SetItem(int8_t index, int64_t new_item) {
					assert(index >= 0 && index <= 2);
					items[index] = new_item;
				}
				int InsertItem(int item) {
					assert(!IsFull());
					if(Contains(item)) {
						return -1;
					}
					int8_t i = 0;
					for(i = 0; i < count; i++) {
						if(items[i] > item) {
							break;
						}
					}
					InsertItemByIndex(i, item, nullptr, true);
					return i;
				}
				void InsertItemByIndex(int8_t index, int64_t item, Node *with_child, bool to_left = true) {
					assert(count < 3 && index >= 0 && index < 3);
					for(int8_t i = count - 1; i >= index; i--) {
						items[i + 1] = items[i];
					}
					items[index] = item;
					int8_t start_index = to_left ? index : index + 1;
					for(int8_t i = count; i >= start_index; i--) {
						children[i + 1] = children[i];
					}
					children[start_index] = with_child;
					count++;
				}
				Node *RemoveItemByIndex(int8_t index, bool keep_left) {
					assert(index >= 0 && index < count);
					Node *removed_child = keep_left ? children[index + 1] : children[index];
					for(int8_t i = index; i < count - 1; i++) {
						items[i] = items[i + 1];
					}
					for(int8_t i = keep_left ? index + 1 : index; i < count; i++) {
						children[i] = children[i + 1];
					}
					count--;
					return removed_child;
				}
				int8_t GetChildIndex(Node *child) {
					for(int8_t i = 0; i < count + 1; i++) {
						if(children[i] == child) {
							return i;
						}
					}
					return -1;
				}
				Node *GetChild(int8_t index) {
					return children[index];
				}
				void SetChild(int8_t index, Node *child) {
					children[index] = child;
				}
				Node *GetRightmostChild() {
					return children[count];
				}
				Node *GetLeftmostChild() {
					return children[0];
				}
				Node *GetItemLeftChild(int8_t item_index) {
					if(item_index < 0 || item_index > count - 1) {
						return nullptr;
					}
					return children[item_index];
				}
				Node *GetItemRightChild(int8_t item_index) {
					if(item_index < 0 || item_index > count - 1) {
						return nullptr;
					}
					return children[item_index + 1];
				}
				Node *GetNextPossibleChild(int64_t item) {
					int i = 0;
					for(i = 0; i < count; i++) {
						if(items[i] > item) {
							break;
						}
					}
					return children[i];
				}
			private:
				std::array<int64_t, 3> items;
				std::array<Node *, 4> children;
				int8_t count = 0;
		};
		
		class Tree234 {
			public:
				Tree234() = default;
				Tree234(const Tree234 &) = delete;
				Tree234(const Tree234 &&) = delete;
				Tree234 &operator = (const Tree234 &) = delete;
				Tree234 &operator = (const Tree234 &&) = delete;
				~Tree234();
				
				void Insert(int64_t item);
				bool Remove(int64_t item);
				void Traverse();
				void Print(const char *file_name = nullptr);
			private:
				void InsertPreSplit(int64_t item);
				void InsertPostMerge(int64_t item);
				Node *Insert(Node *tree, int64_t item);
				Node *MergeNode(Node *dst_node, Node *node);
				void MergeNodeNotFull(Node *dst_node, Node *node);
				Node *SplitNode(Node *node);
				int64_t GetTreeMaxItem(Node *tree);
				int64_t GetTreeMinItem(Node *tree);
				bool TryLeftRotate(Node *parent, Node *to_child);
				bool TryRightRotate(Node *parent, Node *to_child);
				void RightRotate(Node *parent, int8_t index);
				void LeftRotate(Node *parent, int8_t index);
				bool RemovePreMerge(Node *node, int64_t item);
				Node *Merge(Node *parent, int8_t index);
				void DeleteNode(Node *tree);
				void Traverse(Node *tree);
				void PrintNode(std::ofstream &ofs, Node *node, int64_t parent_index, int64_t index, int8_t parent_child_index);
				Node *root_{nullptr};
		};
		
		Tree234::~Tree234() {
			DeleteNode(root_);
		}
		
		void Tree234::DeleteNode(Node *tree) {
			if(!tree) {
				return;
			}
			for(int8_t i = 0; i <= tree->GetCount(); i++) {
				DeleteNode(tree->GetChild(i));
			}
			delete tree;
		}
		
		void Tree234::Traverse() {
			Traverse(root_);
			std::cout << std::endl;
		}
		
		void Tree234::Traverse(Node *node) {
			if(!node){
				return;
			}
			int8_t i = 0;
			for(i = 0; i < node->GetCount(); i++) {
				Traverse(node->GetChild(i));
				std::cout << node->GetItem(i) << ", ";
			}
			Traverse(node->GetChild(i));
		}
		
		void Tree234::InsertPreSplit(int64_t item) {
			if(!root_) {
				root_ = new Node(item);
				return;
			}
			
			Node *parent = nullptr;
			Node *node = root_;
			
			while(true) {
				if(!node) {
					std::unique_ptr<Node> tmp(new Node(item));
					MergeNodeNotFull(parent, tmp.get());
					return;
				}
				if(node->Contains(item)) {
					return;
				}
				if(node->IsFull()) {
					node = SplitNode(node);
					Node *cur_node = nullptr;
					
					if(item < node->GetItem(0)) {
						cur_node = node->GetChild(0);
					} else {
						cur_node = node->GetChild(1);
					}
					
					if(!parent) {
						root_ = node;
					} else {
						MergeNodeNotFull(parent, node);
					}
					node = cur_node;
				}
				parent = node;
				node = parent->GetNextPossibleChild(item);
			}
		}
		
		void Tree234::InsertPostMerge(int64_t item) {
			if(!root_) {
				root_ = new Node(item);
				return;
			}
			Node *split_node = Insert(root_, item);
			if(split_node) {
				root_ = split_node;
			}
		}
		
		void Tree234::Insert(int64_t item) {
			InsertPreSplit(item);
		}
		
		Node *Tree234::Insert(Node *tree, int64_t item) {
			assert(tree != nullptr);
			std::unique_ptr<Node> split_node;
			
			if(tree->Contains(item)) {
				return nullptr;
			}
			
			Node *next_node = tree->GetNextPossibleChild(item);
			if(next_node) {
				split_node.reset(Insert(next_node, item));
			} else {
				split_node.reset(new Node(item));
			}
			
			if(split_node) {
				return MergeNode(tree, split_node.get());
			}
			return nullptr;
		}
		
		Node *Tree234::MergeNode(Node *dst_node, Node *node) {
			assert(dst_node != nullptr && node != nullptr);
			if(!dst_node->IsFull()) {
				MergeNodeNotFull(dst_node, node);
				return nullptr;
			}
			dst_node = SplitNode(dst_node);
			
			if(node->GetItem(0) < dst_node->GetItem(0)) {
				MergeNodeNotFull(dst_node->GetChild(0), node);
			} else {
				MergeNodeNotFull(dst_node->GetChild(1), node);
			}
			return dst_node;
		}
		
		void Tree234::MergeNodeNotFull(Node *dst_node, Node *node) {
			assert(dst_node && node && !dst_node->IsFull() && node->Is2Node());
			int8_t i = dst_node->InsertItem(node->GetItem(0));
			
			dst_node->SetChild(i, node->GetChild(0));
			dst_node->SetChild(i + 1, node->GetChild(1));
		}
		
		Node *Tree234::SplitNode(Node *node) {
			assert(node->GetCount() == 3);
			Node *left = node;
			Node *right = new Node(node->GetItem(2));
			right->SetChild(0, node->GetChild(2));
			right->SetChild(1, node->GetChild(3));
			
			Node *parent = new Node(node->GetItem(1));
			parent->SetChild(0, left);
			parent->SetChild(1, right);
			left->SetCount(1);
			return parent;
		}
		
		bool Tree234::TryLeftRotate(Node *parent, Node *to_child) {
			int to_child_index = parent->GetChildIndex(to_child);
			if(to_child_index >= parent->GetCount()) {
				return false;
			}
			Node *right_sibling = parent->GetChild(to_child_index + 1);
			if(right_sibling->Is2Node()) {
				return false;
			}
			LeftRotate(parent, to_child_index);
			return true;
		}
		
		bool Tree234::TryRightRotate(Node *parent, Node *to_child) {
			int8_t to_child_index = parent->GetChildIndex(to_child);
			if(to_child_index <= 0) {
				return false;
			}
			Node *left_sibling = parent->GetChild(to_child_index - 1);
			if(left_sibling->Is2Node()) {
				return false;
			}
			RightRotate(parent, to_child_index - 1);
			return true;
		}
		
		void Tree234::RightRotate(Node *parent, int8_t index) {
			Node *left = parent->GetItemLeftChild(index);
			Node *right = parent->GetItemRightChild(index);
			
			assert(left && left->Is34Node());
			assert(right && right->Is2Node());
			
			right->InsertItemByIndex(0, parent->GetItem(index), left->GetRightmostChild(), true);
			parent->SetItem(index, left->GetMaxItem());
			left->RemoveItemByIndex(left->GetCount() - 1, true);
		}
		
		void Tree234::LeftRotate(Node *parent, int8_t index) {
			Node *left = parent->GetItemLeftChild(index);
			Node *right = parent->GetItemRightChild(index);
			
			assert(right && right->Is34Node());
			assert(left && left->Is2Node());
			
			left->InsertItemByIndex(left->GetCount(), parent->GetItem(index), right->GetLeftmostChild(), false);
			parent->SetItem(index, right->GetMinItem());
			right->RemoveItemByIndex(0, false);
		}
		
		Node *Tree234::Merge(Node *parent, int8_t index) {
			assert(parent);
			
			Node *left_child = parent->GetItemLeftChild(index);
			Node *right_child = parent->GetItemRightChild(index);
			
			assert(left_child->Is2Node() && right_child->Is2Node());
			int64_t item = parent->GetItem(index);
			
			left_child->SetItem(1, item);
			left_child->SetItem(2, right_child->GetItem(0));
			left_child->SetChild(2, right_child->GetChild(0));
			left_child->SetChild(3, right_child->GetChild(1));
			
			left_child->SetCount(3);
			parent->RemoveItemByIndex(index, true);
			
			delete right_child;
			return left_child;
		}
		
		bool Tree234::Remove(int64_t item) {
			return RemovePreMerge(root_, item);
		}
		
		bool Tree234::RemovePreMerge(Node *node, int64_t item) {
			while(node) {
				if(node->IsLeaf()) {
					if(node->Contains(item)) {
						if(node->Is2Node()) {
							delete node;
							root_ = nullptr;
						} else {
							node->RemoveItemByIndex(node->GetItemIndex(item), true);
						}
						return true;
					}
					return false;
				}
				
				if(node->Contains(item)) {
					int8_t index = node->GetItemIndex(item);
					Node *left_child = node->GetItemLeftChild(index);
					Node *right_child = node->GetItemRightChild(index);
					assert(left_child && right_child);
					
					if(left_child->Is2Node() && right_child->Is2Node()) {
						if(node->Is2Node()) {
							Node *new_root = Merge(node, index);
							delete root_;
							root_ = new_root;
							node = root_;
							continue;
						}
						
						do{
							if(index > 0) {
								Node *left_sibling = node->GetItemLeftChild(index - 1);
								if(left_sibling->Is34Node()) {
									RightRotate(node, index - 1);
									break;
								}
							}
							if(index < node->GetCount() - 1) {
								Node *right_sibling = node->GetItemRightChild(index + 1);
								if(right_sibling->Is34Node()) {
									LeftRotate(node, index + 1);
									break;
								}
							}
							if(index > 0) {
								Merge(node, index - 1);
								break;
							}
							Merge(node, index + 1);
						} while(false);
					}
					
					left_child = node->GetItemLeftChild(index);
					right_child = node->GetItemRightChild(index);
					
					if(left_child->Is34Node()) {
						int64_t predecessor_item = GetTreeMaxItem(left_child);
						node->SetItem(node->GetItemIndex(item), predecessor_item);
						node = left_child;
						item = predecessor_item;
						continue;
					}
					
					if(right_child->Is34Node()) {
						int64_t successor_item = GetTreeMinItem(right_child);
						node->SetItem(node->GetItemIndex(item), successor_item);
						node = right_child;
						item = successor_item;
						continue;
					}
				}
				Node *next_node = node->GetNextPossibleChild(item);
				
				if(next_node->Is34Node()) {
					node = next_node;
					continue;
				}
				if(TryRightRotate(node, next_node)) {
					node = next_node;
					continue;
				}
				if(TryLeftRotate(node, next_node)) {
					node = next_node;
					continue;
				}
				
				int8_t child_index = node->GetChildIndex(next_node);
				if(child_index > 0) {
					node = Merge(node, child_index - 1);
				} else {
					node = Merge(node, child_index);
				}
			}
			return false;
		}
		
		int64_t Tree234::GetTreeMaxItem(Node *tree) {
			assert(tree);
			int64_t max = 0;
			while(tree) {
				max = tree->GetMaxItem();
				tree = tree->GetRightmostChild();
			}
			return max;
		}
		
		int64_t Tree234::GetTreeMinItem(Node *tree) {
			assert(tree);
			int64_t min = 0;
			
			while(tree) {
				min = tree->GetMinItem();
				tree = tree->GetLeftmostChild();
			}
			return min;
		}
		
		void Tree234::Print(const char *file_name) {
			if(!file_name) {
				file_name = "out.dot";
			}
			std::ofstream ofs;
			ofs.open(file_name);
			if(!ofs) {
				std::cout << "create tree dot file failed, " << file_name << std::endl;
				return;
			}
			ofs << "digraph G {\n";
			ofs << "node [shape=record]\n";
			int64_t index = 0;
			
			struct NodeInfo{
				Node *node;
				int64_t index;
			};
			std::queue<NodeInfo> q;
			if(root_) {
				PrintNode(ofs, root_, -1, index, 0);
				NodeInfo ni{};
				ni.node = root_;
				ni.index = index;
				q.push(ni);
				
				while(!q.empty()) {
					NodeInfo node_info = q.front();
					q.pop();
					assert(node_info.node->GetCount() > 0);
					
					if(!node_info.node->IsLeaf()) {
						if(node_info.node->GetCount() > 0) {
							PrintNode(ofs, node_info.node->GetChild(0), node_info.index, ++index, 0);
							ni.node = node_info.node->GetChild(0);
							ni.index = index;
							q.push(ni);
							
							PrintNode(ofs, node_info.node->GetChild(1), node_info.index, ++index, 1);
							ni.node = node_info.node->GetChild(1);
							ni.index = index;
							q.push(ni);
						}
						
						if(node_info.node->GetCount() > 1) {
							PrintNode(ofs, node_info.node->GetChild(2), node_info.index, ++index, 2);
							ni.node = node_info.node->GetChild(2);
							ni.index = index;
							q.push(ni);
						}
						
						if(node_info.node->GetCount() > 2) {
							PrintNode(ofs, node_info.node->GetChild(3), node_info.index, ++index, 3);
							ni.node = node_info.node->GetChild(3);
							ni.index = index;
							q.push(ni);
						}
					}
				}
			}
			ofs << "}\n";
			ofs.close();
		}
		
		void Tree234::PrintNode(std::ofstream &ofs, Node *node, int64_t parent_index, int64_t index, int8_t parent_child_index) {
			assert(node);
			switch(node->GetCount()) {
				case 1:
					ofs << "node_" << index << "[label=\"<f0> " << node->GetItem(0) << "\"]\n";
					break;
				case 2:
					ofs << "node_" << index << "[label=\"<f0> " << node->GetItem(0) << " | <f1> " << node->GetItem(1) << "\"]\n";
					break;
				case 3:
					ofs << "node_" << index << " [label=\"<f0> " << node->GetItem(0) << " | <f1> " << node->GetItem(1) << "| <f2> " << node->GetItem(2) << "\"]\n";
					break;
				default:
					break;
			}
			if(parent_index >= 0) {
				ofs << "node_" << parent_index << ":f" << (parent_child_index == 0 ? 0 : parent_child_index - 1) << ":" << (parent_child_index == 0 ? "sw" : "se") << " -> node_" << index << "\n";
			}
		}
	}
};

static void test1() {
	std::array<int16_t, 13> arr = {3, 1, 5, 4, 2, 9, 10, 8, 7, 6, 16, 13, 14};
	data_structures::tree_234::Tree234 tree;
	for(auto i : arr) {
		tree.Insert(i);
	}
	tree.Remove(5);
	tree.Print();
}

static void test2(int64_t n) {
	data_structures::tree_234::Tree234 tree;
	for(int64_t i = 0; i < n; i++) {
		tree.Insert(i);
	}
	tree.Traverse();
	tree.Print((std::to_string(n) + ".dot").c_str());
}

int main(int argc, char *argv[]) {
	if(argc < 2){
		test1();
	} else {
		test2(std::stoi(argv[1]));
	}
	return 0;
}