#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace dynamic_programming {
	namespace word_break {
		bool exists(const std::string &str, const std::unordered_set<std::string> &strSet) {
			return strSet.find(str) != strSet.end();
		}
		
		bool check(const std::string &s, const std::unordered_set<std::string> &strSet, int pos, std::vector<int> *dp) {
			if(pos == s.length()) {
				return true;
			}
			
			if(dp->at(pos) != INT_MAX) {
				return dp->at(pos) == 1;
			}
			
			std::string wordTillNow = "";
			for(int i = pos; i < s.length(); i++) {
				wordTillNow += std::string(1, s[i]);
				if(exists(wordTillNow, strSet) and check(s, strSet, i + 1, dp)) {
					dp->at(pos) = 1;
					return true;
				}
			}
			dp->at(pos) = 0;
			return false;
		}
		
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