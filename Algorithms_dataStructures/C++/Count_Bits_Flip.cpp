#include <cassert>
#include <iostream>

namespace bit_manipulation{
	namespace count_bits_flip{
		std::uint64_t countBitsFlip(std::int64_t A, std::int64_t B) {
			int count = 0;
			A = A ^ B;
			while(A) {
				A = A & (A - 1);
				count++;
			}
			return count;
		}
	}
}

static void test() {
	assert(bit_manipulation::count_bits_flip::countBitsFlip(10, 20) == 4);
	assert(bit_manipulation::count_bits_flip::countBitsFlip(20, 25) == 3);
	assert(bit_manipulation::count_bits_flip::countBitsFlip(7, 10) == 3);
	assert(bit_manipulation::count_bits_flip::countBitsFlip(17, 25) == 1);
	assert(bit_manipulation::count_bits_flip::countBitsFlip(11, 8) == 2);
	assert(bit_manipulation::count_bits_flip::countBitsFlip(21, 22) == 2);
	assert(bit_manipulation::count_bits_flip::countBitsFlip(7, 786) == 5);
	std::cout << "All test cases successfully passed!" << std::endl;
}

int main() {
	test();
	return 0;
}