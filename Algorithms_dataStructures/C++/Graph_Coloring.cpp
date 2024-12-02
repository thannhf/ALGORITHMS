#include <array>
#include <iostream>
#include <vector>

namespace backtracking{
	namespace graph_coloring{
		template <size_t V>
		void printSolution(const std::array<int, V>& color) {
			std::cout << "Following are the assigned colors\n";
			for(auto& col : color) {
				std::cout << col;
			}
			std::cout << "\n";
		}
		
		template <size_t V>
		bool isSafe(int v, const std::array<std::array<int, V>, V>& graph, const std::array<int, V>& color, int c) {
			for(int i = 0; i < V; i++) {
				if(graph[v][i] && c == color[i]) {
					return false;
				}
			}
			return true;
		}
		
		template <size_t V>
		void graphColoring(const std::array<std::array<int, V>, V>& graph, int m, std::array<int, V> color, int v) {
			if(v == V) {
				printSolution<V>(color);
				return;
			}
			
			for(int c = 1; c <= m; c++) {
				if(isSafe<V>(v, graph, color, c)) {
					color[v] = c;
					graphColoring<V>(graph, m, color, v + 1);
					color[v] = 0;
				}
			}
		}
	}
}

int main() {
	const int V = 4;
	std::array<std::array<int, V>, V> graph = {std::array<int, V>({0, 1, 1, 1}), std::array<int, V>({1, 0, 1, 0}), std::array<int, V>({1, 1, 0, 1}), std::array<int, V>({1, 0, 1, 0})};
		
	int m = 3;
	std::array<int, V> color{};
	
	backtracking::graph_coloring::graphColoring<V>(graph, m, color, 0);
	return 0;
}