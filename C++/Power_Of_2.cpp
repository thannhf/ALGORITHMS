#include <cassert>
#include <iostream>

namespace bit_manipulation{
	bool isPowerOfTwo(std::int64_t n) {
		return n > 0 && !(n & n - 1);
	}
}

static void test() {
	assert(bit_manipulation::isPowerOfTwo(4) == true);
	assert(bit_manipulation::isPowerOfTwo(6) == false);
	assert(bit_manipulation::isPowerOfTwo(13) == false);
	assert(bit_manipulation::isPowerOfTwo(64) == true);
	assert(bit_manipulation::isPowerOfTwo(15) == false);
	assert(bit_manipulation::isPowerOfTwo(32) == true);
	assert(bit_manipulation::isPowerOfTwo(97) == false);
	assert(bit_manipulation::isPowerOfTwo(1024) == true);
	std::cout << "All test cases successfully passed!" << std::endl;
}

int main() {
	test();
	return 0;
}