// Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

// Example 1:

// Input: rowIndex = 3
// Output: [1,3,3,1]
// Example 2:

// Input: rowIndex = 0
// Output: [1]
// Example 3:

// Input: rowIndex = 1
// Output: [1,1]

/**
 * @param {number} rowIndex
 * @return {number[]}
 */
var getRow = function(rowIndex) {
    let triangle = [];
    for(let i = 0; i <= rowIndex; i++) {
        let row = [];
        for(let j = 0; j <= i; j++) {
            if(j === 0 || j === i) {
                row.push(1);
            } else {
                let leftVal = triangle[i - 1][j - 1];
                let rightVal = triangle[i - 1][j];
                row.push(leftVal + rightVal);
            }
        }
        triangle.push(row);
    }
    return triangle[rowIndex];
};