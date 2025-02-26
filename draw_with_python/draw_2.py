# pattern = n = 5
# k = 2 * n - 2 => k = 2 * 5 - 2 = 8 with a line  - 1 white spaces => top triangle
# for 1 - i: 0 -> n => 1
# for 1 - j: 0 -> i + 1 => 0 -> 1 + 1 = 2.
##############################
# with bottom triangle we have reverse top triangle
##########################################
def pattern(n):
    k = 2 * n - 2
    for i in range(0, n):
        for j in range(0, k):
            print(end=" ")
        k = k - 1;
        for j in range(0, i + 1):
            print("* ", end="")
        print("\r")
    k = n - 2
    for i in range(n, -1, -1):
        for j in range(k, 0, -1):
            print(end=" ")
        k = k + 1
        for j in range(0, i + 1):
            print("* ", end="")
        print("\r")
pattern(5)
