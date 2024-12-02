#include <cassert>
#include <iostream>

namespace bit_manipulation {
	namespace count_of_set_bits{
		std::uint64_t countSetBits(std::int64_t n) {
			int count = 0;
			while(n != 0) {
				++count;
				n = (n & (n - 1));
			}
			return count;
		}
	}
}

static void test(){
	// n = 4 return 1
    assert(bit_manipulation::count_of_set_bits::countSetBits(4) == 1);
    // n = 6 return 2
    assert(bit_manipulation::count_of_set_bits::countSetBits(6) == 2);
    // n = 13 return 3
    assert(bit_manipulation::count_of_set_bits::countSetBits(13) == 3);
    // n = 9 return 2
    assert(bit_manipulation::count_of_set_bits::countSetBits(9) == 2);
    // n = 15 return 4
    assert(bit_manipulation::count_of_set_bits::countSetBits(15) == 4);
    // n = 25 return 3
    assert(bit_manipulation::count_of_set_bits::countSetBits(25) == 3);
    // n = 97 return 3
    assert(bit_manipulation::count_of_set_bits::countSetBits(97) == 3);
    // n = 31 return 5
    assert(bit_manipulation::count_of_set_bits::countSetBits(31) == 5);
    std::cout << "All test cases successfully passed!" << std::endl;
}

int main() {
	test();
	return 0;
}