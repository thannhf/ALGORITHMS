#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace data_structures{
	class trie{
		private:
			static constexpr uint8_t NUM_CHARS = 26;
			std::array<std::shared_ptr<trie>, NUM_CHARS << 1> arr;
			bool isEndofWord = false;
			
			uint8_t char_to_int(const char& ch) const {
				if(ch >= 'A' && ch <= 'Z') {
					return ch - 'A';
				} else if(ch >= 'a' && ch <= 'z') {
					return ch - 'a' + NUM_CHARS;
				}
				std::cerr << "Invalid character present. Exiting...";
				std::exit(EXIT_FAILURE);
				return 0;
			}
			
			bool search(const std::shared_ptr<trie>& root, const std::string& str, int index) {
				if(index == str.length()) {
					if(!root->isEndofWord) {
						return false;
					}
					return true;
				}
				
				int j = char_to_int(str[index]);
				if(!root->arr[j]) {
					return false;
				}
				return search(root->arr[j], str, index + 1);
			}
		public:
			trie() = default;
			void insert(const std::string& str) {
				std::shared_ptr<trie> root(nullptr);
				
				for(const char& ch : str) {
					int j = char_to_int(ch);
					if(root) {
						if(root->arr[j]) {
							root = root->arr[j];
						} else {
							std::shared_ptr<trie> temp(new trie());
							root->arr[j] = temp;
							root = temp;
						}
					} else if(arr[j]) {
						root = arr[j];
					} else {
						std::shared_ptr<trie> temp(new trie());
						arr[j] = temp;
						root = temp;
					}
				}
				root->isEndofWord = true;
			}
			
			bool search(const std::string& str, int index) {
				if(index == str.length()) {
					if(!isEndofWord) {
						return false;
					}
					return true;
				}
				int j = char_to_int(str[index]);
				if(!arr[j]) {
					return false;
				}
				return search(arr[j], str, index + 1);
			}
			
			bool deleteString(const std::string& str, int index) {
				if(index == str.length()) {
					if(!isEndofWord) {
						return false;
					}
					isEndofWord = false;
					return true;
				}
				int j = char_to_int(str[index]);
				if(!arr[j]) {
					return false;
				}
				bool var = deleteString(str, index + 1);
				if(var) {
					arr[j].reset();
					if(isEndofWord) {
						return false;
					} else {
						int i = 0;
						for(i = 0; i < NUM_CHARS; i++) {
							if(arr[i]) {
								return false;
							}
						}
						return true;
					}
				}
				std::cout << __func__ << ":" << __LINE__ << "Should not reach this line\n";
				return false;
			}
	};
}

static void test() {
	data_structures::trie root;
	root.insert("Hello");
	root.insert("World");
	
	assert(!root.search("hello", 0));
	std::cout << "hello - " << root.search("hello", 0) << "\n";
	
	assert(root.search("Hello", 0));
	std::cout << "Hello - " << root.search("Hello", 0) << "\n";
	
	assert(!root.search("Word", 0));
	std::cout << "Word - " << root.search("Word", 0) << "\n";
	
	assert(root.search("World", 0));
	std::cout << "World - " << root.search("World", 0) << "\n";
}

int main() {
	test();
	return 0;
}