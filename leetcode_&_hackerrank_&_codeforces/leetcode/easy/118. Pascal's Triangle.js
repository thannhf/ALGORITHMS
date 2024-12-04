// Given an integer numRows, return the first numRows of Pascal's triangle.
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

// Example 1:

// Input: numRows = 5
// Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
// Example 2:

// Input: numRows = 1
// Output: [[1]]

/**
 * @param {number} numRows
 * @return {number[][]}
 Trường hợp cơ sở: Nếu numRows là 1, trả về [[1]].
Tạo đệ quy tam giác cho numRows - 1.
Tính hàng hiện tại bằng cách tính tổng các phần tử liền kề từ hàng trước.
 */
var generate = function(numRows) {
    if(numRows === 0) return [];
    if(numRows === 1) return [[1]];
    let prevRows = generate(numRows -1);
    let newRow = new Array(numRows).fill(1);
    /**
    i = 1               *    numrow -1
    i = 2 & 3      i-1<=**=> i không trừ => i = 2 ; numrow -2  => numrow -2 = hàng thứ 2
    i = 4 & 5 & 6       *** numrow -3
    ...                 **** numrow -4
    ...                 ***** numrow -5
    
     */
    for(let i = 1; i < numRows -1; i++) {
        newRow[i] = prevRows[numRows - 2][i - 1] + prevRows[numRows - 2][i];
    }
    prevRows.push(newRow);
    return prevRows;
};