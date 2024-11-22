#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

namespace data_structures{
	template <class T>
	class SegmentTree {
		private:
			const T ID = 0;
			std::vector<T> t;
			int size = 0;
		private:
			T comb(T x, T y) {
				return x + y;
			}
			int mid(int l, int r) {
				return l + (r - l) / 2;
			}
			void update(int i, int l, int r, int pos, T val) {
				if(l == r) t[i] = val;
				else {
					int m = mid(l, r);
					if(pos <= m) update(i * 2, l, m, pos, val);
					else update(i * 2 + 1, m + 1, r, pos, val);
					t[i] = comb(t[i * 2], t[i * 2 + 1]);
				}
			}
			T range_comb(int i, int l, int r, int tl, int tr) {
				if(l == tl && r == tr) return t[i];
				if(tl > tr) return 0;
				int m = mid(l, r);
				return comb(range_comb(i * 2, l, m, tl, std::min(tr, m)), range_comb(i * 2 + 1, m + 1, r, std::max(tl, m + 1), tr));
			}
		public:
			SegmentTree(int n) : t(n * 4, ID), size(n){}
			void update(int pos, T val) {
				update(1, 1, size, pos, val);
			}
			T range_comb(int l, int r) {
				return range_comb(1, 1, size, l, r);
			}
	};
}
static void test() {
    data_structures::SegmentTree<int> t(5);
    t.update(1, 1);
    t.update(2, 2);
    t.update(3, 3);
    t.update(4, 4);
    t.update(5, 5);
    assert(t.range_comb(1, 3) == 6); // 1 + 2 + 3 = 6
    t.update(1, 3);
    assert(t.range_comb(1, 3) == 8); // 3 + 2 + 3 = 8

    std::cout << "All tests have successfully passed!\n";
}
int main() {
	test();
	return 0;
}