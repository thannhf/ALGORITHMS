// Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.
// For example:
// A -> 1
// B -> 2
// C -> 3
// ...
// Z -> 26
// AA -> 27
// AB -> 28 
// ...

// Example 1:

// Input: columnNumber = 1
// Output: "A"
// Example 2:

// Input: columnNumber = 28
// Output: "AB"
// Example 3:

// Input: columnNumber = 701
// Output: "ZY"

/**
 * @param {number} columnNumber
 * @return {string}
 */
var convertToTitle = function(columnNumber) {
    let res = '';
    while(columnNumber > 0) {
        let r = columnNumber % 26;
        let q = parseInt(columnNumber / 26);
        if(r === 0) {
            r = 26;
            q--;
        }
        res = String.fromCharCode(64 + r) + res;
        columnNumber = q;
    }
    return res;
};