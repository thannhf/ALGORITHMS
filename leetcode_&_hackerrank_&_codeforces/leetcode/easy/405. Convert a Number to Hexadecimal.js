// Given a 32-bit integer num, return a string representing its hexadecimal representation. For negative integers, two’s complement method is used.

// All the letters in the answer string should be lowercase characters, and there should not be any leading zeros in the answer except for the zero itself.

// Note: You are not allowed to use any built-in library method to directly solve this problem.

 

// Example 1:

// Input: num = 26
// Output: "1a"
// Example 2:

// Input: num = -1
// Output: "ffffffff"

/**
 * @param {number} num
 * @return {string}
 */
var toHex = function(num) {
    num = num < 0 ? ~-num + 1 >>> 0 : num;
    const hex = [];
    while(num >= 16) {
        hex.unshift(num % 16)
        num = Math.floor(num / 16);
    }
    hex.unshift(num);
    return hex.map(e => "0123456789abcdef"[e]).join``;
};