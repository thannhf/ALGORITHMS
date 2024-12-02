#include <array>
#include <cassert>
#include <iostream>

namespace backtracking{
	namespace rat_maze {
		template <size_t size>
		bool solveMaze(int currposrow, int currposcol, const std::array<std::array<int, size>, size> &maze, std::array<std::array<int, size>, size> soln) {
			if((currposrow == size - 1) && (currposcol == size -1)) {
				soln[currposrow][currposcol] = 1;
				for(int i = 0; i < size; ++i) {
					for(int j = 0; j < size; ++j) {
						std::cout << soln[i][j] << " ";
					}
					std::cout << std::endl;
				}
				return true;
			} else {
				soln[currposrow][currposcol] = 1;
				if((currposcol < size - 1) && maze[currposrow][currposcol + 1] == 1 && solveMaze(currposrow, currposcol + 1, maze, soln)) {
					return true;
				}
				
				if((currposrow < size - 1) && maze[currposrow + 1][currposcol] == 1 && solveMaze(currposrow + 1, currposcol, maze, soln)) {
					return true;
				}
				
				soln[currposrow][currposcol] = 0;
				return false;
			}
		}
	}
}

static void test() {
	const int size = 4;
	std::array<std::array<int, size>, size> maze = {
		std::array<int, size>{1, 0, 1, 0}, std::array<int, size>{1, 0, 1, 1},
		std::array<int, size>{1, 0, 0, 1}, std::array<int, size>{1, 1, 1, 1}
	};
	std::array<std::array<int, size>, size> soln{};
	
	for(int i = 0; i < size; ++i) {
		for(int j = 0; j < size; ++j) {
			soln[i][j] = 0;
		}
	}
	
	int currposrow = 0;
	int currposcol = 0;
	assert(backtracking::rat_maze::solveMaze<size>(currposrow, currposcol, maze, soln) == 1);
}

int main() {
	test();
	return 0;
}