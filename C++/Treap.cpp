#include<array>
#include<cassert>
#include<cstdint>
#include<iostream>

namespace data_structures{
	namespace treap {
		const int maxNode = 1e5 + 5;
		
		struct Treap{
			int root = 0;
			int treapCnt = 0;
			std::array<int, maxNode> key = {};
			std::array<int, maxNode> priority = {};
			std::array<std::array<int, 2>, maxNode> childs = {{}};
			std::array<int, maxNode> cnt = {};
			std::array<int, maxNode> size = {};
			
			Treap() : treapCnt(1) {
				priority[0] = INT32_MAX;
				size[0] = 0;
			}
			
			void update(int x) {
				size[x] = size[childs[x][0]] + cnt[x] + size[childs[x][1]];
			}
			
			void rotate(int &x, int t) {
				int y = childs[x][t];
				childs[x][t] = childs[y][1 - t];
				childs[y][1 - t] = x;
				update(x);
				update(y);
				x = y;
			}
			
			void _insert(int &x, int k) {
				if(x) {
					if(key[x] == k) {
						cnt[x]++;
					} else {
						int t = (key[x] < k);
						_insert(childs[x][t], k);
						if(priority[childs[x][t]] < priority[x]) {
							rotate(x, t);
						}
					}
				} else {
					x = treapCnt++;
					key[x] = k;
					cnt[x] = 1;
					priority[x] = rand();
					childs[x][0] = childs[x][1] = 0;
				}
				update(x);
			}
			
			void _erase(int &x, int k) {
				if(key[x] == k) {
					if(cnt[x] > 1) {
						cnt[x]--;
					} else {
						if(childs[x][0] == 0 && childs[x][1] == 0) {
							x = 0;
							return;
						}
						int t = (priority[childs[x][0]] > priority[childs[x][1]]);
						rotate(x, t);
						_erase(x, k);
					}
				} else {
					_erase(childs[x][key[x] < k], k);
				}
				update(x);
			}
			
			int _get_k_th(int &x, int k) {
				if(k <= size[childs[x][0]]) {
					return _get_k_th(childs[x][0], k);
				}
				k -= size[childs[x][0]] + cnt[x];
				if(k <= 0) {
					return key[x];
				}
				return _get_k_th(childs[x][1], k);
			}
			
			int _get_rank(int x, int k) {
				if(!x) {
					return 0;
				}
				if(k == key[x]) {
					return size[childs[x][0]] + 1;
				} else if(k < key[x]) {
					return _get_rank(childs[x][0], k);
				} else {
					return size[childs[x][0]] + cnt[x] + _get_rank(childs[x][1], k);
				}
			}
			
			int get_predecessor(int k) {
				int x = root, pre = -1;
				while(x) {
					if(key[x] < k) {
						pre = key[x], 
						x = childs[x][1];
					} else {
						x = childs[x][0];
					}
				}
				return pre;
			}
			
			int get_next(int k) {
				int x = root, next = -1;
				while(x) {
					if(key[x] > k) {
						next = key[x], x = childs[x][0];
					} else {
						x = childs[x][1];
					}
				}
				return next;
			}
			
			void insert(int k) {
				_insert(root, k);
			}
			
			void erase(int k) {
				_erase(root, k);
			}
			
			int get_k_th(int k) {
				return _get_k_th(root, k);
			}
			
			int get_rank(int k) {
				return _get_rank(root, k);
			}
		};
	}
}

static void test() {
	data_structures::treap::Treap mTreap;
	
	mTreap.insert(1);
	mTreap.insert(2);
	mTreap.insert(3);
	assert(mTreap.get_k_th(2) == 2);
	
	mTreap.insert(4);
	mTreap.insert(5);
	mTreap.insert(6);
	assert(mTreap.get_next(4) == 5);
	
	mTreap.insert(7);
	assert(mTreap.get_predecessor(7) == 6);
	
	mTreap.erase(4);
	assert(mTreap.get_k_th(4) == 5);
	assert(mTreap.get_rank(5) == 4);
	
	mTreap.insert(10);
	assert(mTreap.get_rank(10) == 7);
	assert(mTreap.get_predecessor(10) == 7);
	
	std::cout << "All tests have successfully passed!\n";
}

int main() {
	test();
	return 0;
}