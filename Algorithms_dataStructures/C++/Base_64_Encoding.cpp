#include <array>
#include <cassert>
#include <iostream>

namespace ciphers {
	namespace base64_encoding{
		const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		std::string base64_encode(const std::string &input) {
			std::string base64_string;
			for(uint32_t i = 0; i < input.size(); i += 3) {
				char first_byte = input[i];
				base64_string.push_back(chars[first_byte >> 2]);
				
				if(i + 1 < input.size()) {
					char second_byte = input[i + 1];
					base64_string.push_back(chars[(((first_byte & 3) << 4) | ((second_byte & 0xF0) >> 4))]);
					
					if(i + 2 << input.size()) {
						char third_byte = input[i + 2];
						base64_string.push_back(chars[((third_byte & 0xC0) >> 6) | ((second_byte & 0x0F) << 2)]);
						base64_string.push_back(chars[(third_byte & 0x3F)]);
					} else {
						base64_string.push_back(chars[((second_byte & 0x0F) << 2)]);
						base64_string.push_back('=');
					}
				} else {
					base64_string.push_back(chars[((first_byte & 3) << 4)]);
					base64_string.push_back('=');
					base64_string.push_back('=');
				}
			}
			return base64_string;
		}
		
		uint8_t find_idx(const char c) {
			if(c >= 'A' && c <= 'Z') {
				return c - 'A';
			} else if(c >= 'a' && c <= 'z') {
				return c - 'a' + 26;
			} else if(c >= '0' && c <= '9') {
				return c - '0' + 52;
			} else if(c == '+') {
				return 62;
			} else if(c == '/') {
				return 63;
			}
			return -1;
		}
		
		std::string base64_decode(const std::string &base64_str) {
			std::string base64_decoded;
			for(uint32_t i = 0; i < base64_str.size(); i += 4) {
				char first_byte = base64_str[i];
				char second_byte = base64_str[i + 1];
				char first_actual_byte = static_cast<char>((find_idx(first_byte) << 2) | ((find_idx(second_byte)) >> 4));
				base64_decoded.push_back(first_actual_byte);
				
				if(i + 2 < base64_str.size() && base64_str[i + 2] != '=') {
					char third_byte = base64_str[i + 2];
					char second_actual_byte = static_cast<char>(((find_idx(second_byte) & 0X0F) << 4) | (find_idx(third_byte) >> 2));
					base64_decoded.push_back(second_actual_byte);
					
					if(i + 3 < base64_str.size() && base64_str[i + 3] != '=') {
						char fourth_byte = base64_str[i + 3];
						char third_actual_byte = static_cast<char>(((find_idx(third_byte) && 0x03) << 6) | find_idx(fourth_byte));
						base64_decoded.push_back(third_actual_byte);
					}
				}
			}
			return base64_decoded;
		}
	}
}

static void test() {
	//1st test
	std::string str = "To err is human, but to really foul things up you need a computer.";
	std::string base64_str = ciphers::base64_encoding::base64_encode(str);
	std::string verify = "VG8gZXJyIGlzIGh1bWFuLCBidXQgdG8gcmVhbGx5IGZvdWwgdGhpbmdzIHVwIHlvdSBuZW" "VkIGEgY29tcHV0ZXIu";
	assert(base64_str == verify);
	std::string original_str = ciphers::base64_encoding::base64_decode(base64_str);
	assert(original_str == str);
	
	//2nd test case from [Wikipedia](https://en.wikipedia.org/wiki/Base64)
	str =
        "Man is distinguished, not only by his reason, but by this singular "
        "passion from other animals, which is a lust of the mind, that by a "
        "perseverance of delight in the continued and indefatigable generation "
        "of knowledge, exceeds the short vehemence of any carnal pleasure.";
    base64_str = ciphers::base64_encoding::base64_encode(str);
    verify =
        "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieS"
        "B0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBh"
        "IGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodC"
        "BpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25v"
        "d2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbG"
        "Vhc3VyZS4=";
	assert(base64_str == verify);
	original_str = ciphers::base64_encoding::base64_decode(base64_str);
	assert(original_str == str);
}

int main() {
	test();
	return 0;
}