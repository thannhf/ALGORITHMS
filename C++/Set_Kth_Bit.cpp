#include <cassert>
#include <iostream>

namespace bit_manipulation{
	namespace set_kth_bit{
		std::uint64_t setKthBit(std::int64_t N, std::int64_t k) {
			int pos = 1 << k;
			return N | pos;
		}
	}
}

static void test(){
	assert(bit_manipulation::set_kth_bit::setKthBit(10, 2) == 14);
	assert(bit_manipulation::set_kth_bit::setKthBit(25, 1) == 27);
	assert(bit_manipulation::set_kth_bit::setKthBit(400001, 5) == 400033);
	assert(bit_manipulation::set_kth_bit::setKthBit(123, 3) == 123);
	std::cout << "All test cases successfully passed!" << std::endl;
}

int main() {
	test();
	return 0;
}