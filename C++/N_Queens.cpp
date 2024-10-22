#include <array>
#include <iostream>

namespace backtracking {
	namespace n_queens {
		template <size_t n>
		void printSolution(const std::array<std::array<int, n>, n> &board) {
			std::cout << "\n";
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					std::cout << "" << board[i][j] << " ";
				}
				std::cout << "\n";
			}
		}
		
		template <size_t n>
		bool isSafe(const std::array<std::array<int, n>, n> &board, const int &row, const int &col) {
			int i = 0, j = 0;
			for(i = 0; i < col; i++) {
				if(board[row][i]) {
					return false;
				}
			}
			
			for(i = row, j = col; i >= 0 && j >= 0; i--, j--) {
				if(board[i][j]) {
					return false;
				}
			}
			
			for(i = row, j = col; j >= 0 && i < n; i++, j--) {
				if(board[i][j]) {
					return false;
				}
			}
			
			return true;
		}
		
		template <size_t n>
		void solveNQ(std::array<std::array<int, n>, n> board, const int &col) {
			if(col >= n) {
				printSolution<n>(board);
				return;
			}
			
			for(int i = 0; i < n; i++) {
				if(isSafe<n>(board, i, col)) {
					board[i][col] = 1;
					solveNQ<n>(board, col + 1);
					board[i][col] = 0;
				}
			}
		}
	}
}

int main() {
	const int n = 4;
	std::array<std::array<int, n>, n> board = {
		std::array<int, n>({0, 0, 0, 0}), std::array<int, n>({0, 0, 0, 0}),
		std::array<int, n>({0, 0, 0, 0}), std::array<int, n>({0, 0, 0, 0})
	};
	
	backtracking::n_queens::solveNQ<n>(board, 0);
	return 0;
}