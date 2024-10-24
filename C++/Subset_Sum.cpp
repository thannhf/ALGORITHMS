#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace dynamic_programming {
	namespace subset_sum{
		bool subset_sum_recursion(const std::vector<int> &arr, int targetSum, std::vector<std::unordered_map<int, bool>> *dp, int index = 0) {
			if(targetSum == 0) return true;
			if(index == arr.size()) {
				return false;
			}
			if((*dp)[index].count(targetSum)) {
				return (*dp)[index][targetSum];
			}
			
			bool ans = subset_sum_recursion(arr, targetSum - arr[index], dp, index + 1) || subset_sum_recursion(arr, targetSum, dp, index + 1);
			(*dp)[index][targetSum] = ans;
			return ans;
		}
		
		bool subset_sum_problem(const std::vector<int> &arr, const int targetSum){
			size_t n = arr.size();
			std::vector<std::unordered_map<int, bool>> dp(n);
			return subset_sum_recursion(arr, targetSum, &dp);
		}
	}
}

static void test() {
	std::vector<std::vector<int>> custom_input_arr(3);
	custom_input_arr[0] = std::vector<int>{1, -10, 2, 31, -6};
	custom_input_arr[1] = std::vector<int>{2, 3, 4};
	custom_input_arr[2] = std::vector<int>{0, 1, 0, 1, 0};
	
	std::vector<int> custom_input_target_sum(3);
	custom_input_target_sum[0] = -14;
	custom_input_target_sum[1] = 10;
	custom_input_target_sum[2] = 2;
	
	std::vector<int> calculated_output(3);
	
	for(int i = 0; i < 3; i++) {
		calculated_output[i] = dynamic_programming::subset_sum::subset_sum_problem(custom_input_arr[i], custom_input_target_sum[i]);
	}
	
	std::vector<bool> expected_output{true, false, true};
	
	for(int i = 0; i < 3; i++) {
		assert(expected_output[i] == calculated_output[i]);
	}
	std::cout << "All tests passed successfully!\n";
}

int main() {
	test();
	return 0;
}