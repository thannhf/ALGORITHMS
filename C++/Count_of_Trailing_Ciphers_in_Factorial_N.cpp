#include <cassert>
#include <iostream>

namespace bit_manipulation{
	namespace count_of_trailing_ciphers_in_factorial_n{
		uint64_t numberOfCiphersInFactorialN(uint64_t n){
			uint64_t count = 0;
			for(uint64_t i = 5; n / i >= 1; i *= 5) {
				count += static_cast<uint64_t>(n) / i;
			}
			return count;
		}
	}
}

static void test() {
	//1st test
	std::cout << "1st test ";
	assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::numberOfCiphersInFactorialN(395) == 97);
	std::cout << "passed" << std::endl;
	
	//2nd test
	std::cout << "2nd test ";
	assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::numberOfCiphersInFactorialN(977) == 242);
	std::cout << "passed" << std::endl;
	
	//3rd test
	std::cout << "3rd test ";
	assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::numberOfCiphersInFactorialN(871) == 215);
	std::cout << "passed" << std::endl;
	
	//4th test
	std::cout << "4th test ";
	assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::numberOfCiphersInFactorialN(239) == 57);
	std::cout << "passed" << std::endl;
	
	//5th test
	std::cout << "5th test ";
	assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::numberOfCiphersInFactorialN(0) == 0);
	std::cout << "passed" << std::endl;
}

int main() {
	test();
	return 0;
}