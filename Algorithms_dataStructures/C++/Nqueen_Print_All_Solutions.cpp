#include <array>
#include <iostream>

namespace backtracking {
	namespace n_queens_all_solutions {
		template <size_t n>
		void PrintSol(const std::array<std::array<int, n>, n>& board){
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					std::cout << board[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		
		template <size_t n>
		bool CanIMove(const std::array<std::array<int, n>, n>& board, int row, int col) {
			for(int i = 0; i < col; i++) {
				if(board[row][i] == 1) {
					return false;
				}
			}
			
			for(int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
				if(board[i][j] == 1) {
					return false;
				}
			}
			
			for(int i = row, j = col; i <= n - 1 && j >= 0; i++, j--) {
				if(board[i][j] == 1) {
					return false;
				}
			}
			return true;
		}
		
		template <size_t n>
		void NQueenSol(std::array<std::array<int, n>, n> board, int col) {
			if(col >= n) {
				PrintSol(board);
				return;
			}
			for(int i = 0; i < n; i++) {
				if(CanIMove(board, i, col)) {
					board[i][col] = 1;
					NQueenSol(board, col + 1);
					board[i][col] = 0;
				}
			}
		}
	}
}

int main() {
	const int n = 4;
	std::array<std::array<int, n>, n> board{0};
	backtracking::n_queens_all_solutions::NQueenSol(board, 0);
}