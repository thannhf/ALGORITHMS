#include <cassert>
#include <functional>
#include <initializer_list>
#include <string>
#include <vector>
#include <iostream>

namespace data_structures{
	class Bitset{
		private:
			std::vector<std::size_t> data;
			static const std::size_t blockSize = sizeof(std::size_t);
		public:
			explicit Bitset(std::size_t);
			std::size_t size();
			void add(std::size_t);
			bool constains(std::size_t);
	};
	std::size_t Bitset::size() {
		return data.size();
	}
	Bitset::Bitset(std::size_t initSize) : data(initSize) {}
	void Bitset::add(std::size_t x) {
		std::size_t blockIndex = x / blockSize;
		if(blockIndex >= data.size()) {
			data.resize(blockIndex + 1);
		}
		data[blockIndex] |= 1 << (x % blockSize);
	}
	bool Bitset::constains(std::size_t x) {
		std::size_t blockIndex = x / blockSize;
		if(blockIndex >= data.size()) {
			return false;
		}
		return data[blockIndex] & (1 << (x % blockSize));
	}
	template <typename T>
	class BloomFilter{
		private:
			Bitset set;
			std::vector<std::function<std::size_t(T)>> hashFunks;
		public:
			BloomFilter(std::size_t, std::initializer_list<std::function<std::size_t(T)>>);
			void add(T);
			bool contains(T);
	};
	template <typename T>
	BloomFilter<T>::BloomFilter(std::size_t size, std::initializer_list<std::function<std::size_t(T)>> funks) : set(size), hashFunks(funks){}
	template <typename T>
	void BloomFilter<T>::add(T x) {
		for(std::size_t i = 0; i < hashFunks.size(); i++) {
			set.add(hashFunks[i](x) % (sizeof(std::size_t) * set.size()));
		}
	}
	template <typename T>
	bool BloomFilter<T>::contains(T x) {
		for(std::size_t i = 0; i < hashFunks.size(); i++) {
			if(set.constains(hashFunks[i](x) % (sizeof(std::size_t) * set.size())) == false) {
				return false;
			}
		}
		return true;
	}
	static std::size_t hashDJB2(std::string const& s) {
		std::size_t hash = 5381;
		for(char c : s) {
			hash = ((hash << 5) + hash) + c;
		}
		return hash;
	}
	static std::size_t hashStr(std::string const& s) {
		std::size_t hash = 37;
		std::size_t primeNum1 = 54059;
		std::size_t primeNum2 = 76963;
		for(char c : s) {
			hash = (hash * primeNum1) ^ (c * primeNum2);
		}
		return hash;
	}
	std::size_t hashInt_1(int x) {
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x;
	}
	std::size_t hashInt_2(int x) {
		auto y = static_cast<std::size_t>(x);
		y = (y ^ (y >> 30)) * static_cast<std::size_t>(0xbf58476d1ce4e5b9);
		y = (y ^ (y >> 27)) * static_cast<std::size_t>(0x94d049bb133111eb);
		y = y ^ (y >> 31);
		return y;
	}
}
static void test_bloom_filter_string() {
	data_structures::BloomFilter<std::string> filter(10, {data_structures::hashDJB2, data_structures::hashStr});
	std::vector<std::string> toCheck{"hello", "world", "!"};
	std::vector<std::string> toFalse{"false", "world2", "!!!"};
	for(const auto& x : toCheck) {
		filter.add(x);
	}
	for(const auto& x : toFalse) {
		assert(filter.contains(x) == false);
	}
	for(const auto& x : toCheck) {
		assert(filter.contains(x));
	}
}
static void test_bloom_filter_int() {
	data_structures::BloomFilter<int> filter(20, {data_structures::hashInt_1, data_structures::hashInt_2});
	std::vector<int> toCheck{100, 200, 300, 50};
	std::vector<int> toFalse{1, 2, 3, 4, 5, 6, 7, 8};
	for(int x : toCheck) {
		filter.add(x);
	}
	for(int x : toFalse) {
		assert(filter.contains(x) == false);
	}
	for(int x : toCheck) {
		assert(filter.contains(x));
	}
}
static void test_bitset() {
	data_structures::Bitset set(2);
	std::vector<std::size_t> toCheck{0, 1, 5, 8, 63, 64, 67, 127};
	for(auto x : toCheck) {
		set.add(x);
		assert(set.constains(x));
	}
	assert(set.constains(128) == false);
	assert(set.constains(256) == false);
}
int main() {
	test_bitset();
	test_bloom_filter_string();
	test_bloom_filter_int();
	
	std::cout << "All tests have successfully passed!\n";
	return 0;
}