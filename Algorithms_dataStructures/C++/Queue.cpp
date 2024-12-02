#ifndef DATA_STRUCTURES_QUEUE_HPP_
#define DATA_STRUCTURES_QUEUE_HPP_
#include "node.hpp"
template <class ValueType>
class queue{
	using node_type = Node<ValueType>;
	public:
		using value_type = ValueType;
		void display() const {
			std::cout << "Front --> ";
			display_all(this->queueFront.get());
			std::cout << '\n';
			std::cout << "Size of queue: " << size << '\n';
		}
		std::vector<value_type> toVector() const {
			return push_all_to_vector(this->queueFront.get(), this->size);
		}
	private:
		void ensureNotEmpty() const {
			if(isEmptyQueue()) {
				throw std::invalid_argument("Queue is empty");
			}
		}
	public:
		bool isEmptyQueue() const {
			return (queueFront == nullptr);
		}
		void enQueue(const value_type& item) {
			auto newNode = std::make_shared<node_type>();
			newNode->data = item;
			newNode->next = nullptr;
			if(isEmptyQueue()) {
				queueFront = newNode;
				queueRear = newNode;
			} else {
				queueRear->next = newNode;
				queueRear = queueRear->next;
			}
			++size;
		}
		value_type front() const {
			ensureNotEmpty();
			return queueFront->data;
		}
		void deQueue() {
			ensureNotEmpty();
			queueFront = queueFront->next;
			--size;
		}
		void clear() {
			queueFront = nullptr;
			queueRear = nullptr;
			size = 0;
		}
	private:
		std::shared_ptr<node_type> queueFront = {};
		std::shared_ptr<node_type> queueRear = {};
		std::size_t size = 0;
};
#endif