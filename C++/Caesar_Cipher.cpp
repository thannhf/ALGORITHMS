#include <iostream>
#include <string>
#include <cassert>

namespace ciphers {
	namespace caesar {
		namespace {
			inline char get_char(const int x) {
				return char(x + 65);
			}
			
			inline int get_value(const char c) {
				return int(c - 65);
			}
		}
		
		std::string encrypt(const std::string &text, const int &shift) {
			std::string encrypted_text = "";
			for(char c : text) {
				int place_value = get_value(c);
				place_value = (place_value + shift) % 26;
				char new_char = get_char(place_value);
				encrypted_text += new_char;
			}
			return encrypted_text;
		}
		
		std::string decrypt(const std::string &text, const int &shift) {
			std::string decrypted_text = "";
			for(char c : text) {
				int place_value = get_value(c);
				place_value = (place_value - shift) % 26;
				if(place_value < 0) {
					place_value = place_value + 26;
				}
				char new_char = get_char(place_value);
				decrypted_text += new_char;
			}
			return decrypted_text;
		}
	}
}

void test() {
	//test 1
	std::string text1 = "ALANTURING";
	std::string encrypted1 = ciphers::caesar::encrypt(text1, 17);
	std::string decrypted1 = ciphers::caesar::decrypt(encrypted1, 17);
	assert(text1 == decrypted1);
	std::cout << "Original text: " << text1;
	std::cout << " , Encrypted text (with shift = 21): " << encrypted1;
	std::cout << " , Decrypted text: " << decrypted1 << std::endl;
	
	//test 2
	std::string text2 = "HELLOWORLD";
	std::string encrypted2 = ciphers::caesar::encrypt(text2, 1729);
	std::string decrypted2 = ciphers::caesar::decrypt(encrypted2, 1729);
	assert(text2 == decrypted2);
	std::cout << "Original text: " << text2;
	std::cout << " , Encrypted text (with shift = 1729) : " << encrypted2;
	std::cout << " , Decrypted text: " << decrypted2 << std::endl;
}

int main() {
	test();
	return 0;
}