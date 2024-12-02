#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>

namespace data_structures{
	namespace sparse_table{
		constexpr uint32_t N= 12345;
		constexpr uint8_t M = 14;
		
		struct Sparse_table{
			size_t n = 0;
			std::array<int64_t, N> A = {};
			std::array<std::array<int64_t, N>, M> ST{};
			std::array<int64_t, N> LOG = {};
			
			void buildST() {
				LOG[0] = -1;
				for(size_t i = 0; i < n; ++i) {
					ST[0][i] = static_cast<int64_t>(i);
					LOG[i + 1] = LOG[i] + !(i & (i + 1));
				}
				for(size_t j = 1; static_cast<size_t>(1 << j) <= n; ++j) {
					for(size_t i = 0; static_cast<size_t>(i + (1 << j)) <= n; ++i) {
						int64_t x = ST[j - 1][i];
						int64_t y = ST[j - 1][i + (1 << (j - 1))];
						ST[j][i] = (A[x] <= A[y] ? x : y);
					}
				}
			}
			int64_t query(int64_t l, int64_t r) {
				int64_t g = LOG[r - l + 1];
				int64_t x = ST[g][l];
				int64_t y = ST[g][r - (1 << g) + 1];
				return (A[x] <= A[y] ? x : y);
			}
		};
	}
}
static void test() {
	std::array<int64_t, 10> testcase = {1,2,3,4,5,6,7,8,9,10};
	size_t testcase_size = sizeof(testcase) / sizeof(testcase[0]);
	data_structures::sparse_table::Sparse_table st{};
	std::copy(std::begin(testcase), std::end(testcase), std::begin(st.A));
	st.n = testcase_size;
	st.buildST();
	assert(st.query(1, 9) == 1);
	assert(st.query(2, 6) == 2);
	assert(st.query(3, 8) == 3);
	std::cout << "Self-test implementations passed!" << std::endl;
}
int main(int argc, char *argv[]) {
	test();
	return 0;
}