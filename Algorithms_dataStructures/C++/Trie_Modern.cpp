#include <iostream>
#include <memory>
#include <string>

class Trie {
	private:
		static constexpr size_t ALPHABETS = 26;
		struct TrieNode {
			std::shared_ptr<TrieNode> character[ALPHABETS]{nullptr};
			bool isEndOfWord{false};
		};
		
		inline static bool hasChildren(std::shared_ptr<TrieNode> node) {
			for(size_t i = 0; i < ALPHABETS; i++) {
				if(node->character[i]) {
					return true;
				}
			}
			return false;
		}
		
		std::shared_ptr<TrieNode> removeWordHelper(const std::string& word, std::shared_ptr<TrieNode> curr, size_t index) {
			if(word.size() == index) {
				if(curr->isEndOfWord) {
					curr->isEndOfWord = false;
				}
				if(hasChildren(curr)) {
					return curr;
				}
				return nullptr;
			}
			size_t idx = word[index] - 'a';
			
			if(!curr->character[idx]) {
				throw std::runtime_error(std::move(std::string("Word not found.")));
			}
			
			curr->character[idx] = removeWordHelper(word, curr->character[idx], index + 1);
			
			if(curr->character[idx] || hasChildren(curr)) {
				return curr;
			}
			return nullptr;
		}
	public:
		Trie() : m_root(std::make_shared<TrieNode>()) {}
		
		void insert(const std::string& word) {
			auto curr = m_root;
			for(char ch : word) {
				size_t index = ch - 'a';
				
				if(!curr->character[index]) {
					curr->character[index] = std::make_shared<TrieNode>();
				}
				curr = curr->character[index];
			}
			curr->isEndOfWord = true;
		}
		
		bool search(const std::string& word) {
			auto curr = m_root;
			for(char ch : word) {
				size_t index = ch - 'a';
				if(!curr->character[index]) {
					return false;
				}
				curr = curr->character[index];
			}
			return curr->isEndOfWord;
		}
		
		void removeWord(const std::string& word) {
			m_root = removeWordHelper(word, m_root, 0);
		}
	private:
		std::shared_ptr<TrieNode> m_root;
};

int main() {
	Trie trie;
	trie.insert("hel");
	trie.insert("hello");
	trie.removeWord("hel");
	std::cout << trie.search("hello") << '\n';
	return 0;
}