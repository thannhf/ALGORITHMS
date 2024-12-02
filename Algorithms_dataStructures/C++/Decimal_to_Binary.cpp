#include <iostream>
void method1(int number){
	int remainder, binary = 0, var = 1;
	do {
		remainder = number % 2;
		number = number / 2;
		binary = binary + (remainder * var);
		var = var * 10;
	} while(number > 0);
	std::cout << "Method 1: " << binary << std::endl;
}
void method2(int number) {
	int num_bits = 0;
	char bit_string[50];
	do{
		bool bit = number & 0x01;
		if(bit) {
			bit_string[num_bits++] = '1';
		} else {
			bit_string[num_bits++] = '0';
		}
		number >>= 1;
	}while(number > 0);
	std::cout << "Method 2: ";
	while(num_bits >= 0) {
		std::cout << bit_string[num_bits--];
	}
	std::cout << std::endl;
}
int main() {
	int number;
	std::cout << "Enter a number: ";
	std::cin >> number;
	method1(number);
	method2(number);
	return 0;
}