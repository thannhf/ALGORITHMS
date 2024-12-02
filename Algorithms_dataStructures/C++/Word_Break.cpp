#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
//đoạn mã kiểm tra xem một chuỗi s có thể được phân chia thành các từ hợp lệ từ một từ điển wordDict hay không, với cách tiếp cận đệ quy
namespace dynamic_programming {
	namespace word_break {
		//chức năng kiểm tra xem str có tồn tại trong tập hợp strSet hay không
		//sử dụng hàm find của unordered_set, trả về true nếu tìm thấy str trong strSet, ngược lại trả về false
		//giúp xác định nhanh chóng xem một từ có nằm trong từ điển wordDict hay không
		bool exists(const std::string &str, const std::unordered_set<std::string> &strSet) {
			return strSet.find(str) != strSet.end();
		}
		//s: chuỗi cần kiểm tra xem có thể được chia thành các từ hợp lệ không
		//strSet: tập hợp các từ trong wordDict dưới dạng unordered_set.
		//pos: vị trí hiện tại trong chuỗi s từ đó sẽ kiểm tra chuỗi con tiếp theo
		//dp: vector dp lưu trữ kết quả kiểm tra ở từng vị trí, để tránh lặp lại tính toán.
		bool check(const std::string &s, const std::unordered_set<std::string> &strSet, int pos, std::vector<int> *dp) {
			//basic: nếu pos đạt đến độ dài của chuỗi s, trả về true, nghĩa là đã tìm thấy cách chia hợp lệ cho toàn bộ chuỗi
			if(pos == s.length()) {
				return true;
			}
			//check dp: nếu dp[pos] không phải là INT_MAX, nghĩa là đã tính toán trước tại vị trí pos. giá trị này cho biết có thể tạo 
			//thành chuỗi hợp lệ từ vị trí pos hay không.
			if(dp->at(pos) != INT_MAX) {
				return dp->at(pos) == 1;
			}
			//create wordTillNow text: vòng lặp từ pos đến hết chuỗi, tạo chuỗi wordTillNow từng ký tự một.
			std::string wordTillNow = "";
			for(int i = pos; i < s.length(); i++) {
				wordTillNow += std::string(1, s[i]);
				//check exists: nếu wordTillNow có trong strSet và việc gọi đệ quy check(s, strSet, i + 1, dp) return true, 
				//thì tức là s có thể chia được thành các từ hợp lệ. đặt dp[pos] = 1 và trả về true;
				if(exists(wordTillNow, strSet) and check(s, strSet, i + 1, dp)) {
					dp->at(pos) = 1;
					return true;
				}
			}
			//nếu thất bại nếu không tìm thấy cách chia hợp lệ, đặt dp[pos] = 0 và trả về false;
			dp->at(pos) = 0;
			return false;
		}
		//đây là hàm chính để kiểm tra chuỗi s có thể được chia thành các từ trong wordDict hay không.
		//chuyển đổi wordDict thành strSet để tra cứu nhanh các từ hợp lệ
		//khởi tạo vector dp với kích thước bằng độ dài của s và giá trị ban đầu là INT_MAX, thể hiện rằng vị trí đó chưa được tính toán.
		//gọi hàm đệ quy: gọi check(s, strSet, 0, &dp) bắt đầu kiểm tra từ vị trí 0 trong chuỗi s.
		bool wordBreak(const std::string &s, const std::vector<std::string> &wordDict) {
			std::unordered_set<std::string> strSet;
			for(const auto &s : wordDict) {
				strSet.insert(s);
			}
			std::vector<int> dp(s.length(), INT_MAX);
			return check(s, strSet, 0, &dp);
		}
	}
}
//đoạn mã này sử dụng các phương pháp đệ quy và memoization để kiểm tra xem chuỗi s có thể phân chia thành các từ hợp lệ trong từ điển wordDict hay không. 
//memoization thông qua dp giúp tối ưu hóa thời gian bằng cách tránh tính toán lại các vị trí đã kiểm tra trước đó.
static void test() {
	const std::string s = "applepenapple";
	const std::vector<std::string> wordDict = {"apple", "pen"};
	assert(dynamic_programming::word_break::wordBreak(s, wordDict));
	std::cout << dynamic_programming::word_break::wordBreak(s, wordDict) << std::endl;
	std::cout << "test implementation passed!\n";
}

int main() {
	test();
	const std::string s = "applepenapple";
	const std::vector<std::string> wordDict = {"apple", "pen"};
	std::cout << dynamic_programming::word_break::wordBreak(s, wordDict) << std::endl;
}
