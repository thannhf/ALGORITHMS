// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
// An input string is valid if:
// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.
// Every close bracket has a corresponding open bracket of the same type.

// Example 1:
// Input: s = "()"
// Output: true

// Example 2:
// Input: s = "()[]{}"
// Output: true

// Example 3:
// Input: s = "(]"
// Output: false

// Example 4:
// Input: s = "([])"
// Output: true

/**
 * @param {string} s
 * @return {boolean}
 */
var isValid = function(s) {
    if(s.length % 2 !== 0) return false;
    let stack = [];
    for(let i = 0; i < s.length; i++) {
        if(s[i] === '(') {
            stack.push(')');
        } else if(s[i] === '[') {
            stack.push(']');
        } else if(s[i] === '{') {
            stack.push('}');
        } else if(stack.length === 0 || stack.pop() !== s[i]) {
            return false;
        }
    }
    return stack.length === 0 ? true : false
};