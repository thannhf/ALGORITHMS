#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace ciphers{
	namespace a1z26 {
		std::map<uint8_t, char> a1z26_decrypt_map = {
		    {1, 'a'},  {2, 'b'},  {3, 'c'},  {4, 'd'},  {5, 'e'},  {6, 'f'},  {7, 'g'},
		    {8, 'h'},  {9, 'i'},  {10, 'j'}, {11, 'k'}, {12, 'l'}, {13, 'm'}, {14, 'n'},
		    {15, 'o'}, {16, 'p'}, {17, 'q'}, {18, 'r'}, {19, 's'}, {20, 't'}, {21, 'u'},
		    {22, 'v'}, {23, 'w'}, {24, 'x'}, {25, 'y'}, {26, 'z'},
		};
		
		std::map<char, uint8_t> a1z26_encrypt_map = {
		    {'a', 1},  {'b', 2},  {'c', 3},  {'d', 4},  {'e', 5},  {'f', 6},  {'g', 7},
		    {'h', 8},  {'i', 9},  {'j', 10}, {'k', 11}, {'l', 12}, {'m', 13}, {'n', 14},
		    {'o', 15}, {'p', 16}, {'q', 17}, {'r', 18}, {'s', 19}, {'t', 20}, {'u', 21},
		    {'v', 22}, {'w', 23}, {'x', 24}, {'y', 25}, {'z', 26}
		};
		
		std::string encrypt(std::string text) {
			std::string result;
			std::transform(text.begin(), text.end(), text.begin(), ::tolower);
			std::replace(text.begin(), text.end(), ':', ' ');
			
			for(char letter : text) {
				if(letter != ' ') {
					result += std::to_string(a1z26_encrypt_map[letter]);
					result += "-";
				} else {
					result.pop_back();
					result += ' ';
				}
			}
			result.pop_back();
			return result;
		}
		
		std::string decrypt(const std::string& text, bool bReturnUppercase = false) {
			std::string result;
			std::vector<std::string> word_array;
			std::stringstream sstream(text);
			std::string word;
			while(sstream >> word) {
				word_array.push_back(word);
			}
			
			for(auto& i : word_array) {
				std::replace(i.begin(), i.end(), '-', ' ');
				std::vector<std::string> text_array;
				std::stringstream ss(i);
				std::string res_text;
				while(ss >> res_text) {
					text_array.push_back(res_text);
				}
				
				for(auto& i : text_array){
					result += a1z26_decrypt_map[stoi(i)];
				}
				result += ' ';
			}
			result.pop_back();
			if(bReturnUppercase) {
				std::transform(result.begin(), result.end(), result.begin(), ::toupper);
			}
			return result;
		}
	}
}

static void test() {
	//1st test
	std::string input = "hello world";
	std::string expected = "8-5-12-12-15 23-15-18-12-4";
	std::string output = ciphers::a1z26::encrypt(input);
	
	std::cout << "Input: " << input << std::endl;
	std::cout << "Expected: " << expected << std::endl;
	std::cout << "Output: " << output << std::endl;
	assert(output == expected);
	std::cout << "TEST PASSED" << std::endl;
	
	//2nd test
	input = "12-15-23-5-18-3-1-19-5";
	expected = "lowercase";
	output = ciphers::a1z26::decrypt(input);
	
	std::cout << "Input: " << input << std::endl;
	std::cout << "Expected: " << expected << std::endl;
	std::cout << "Output: " << output << std::endl;
	assert(output == expected);
	std::cout << "TEST PASSED" << std::endl;
	
	//3rd test
	input = "21-16-16-5-18-3-1-19-5";
	expected = "UPPERCASE";
	output = ciphers::a1z26::decrypt(input, true);
	
	std::cout << "Input: " << input << std::endl;
	std::cout << "Expected: " << expected << std::endl;
	std::cout << "Output: " << output << std::endl;
	assert(output == expected);
	std::cout << "TEST PASSED" << std::endl;
}

int main() {
	test();
	return 0;
}