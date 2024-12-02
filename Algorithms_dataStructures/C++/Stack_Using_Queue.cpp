#include <cassert>
#include <cstdint>
#include <iostream>
#include <queue>

namespace data_structures{
	namespace stack_using_queue{
		struct Stack {
			std::queue<int64_t> main_q;
			std::queue<int64_t> auxiliary_q;
			
			uint32_t current_size = 0;
			
			int top() {
				return main_q.front();
			}
			
			void push(int val) {
				auxiliary_q.push(val);
				while(!main_q.empty()) {
					auxiliary_q.push(main_q.front());
					main_q.pop();
				}
				swap(main_q, auxiliary_q);
				current_size++;
			}
			
			void pop() {
				if(main_q.empty()) {
					return;
				}
				main_q.pop();
				current_size--;
			}
			
			int size() {
				return current_size;
			}
		};
	}
}

static void test() {
	data_structures::stack_using_queue::Stack s;
	s.push(1);
	s.push(2);
	s.push(3);
	
	assert(s.size() == 3);
	assert(s.top() == 3);
	
	s.pop();
	assert(s.top() == 2);
	
	s.pop();
	assert(s.top() == 1);
	
	s.push(5);
	assert(s.top() == 5);
	
	s.pop();
	assert(s.top() == 1);
	
	assert(s.size() == 1);
}

int main() {
	test();
	return 0;
}