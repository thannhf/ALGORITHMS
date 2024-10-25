#include <cassert>
#include <iostream>

namespace bit_manipulation{
	uint64_t next_higher_number(uint64_t x) {
		uint64_t rightOne = 0;
		uint64_t nextHigherOneBit = 0;
		uint64_t rightOnesPattern = 0;
		uint64_t next = 0;
		
		if(x) {
			rightOne = x & -static_cast<signed>(x);
			nextHigherOneBit = x + rightOne;
			rightOnesPattern = x ^ nextHigherOneBit;
			rightOnesPattern = (rightOnesPattern) / rightOne;
			rightOnesPattern >>= 2;
			next = nextHigherOneBit | rightOnesPattern;
		}
		return next;
	}
}

static void test() {
	assert(bit_manipulation::next_higher_number(4) == 8);
	assert(bit_manipulation::next_higher_number(6) == 9);
	assert(bit_manipulation::next_higher_number(13) == 14);
	assert(bit_manipulation::next_higher_number(64) == 128);
	assert(bit_manipulation::next_higher_number(15) == 23);
	assert(bit_manipulation::next_higher_number(32) == 64);
	assert(bit_manipulation::next_higher_number(97) == 98);
	assert(bit_manipulation::next_higher_number(1024) == 2048);
	std::cout << "All test cases have successfully passed!" << std::endl;
}

int main() {
	test();
	return 0;
}