#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>

namespace data_structures{
	namespace list_array{
		template <uint64_t N>
		struct list {
			std::array<uint64_t, N> data{};
			uint64_t top = 0;
			bool isSorted = false;
			uint64_t BinarySearch(const std::array<uint64_t, N> &dataArr, const uint64_t &first, const uint64_t &last, const uint64_t &val) {
				if(last < first) {
					return -1;
				}
				uint64_t mid = (first + last) / 2;
				if(dataArr[mid] == val) 
					return mid;
				else if(val < dataArr[mid])
					return (BinarySearch(dataArr, first, mid - 1, val));
				else if(val > dataArr[mid])
					return (BinarySearch(dataArr, mid + 1, last, val));
				std::cerr << __func__ << ":" << __LINE__ << ": Undefined condition\n";
				return -1;
			}
			uint64_t LinearSearch(const std::array<uint64_t, N> &dataArr, const uint64_t &val) const {
				for(uint64_t i = 0; i < top; i++) {
					if(dataArr[i] == val) {
						return i;
					}
				}
				return -1;
			}
			uint64_t search(const uint64_t &val) {
				uint64_t pos;
				if(isSorted) {
					pos = BinarySearch(data, 0, top - 1, val);
				} else {
					pos = LinearSearch(data, val);
				}
				if(pos != -1) {
					std::cout << "\nElement found at position: " << pos;
				} else {
					std::cout << "\nElement not found";
				}
				return pos;
			}
			void sort() {
				for(uint64_t i = 0; i < top; i++) {
					uint64_t min_idx = i;
					for(uint64_t j = i + 1; j < top; j++) {
						if(data[j] < data[min_idx]) {
							min_idx = j;
						}
					}
					std::swap(data[min_idx], data[i]);
				}
				isSorted = true;
			}
			void insert(const uint64_t &val) {
				if(top == N) {
					std::cout << "\nOverflow";
					return;
				}
				if(!isSorted) {
					data[top] = val;
					top++;
				} else {
					uint64_t pos = 0;
					for(uint64_t i = 0; i < top - 1; i++) {
						if(data[i] <= val && val <= data[i + 1]) {
							pos = i + 1;
							break;
						}
					}
					if(pos == 0) {
						pos = top - 1;
					}
					for(uint64_t i = top; i > pos; i--) {
						data[i] = data[i - 1];
					}
					top++;
					data[pos] = val;
				}
			}
			void remove(const uint64_t &val) {
				uint64_t pos = search(val);
				if(pos == -1) {
					std::cout << "\n Element does not present in the list ";
					return;
				}
				std::cout << "\n" << data[pos] << " deleted";
				for(uint64_t i = pos; i < top; i++) {
					data[i] = data[i + 1];
				}
				top--;
			}
			void show() {
				std::cout << '\n';
				for(uint64_t i = 0; i < top; i++) {
					std::cout << data[i] << " ";
				}
			}
		};
	}
}
static void test() {
	data_structures::list_array::list<50> L;
	L.insert(11);
	L.insert(12);
	assert(L.top == 2);
	L.insert(15);
	L.insert(10);
	L.insert(12);
	L.insert(20);
	L.insert(18);
	assert(L.top == 7);
	L.show();
	
	L.remove(12);
	L.remove(15);
	assert(L.top == 5);
	L.remove(50);
	assert(L.top == 5);
	
	assert(L.search(11) == 0);
	assert(L.search(12) == 2);
	assert(L.search(50) == -1);
	
	L.sort();
	assert(L.isSorted == true);
	L.show();
	
	assert(L.search(11) == 1);
	assert(L.search(12) == 2);
	assert(L.search(50) == -1);
}
int main() {
	test();
	return 0;
}