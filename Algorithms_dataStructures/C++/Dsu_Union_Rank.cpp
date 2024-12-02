#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class dsu {
	private:
		vector<uint64_t>p;
		vector<uint64_t>depth;
		vector<uint64_t>setSize;
	public:
		explicit dsu(uint64_t n) {
			p.assign(n, 0);
			depth.assign(n, 0);
			setSize.assign(n, 0);
			for(uint64_t i = 0; i < n; i++) {
				p[i] = i;
				depth[i] = 0;
				setSize[i] = 1;
			}
		}
		uint64_t findSet(uint64_t i) {
			while(i != p[i]) {
				i = p[i];
			}
			return i;
		}
		void unionSet(uint64_t i, uint64_t j) {
			if(isSame(i, j)) {
				return;
			}
			uint64_t x = findSet(i);
			uint64_t y = findSet(j);
			if(depth[x] > depth[y]) {
				std::swap(x, y);
			}
			p[x] = y;
			if(depth[x] == depth[y]) {
				depth[y]++;
			}
			setSize[y] += setSize[x];
		}
		bool isSame(uint64_t i, uint64_t j) {
			if(findSet(i) == findSet(j)) {
				return true;
			}
			return false;
		}
		vector<uint64_t> getParents(uint64_t i) {
			vector<uint64_t> ans;
			while(p[i] != i) {
				ans.push_back(i);
				i = p[i];
			}
			ans.push_back(i);
			return ans;
		}
};
static void test1() {
	uint64_t n = 10;
	dsu d(n + 1);
	d.unionSet(2, 1);
	d.unionSet(1, 4);
	d.unionSet(8, 1);
	d.unionSet(3, 5);
	d.unionSet(5, 6);
	d.unionSet(5, 7);
	d.unionSet(9, 10);
	d.unionSet(2, 10);
	vector<uint64_t> ans = {7, 5};
	for(uint64_t i = 0; i < ans.size(); i++) {
		assert(d.getParents(7).at(i) == ans[i]);
	}
	cout << "1st test passed!" << endl;
}
static void test2() {
	uint64_t n = 10;
	dsu d(n + 1);
	d.unionSet(2, 1);
	d.unionSet(1, 4);
	d.unionSet(8, 1);
	d.unionSet(3, 5);
	d.unionSet(5, 6);
	d.unionSet(5, 7);
	d.unionSet(9, 10);
	d.unionSet(2, 10);
	
	vector<uint64_t> ans = {2, 1, 10};
	for(uint64_t i = 0; i < ans.size(); i++) {
		assert(d.getParents(2).at(i) == ans[i]);
	}
	cout << "2nd test passed!" << endl;
}
int main() {
	test1();
	test2();
	
	return 0;
}