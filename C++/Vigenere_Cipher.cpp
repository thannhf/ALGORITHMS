#include <iostream>
#include <string>
#include <cassert>

namespace ciphers {
	namespace vigenere{
		namespace {
			inline char get_char(const int x) {
				return char(x + 65);
			}
			inline int get_value(const char c) {
				return int(c - 65);
			}
		}
		std::string encrypt(const std::string &text, const std::string &key) {
			std::string encrypted_text = "";
			for(size_t i = 0, j = 0; i < text.length(); i++, j = (j + 1) % key.length()) {
				int place_value_text = get_value(text[i]);
				int place_value_key = get_value(key[j]);
				place_value_text = (place_value_text + place_value_key) % 26;
				char encrypted_char = get_char(place_value_text);
				encrypted_text += encrypted_char;
			}
			return encrypted_text;
		}
		std::string decrypt(const std::string &text, const std::string &key) {
			std::string decrypted_text = "";
			for(size_t i = 0, j = 0; i < text.length(); i++, j = (j + 1) % key.length()) {
				int place_value_text = get_value(text[i]);
				int place_value_key = get_value(key[j]);
				place_value_text = (place_value_text - place_value_key + 26) % 26;
				char decrypted_char = get_char(place_value_text);
				decrypted_text += decrypted_char;
			}
			return decrypted_text;
		}
	}
}

void test() {
	//Test 1
	std::string text1 = "NIKOLATESLA";
	std::string encrypted1 = ciphers::vigenere::encrypt(text1, "TESLA");
	std::string decrypted1 = ciphers::vigenere::decrypt(encrypted1, "TESLA");
	assert(text1 == decrypted1);
	
	std::cout << "Original text: " << text1;
	std::cout << " , Encrypted text (with key = TESLA) : " << encrypted1;
	std::cout << " , Decrypted text : " << decrypted1 << std::endl;
	
	//test 2
	std::string text2 = "GOOGLEIT";
	std::string encrypted2 = ciphers::vigenere::encrypt(text2, "REALLY");
	std::string decrypted2 = ciphers::vigenere::decrypt(encrypted2, "REALLY");
	assert(text2 == decrypted2);
	
	std::cout << "Original text: " << text2;
	std::cout << " , Encrypted text (with key = REALLY): " << encrypted2;
	std::cout << " , Decrypted text : " << decrypted2 << std::endl;
}

int main() {
	test();
	return 0;
}