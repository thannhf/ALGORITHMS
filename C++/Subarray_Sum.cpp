#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace backtracking {
	namespace subarray_sum {
		uint64_t subarray_sum(int64_t sum, const std::vector<int64_t> &in_arr) {
			int64_t nelement = in_arr.size();
			int64_t count_of_subset = 0;
			int64_t current_sum = 0;
			std::unordered_map<int64_t, int64_t> sumarray;
			
			for(int64_t i = 0; i < nelement; i++){
				current_sum += in_arr[i];
				
				if(current_sum == sum) {
					count_of_subset++;
				}
				
				if(sumarray.find(current_sum - sum) != sumarray.end()) {
					count_of_subset += (sumarray[current_sum - sum]);
				}
				sumarray[current_sum]++;
			}
			return count_of_subset;
		}
	}
}

static void test() {
	//test 1
	std::cout << "1st test: ";
	std::vector<int64_t> array1 = {-7, -3, -2, 5, 8};
	assert(backtracking::subarray_sum::subarray_sum(0, array1) == 1);
	std::cout << "passed" << std::endl;
	
	//test 2
	std::cout << "2nd test: ";
	std::vector<int64_t> array2 = {1, 2, 3, 3};
	assert(backtracking::subarray_sum::subarray_sum(6, array2) == 2);
	std::cout << "passed" << std::endl;
	
	//test 3
	std::cout << "3rd test: ";
	std::vector<int64_t> array3 = {1, 1, 1, 1};
	assert(backtracking::subarray_sum::subarray_sum(1, array3) == 4);
	std::cout << "passed" << std::endl;
	
	//test 4
	std::cout << "4th test: ";
	std::vector<int64_t> array4 = {3, 3, 3, 3};
	assert(backtracking::subarray_sum::subarray_sum(6, array4) == 3);
	std::cout << "passed" << std::endl;
	
	//test 5
	std::cout << "5th test: ";
	std::vector<int64_t> array5 = {};
	assert(backtracking::subarray_sum::subarray_sum(6, array5) == 0);
	std::cout << "passed" << std::endl;
}

int main() {
	test();
	return 0;
}