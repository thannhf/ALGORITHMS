#ifndef DATA_STRUCTURES_STACK_HPP_
#define DATA_STRUCTURES_STACK_HPP_
#include <stdexcept>
#include "node.hpp";

template <class ValueType>
class stack{
	public:
		using value_type = ValueType;
		void display() const {
			std::cout << "Top --> ";
			display_all(this->stackTop.get());
			std::cout << '\n';
			std::cout << "Size of stack: " << size << std::endl;
		}
		std::vector<value_type> toVector() const {
			return push_all_to_vector(this->stackTop.get(), this->size);
		}
	private:
		void ensureNotEmpty() const {
			if(isEmptyStack()) {
				throw std::invalid_argument("Stack is empty.");
			}
		}
	public:
		bool isEmptyStack() const {
			return (stackTop == nullptr);
		}
		void push(const value_type& item) {
			auto newNode = std::make_shared<Node<value_type>>();
			newNode->data = item;
			newNode->next = stackTop;
			stackTop = newNode;
			size++;
		}
		value_type top() const {
			ensureNotEmpty();
			return stackTop->data;
		}
		void pop() {
			ensureNotEmpty();
			stackTop = stackTop->next;
			size--;
		}
		void clear() {
			stackTop = nullptr;
			size = 0;
		}
	private:
		std::shared_ptr<Node<value_type>> stackTop = {};
		std::size_t size = 0;
};
#endif;