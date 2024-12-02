#include <array>
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

namespace data_structures{
	constexpr int MAX_LEVEL = 2;
	constexpr float PROBABILITY = 0.5;
	
	struct Node{
		int key;
		void* value;
		std::vector<std::shared_ptr<Node>> forward;
		Node(int key, int level, void* value = nullptr) : key(key), value(value) {
			for(int i = 0; i < (level + 1); i++) {
				forward.push_back(nullptr);
			}
		};
	};
	class SkipList{
		int level;
		std::shared_ptr<Node> header;
		public:
			SkipList() {
				level = 0;
				header = std::make_shared<Node>(-1, MAX_LEVEL);
			}
			int randomLevel() {
				int lvl = 0;
				while(static_cast<float>(std::rand()) / RAND_MAX < PROBABILITY && lvl < MAX_LEVEL) {
					lvl++;
				}
				return lvl;
			}
			void insertElement(int key, void* value) {
				std::cout << "Inserting" << key << "...";
				std::shared_ptr<Node> x = header;
				std::array<std::shared_ptr<Node>, MAX_LEVEL + 1> update;
				update.fill(nullptr);
				for(int i = level; i >= 0; i--) {
					while(x->forward[i] != nullptr && x->forward[i]->key < key) {
						x = x->forward[i];
					}
					update[i] = x;
				}
				x = x->forward[0];
				bool doesnt_exist = (x == nullptr || x->key != key);
				if(doesnt_exist) {
					int rlevel = randomLevel();
					if(rlevel > level) {
						for(int i = level + 1; i < rlevel + 1; i++) update[i] = header;
						level = rlevel;
					}
					std::shared_ptr<Node> n = std::make_shared<Node>(key, rlevel, value);
					for(int i = 0; i <= rlevel; i++) {
						n->forward[i] = update[i]->forward[i];
						update[i]->forward[i] = n;
					}
					std::cout << "Inserted" << std::endl;
				} else {
					std::cout << "Exists" << std::endl;
				}
			}
			void deleteElement(int key) {
				std::shared_ptr<Node> x = header;
				std::array<std::shared_ptr<Node>, MAX_LEVEL + 1> update;
				update.fill(nullptr);
				for(int i = level; i >= 0; i--) {
					while(x->forward[i] != nullptr && x->forward[i]->key < key) {
						x = x->forward[i];
					}
					update[i] = x;
				}
				x = x->forward[0];
				bool doesnt_exist = (x == nullptr || x->key != key);
				if(!doesnt_exist) {
					for(int i = 0; i <= level; i++) {
						if(update[i]->forward[i] != x) {
							break;
						}
						update[i]->forward[i] = x->forward[i];
					}
					while(level > 0 && header->forward[level] == nullptr) level--;
					std::cout << "Deleted" << std::endl;
				} else {
					std::cout << "Doesn't exist" << std::endl;
				}
			}
			void* searchElement(int key) {
				std::shared_ptr<Node> x = header;
				std::cout << "Searching for " << key << std::endl;
				for(int i = level; i >= 0; i--) {
					while(x->forward[i] && x->forward[i]->key < key) x = x->forward[i];
				}
				x = x->forward[0];
				if(x && x->key == key) {
					std::cout << "Found" << std::endl;
					return x->value;
				} else {
					std::cout << "Not Found" << std::endl;
					return nullptr;
				}
			}
			void displayList() {
				std::cout << "Displaying list:\n";
				for(int i = 0; i <= level; i++) {
					std::shared_ptr<Node> node = header->forward[i];
					std::cout << "Level " << (i) << ": ";
					while(node != nullptr) {
						std::cout << node->key << " ";
						node = node->forward[i];
					}
					std::cout << std::endl;
				}
			}
	};
}
int main() {
	std::srand(std::time(nullptr));
	data_structures::SkipList lst;
	for(int j = 0; j < (1 << (data_structures::MAX_LEVEL + 1)); j++) {
		int k = (std::rand() % (1 << (data_structures::MAX_LEVEL + 2)) + 1);
		lst.insertElement(k, &j);
	}
	lst.displayList();
	return 0;
}