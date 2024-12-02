#include <iostream>
int main(void) {
	int valueToConvert = 0;
	int hexArray[8];
	int i = 0;
	char HexValues[] = "0123456789ABCDEF";
	std::cout << "Enter a Decimal Value" << std::endl;
	std::cin >> valueToConvert;
	while(valueToConvert > 15) {
		hexArray[i++] = valueToConvert % 16;
		valueToConvert /= 16;
	}
	hexArray[i] = valueToConvert;
	std::cout << "Hex Value: ";
	while(i >= 0) std::cout << HexValues[hexArray[i--]];
	std::cout << std::endl;
	return 0;
}