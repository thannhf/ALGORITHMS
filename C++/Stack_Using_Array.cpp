#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace data_structures{
	template <typename T>
	class Stack{
		private:
			std::unique_ptr<T[]> stack;
			int stackSize;
			int stackIndex;
		public:
			Stack(int size) : stackSize(size), stackIndex(-1), stack(new T[size]) {}
			bool full() const {
				return stackIndex == stackSize - 1;
			}
			bool empty() const {
				return stackIndex == -1;
			}
			void push(T element) {
				if(full()) {
					throw std::out_of_range("Stack overflow");
				} else {
					stack[++stackIndex] = element;
				}
			}
			T pop() {
				if(empty()) {
					throw std::out_of_range("Stack underflow");
				}
				return stack[stackIndex--];
			}
			void show() const {
				for(int i = 0; i <= stackIndex; i++) {
					std::cout << stack[i] << "\n";
				}
			}
			T topmost() const {
				if(empty()) {
					throw std::out_of_range("Stack underflow");
				}
				return stack[stackIndex];
			}
			T bottom() const {
				if(empty()) {
					throw std::out_of_range("Stack underflow");
				}
				return stack[0];
			}
	};
}
static void test() {
	data_structures::Stack<int> stack(5);
	assert(stack.empty());
	assert(!stack.full());
	
	stack.push(10);
	assert(stack.topmost() == 10);
	
	stack.push(20);
	assert(stack.topmost() == 20);
	
	stack.push(30);
	stack.push(40);
	stack.push(50);
	assert(stack.full());
	
	try {
		stack.push(60);
	} catch(const std::out_of_range& e) {
		assert(std::string(e.what()) == "Stack overflow");
	}
	
	assert(stack.pop() == 50);
	assert(stack.pop() == 40);
	assert(stack.pop() == 30);
	
	assert(stack.topmost() == 20);
	assert(stack.bottom() == 10);
	
	assert(stack.pop() == 20);
	assert(stack.pop() == 10);
	
	assert(stack.empty());
	assert(!stack.full());
	
	try{
		stack.pop();
	} catch(const std::out_of_range& e) {
		assert(std::string(e.what()) == "Stack underflow");
	}
	
	try{
		stack.topmost();
	} catch(const std::out_of_range& e) {
		assert(std::string(e.what()) == "Stack underflow");
	}
	
	try{
		stack.bottom();
	} catch(const std::out_of_range& e) {
		assert(std::string(e.what()) == "Stack underflow");
	}
}

int main() {
	test();
	std::cout << "All tests passed!" << std::endl;
	return 0;
}