// Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and num2 as a string.

// You must solve the problem without using any built-in library for handling large integers (such as BigInteger). You must also not convert the inputs to integers directly.

 

// Example 1:

// Input: num1 = "11", num2 = "123"
// Output: "134"
// Example 2:

// Input: num1 = "456", num2 = "77"
// Output: "533"
// Example 3:

// Input: num1 = "0", num2 = "0"
// Output: "0"

/**
 * @param {string} num1
 * @param {string} num2
 * @return {string}
 */
var addStrings = function(num1, num2) {
    num1 = num1.split("");
    num2 = num2.split("");
    let carry = "0";
    let result = [];
    while(num1.length || num2.length) {
        let [c1 = "0", c2 = "0"] = [num1.pop(), num2.pop()];
        let add = (Number(carry) + Number(c1) + Number(c2)).toString();
        carry = "0";
        if(Number(add) >= 10) {
            const [c1, c2] = add.split("");
            carry = c1;
            add = c2;
        }
        result.unshift(add);
    }
    if(Number(carry) > 0) result.unshift(carry);
    return result.join("");
};