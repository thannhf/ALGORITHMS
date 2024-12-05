#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

namespace data_structures {
	namespace trie_using_hashmap{
		class Trie{
			private:
				struct Node{
					std::unordered_map<char16_t, std::shared_ptr<Node>> children;
					bool word_end = false;
				};
				
				std::shared_ptr<Node> root_node = std::make_shared<Node>();
			public:
				Trie() = default;
				
				void insert(const std::string& word) {
					std::shared_ptr<Node> curr = root_node;
					for(char ch : word) {
						if(curr->children.find(ch) == curr->children.end()) {
							curr->children[ch] = std::make_shared<Node>();
						}
						curr = curr->children[ch];
					}
					
					if(!curr->word_end && curr != root_node) {
						curr->word_end = true;
					}
				}
				
				bool search(const std::string& word) {
					std::shared_ptr<Node> curr = root_node;
					for(char ch : word) {
						if(curr->children.find(ch) == curr->children.end()) {
							return false;
						}
						curr = curr->children[ch];
						if(!curr) {
							return false;
						}
					}
					
					if(curr->word_end) {
						return true;
					} else {
						return false;
					}
				}
				
				bool startwith(const std::string& prefix) {
					std::shared_ptr<Node> curr = root_node;
					for(char ch : prefix) {
						if(curr->children.find(ch) == curr->children.end()) {
							return false;
						}
						curr = curr->children[ch];
					}
					return true;
				}
				
				void delete_word(std::string word) {
					std::shared_ptr<Node> curr = root_node;
					std::stack<std::shared_ptr<Node>> nodes;
					int cnt = 0;
					for(char ch : word) {
						if(curr->children.find(ch) == curr->children.end()) {
							return;
						}
						if(curr->word_end) {
							cnt++;
						}
						
						nodes.push(curr->children[ch]);
						curr = curr->children[ch];
					}
					
					if(nodes.top()->word_end) {
						nodes.top()->word_end = false;
					}
					
					while(!(nodes.top()->word_end) && nodes.top()->children.empty()) {
						nodes.pop();
						nodes.top()->children.erase(word.back());
						word.pop_back();
					}
				}
				
				std::vector<std::string> get_all_words(std::vector<std::string> results, const std::shared_ptr<Node>& element, std::string prefix) {
					if(element->word_end) {
						results.push_back(prefix);
					}
					if(element->children.empty()) {
						return results;
					}
					for(auto const& x : element->children) {
						std::string key = "";
						key = x.first;
						prefix += key;
						results = get_all_words(results, element->children[x.first], prefix);
						prefix.pop_back();
					}
					return results;
				}
				
				std::vector<std::string> predict_words(const std::string& prefix) {
					std::vector<std::string> result;
					std::shared_ptr<Node> curr = root_node;
					
					for(char ch : prefix) {
						if(curr->children.find(ch) == curr->children.end()) {
							return result;
						}
						curr = curr->children[ch];
					}
					
					if(curr->word_end && curr->children.empty()) {
						result.push_back(prefix);
						return result;
					}
					
					result = get_all_words(result, curr, prefix);
					return result;
				}
		};
	}
}

static void test() {
	data_structures::trie_using_hashmap::Trie obj;
	obj.insert("app");
	obj.insert("abscond");
	obj.insert("about");
	obj.insert("apps");
	obj.insert("apen");
	obj.insert("apples");
	obj.insert("apple");
	obj.insert("approach");
	obj.insert("bus");
	obj.insert("buses");
	obj.insert("Apple");
	obj.insert("Bounce");
	
	assert(!obj.search("appy"));
	std::cout << "appy is not a word in trie" << std::endl;
	
	assert(!obj.search("car"));
	std::cout << "car is not a word in trie" << std::endl;
	
	assert(obj.search("app"));
    assert(obj.search("apple"));
    assert(obj.search("apples"));
    assert(obj.search("apps"));
    assert(obj.search("apen"));
    assert(obj.search("approach"));
    assert(obj.search("about"));
    assert(obj.search("abscond"));
    assert(obj.search("bus"));
    assert(obj.search("buses"));
    assert(obj.search("Bounce"));
    assert(obj.search("Apple"));
    
    std::cout << "All the Inserted words are present in the trie" << std::endl;
    
    assert(!obj.startwith("approachs"));
    assert(obj.startwith("approach"));
    assert(obj.startwith("about"));
    assert(!obj.startwith("appy"));
    assert(obj.startwith("abscond"));
    assert(obj.startwith("bus"));
    assert(obj.startwith("buses"));
    assert(obj.startwith("Bounce"));
    assert(obj.startwith("Apple"));
    assert(obj.startwith("abs"));
    assert(obj.startwith("b"));
    assert(obj.startwith("bus"));
    assert(obj.startwith("Bo"));
    assert(obj.startwith("A"));
    assert(!obj.startwith("Ca"));
    
    assert(!obj.startwith("C"));
    std::cout << "All the tests passed for startwith method" << std::endl;
    
    std::vector<std::string> pred_words = obj.predict_words("a");
    for(const std::string& str : obj.predict_words("a")) {
    	std::cout << str << std::endl;
	}
	assert(pred_words.size() == 8);
	std::cout << "Returned all words that start with prefix a " << std::endl;
	pred_words = obj.predict_words("app");
	
	for(const std::string& str : pred_words) {
		std::cout << str << std::endl;
	}
	
	assert(pred_words.size() == 5);
	std::cout << "Returned all words that start with prefix app " << std::endl;
	pred_words = obj.predict_words("A");
	
	for(const std::string& str : pred_words) {
		std::cout << str << std::endl;
	}
	
	assert(pred_words.size() == 1);
	std::cout << "Returned all words that start with prefix A " << std::endl;
	pred_words = obj.predict_words("bu");
	for(const std::string& str : pred_words) {
		std::cout << str << std::endl;
	}
	assert(pred_words.size() == 2);
	std::cout << "Returned all words that start with prefix bu" << std::endl;
	
	// tests for delete method

    obj.delete_word("app");
    assert(!obj.search("app"));
    std::cout << "word app is deleted sucessful" << std::endl;

    pred_words = obj.predict_words("app");
    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }
    assert(pred_words.size() == 4);
    std::cout << "app is deleted sucessful" << std::endl;
    
    // test case for Chinese language

    obj.insert("??");
    assert(obj.startwith("?"));
    pred_words = obj.predict_words("h");

    assert(pred_words.size() == 0);
    std::cout << "No word starts with prefix h in trie" << std::endl;

    std::cout << "All tests passed" << std::endl;
}

int main() {
	test();
	return 0;
}