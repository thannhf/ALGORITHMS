#include <cassert>
#include <iostream>
#include <vector>

namespace bit_manipulation{
	namespace find_non_repeating_integer{
		int64_t find_non_repeating_integer(const std::vector<int>& nums) {
			int _xor = 0;
			for(const int& num: nums) {
				_xor ^= num;
			}
			return _xor;
		}
	}
}

static void test() {
	std::vector<int> nums_one{1, 1, 2, 2, 4, 5, 5};
	std::vector<int> nums_two{203, 3434, 4545, 3434, 4545};
	std::vector<int> nums_three{90, 1, 3, 90, 3};
	
	assert(bit_manipulation::find_non_repeating_integer::find_non_repeating_integer(nums_one) == 4);
	assert(bit_manipulation::find_non_repeating_integer::find_non_repeating_integer(nums_two) == 203);
	assert(bit_manipulation::find_non_repeating_integer::find_non_repeating_integer(nums_three) == 1);
	
	std::cout << "All test cases successfully passed!" << std::endl; 
}

int main() {
	test();
	return 0;
}