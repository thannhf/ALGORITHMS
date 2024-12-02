#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

namespace bit_manipulation{
	namespace travelling_salesman_using_bit_manipulation{
		std::uint64_t travelling_salesman_using_bit_manipulation(
			std::vector<std::vector<uint32_t>> dist,
			std::uint64_t setOfCities,
			std::uint64_t city,
			std::uint64_t n,
			std::vector<std::vector<uint32_t>> &dp
		) {
			if(setOfCities == (1 << n) - 1) {
				return dist[city][0];
			}
			
			if(dp[setOfCities][city] != -1) {
				return dp[setOfCities][city];
			}
			
			uint64_t ans = 2147483647;
			for(int choice = 0; choice < n; choice++) {
				if((setOfCities & (1 << choice)) == 0) {
					std::uint64_t subProb = dist[city][choice] + travelling_salesman_using_bit_manipulation(
						dist, setOfCities | (1 << choice), choice, n, dp
					);
					ans = std::min(ans, subProb);
				}
			}
			dp[setOfCities][city] = ans;
			return ans;
		}
	}
}

static void test() {
	//1st test_case
	std::vector<std::vector<uint32_t>> dist = {
		{0, 20, 42, 35}, {20, 0, 30, 34}, {42, 30, 0, 12}, {35, 34, 12, 0}
	};
	uint32_t V = dist.size();
	std::vector<std::vector<uint32_t>> dp(1 << V, std::vector<uint32_t>(V, -1));
	assert(bit_manipulation::travelling_salesman_using_bit_manipulation::travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp) == 97);
	std::cout << "1st test-case: passed!" << "\n";
	
	//2nd test-case
	dist = {{0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
	V = dist.size();
	std::vector<std::vector<uint32_t>> dp1(1 << V, std::vector<uint32_t>(V, -1));
	assert(bit_manipulation::travelling_salesman_using_bit_manipulation::travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp1) == 75);
	std::cout << "2nd test-case: passed!" << "\n";
	
	//3rd test-case
	dist = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
	V = dist.size();
	std::vector<std::vector<uint32_t>> dp2(1 << V, std::vector<uint32_t>(V, -1));
	assert(bit_manipulation::travelling_salesman_using_bit_manipulation::travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp2) == 80);
	std::cout << "3rd test-case: passed!" << "\n";
}

int main() {
	test();
	return 0;
}