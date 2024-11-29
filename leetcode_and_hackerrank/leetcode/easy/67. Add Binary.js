// Given two binary strings a and b, return their sum as a binary string.

// Example 1:

// Input: a = "11", b = "1"
// Output: "100"
// Example 2:

// Input: a = "1010", b = "1011"
// Output: "10101"

/**
 * @param {string} a
 * @param {string} b
 * @return {string}
 */
var addBinary = function(a, b) {
    //sử dụng BigInt() để chuyển đổi nhị phân thành số nguyên. Cú pháp là BigInt(0b11) ở đây `0b` là tiền tố và `11` là phân số nhị phân
    //tổng số lượt chuyển đổi trở lại thành chuỗi bằng cách sử dụng toString(2), ở đây 2 là cơ số, do đó toString(2) chuyển đổi thành phân tích nhị phân
    let sum = BigInt(`0b${a}`) + BigInt(`0b${b}`);
    return sum.toString(2);
};