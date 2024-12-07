// Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

 

// Example 1:

// Input: s = "leetcode"

// Output: 0

// Explanation:

// The character 'l' at index 0 is the first character that does not occur at any other index.

// Example 2:

// Input: s = "loveleetcode"

// Output: 2

// Example 3:

// Input: s = "aabb"

// Output: -1

/**
 * @param {string} s
 * @return {number}
 */
var firstUniqChar = function(s) {
    // Sử dụng Map để có hiệu suất tốt hơn và sắp xếp khóa tốt hơn
    const charCountMap = new Map();
    // Điền vào Bản đồ số lượng ký tự
    for(const char of s) {
        charCountMap.set(char, (charCountMap.get(char) || 0) + 1);
    }
    // Lặp qua chuỗi để tìm ký tự duy nhất đầu tiên
    for(let i = 0; i < s.length; i++) {
        if(charCountMap.get(s[i]) === 1) {
            return i;
        }
    }
    return -1;
};
const inputString = "leetcode";
const result = firstUniqChar(inputString);
console.log(result);