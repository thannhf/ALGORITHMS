def pattern(n):
    for i in range(0, n):
        for j in range(0, i + 1):
            print("* ", end="")
        print("\n")
pattern(5)

# i = 5
# for 1 - i: 0 -> n, => 1
# for 1 - j: 0 -> i + 1 => 1 + 1 = 2
# print is space between lines for