#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>

namespace bit_manipulation{
	namespace gray_code{
		std::vector<std::bitset<32>> gray_code_generation(int n){
			std::vector<std::bitset<32>> gray_code = {};
			if(n <= 0) return gray_code;
			int total_codes = 1 << n;
			for(int i = 0; i < total_codes; i++) {
				int gray_num = i ^ (i >> 1);
				gray_code.push_back(std::bitset<32>(gray_num));
			}
			return gray_code;
		}
	}
}

static void test(){
	std::vector<std::bitset<32>> gray_code_negative_1 = {};
	std::vector<std::bitset<32>> gray_code_0 = {};
	std::vector<std::bitset<32>> gray_code_1 = {
		std::bitset<32>(0), std::bitset<32>(1)
	};
	std::vector<std::bitset<32>> gray_code_2 = {
		std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2)
	};
	std::vector<std::bitset<32>> gray_code_3 = {
		std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
		std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4)
	};
	std::vector<std::bitset<32>> gray_code_4 = {
		std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
        std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4),
        std::bitset<32>(12), std::bitset<32>(13), std::bitset<32>(15), std::bitset<32>(14),
        std::bitset<32>(10), std::bitset<32>(11), std::bitset<32>(9), std::bitset<32>(8)
	};
	std::vector<std::bitset<32>> gray_code_5 = {
		std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
        std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4),
        std::bitset<32>(12), std::bitset<32>(13), std::bitset<32>(15), std::bitset<32>(14),
        std::bitset<32>(10), std::bitset<32>(11), std::bitset<32>(9), std::bitset<32>(8),
        std::bitset<32>(24), std::bitset<32>(25), std::bitset<32>(27), std::bitset<32>(26),
        std::bitset<32>(30), std::bitset<32>(31), std::bitset<32>(29), std::bitset<32>(28),
        std::bitset<32>(20), std::bitset<32>(21), std::bitset<32>(23), std::bitset<32>(22),
        std::bitset<32>(18), std::bitset<32>(19), std::bitset<32>(17), std::bitset<32>(16)
	};
	assert(bit_manipulation::gray_code::gray_code_generation(-1) == gray_code_negative_1);
	assert(bit_manipulation::gray_code::gray_code_generation(0) == gray_code_0);
	assert(bit_manipulation::gray_code::gray_code_generation(1) == gray_code_1);
    assert(bit_manipulation::gray_code::gray_code_generation(2) == gray_code_2);
    assert(bit_manipulation::gray_code::gray_code_generation(3) == gray_code_3);
    assert(bit_manipulation::gray_code::gray_code_generation(4) == gray_code_4);
    assert(bit_manipulation::gray_code::gray_code_generation(5) == gray_code_5);
}

int main() {
	test();
	return 0;
}