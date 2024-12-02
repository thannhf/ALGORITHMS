#include <array>
#include <cstdint>
#include <iostream>

constexpr uint16_t max_size{10};
namespace data_structures {
	namespace queue_using_array{
		class Queue_Array{
			public:
				void enqueue(const int16_t&);
				int dequeue();
				void display() const;
			private:
				int8_t front{-1};
				int8_t rear{-1};
				std::array<int16_t, max_size> arr{};
		};
		void Queue_Array::enqueue(const int16_t& ele) {
			if(rear == arr.size() - 1) {
				std::cout << "\nStack is full";
			} else if(front == -1 && rear == -1) {
				front = 0;
				rear = 0;
				arr[rear] = ele;
			} else if(rear < arr.size()) {
				++rear;
				arr[rear] = ele;
			}
		}
		int Queue_Array::dequeue() {
			int8_t d{0};
			if(front == -1) {
				std::cout << "\nstack is empty";
				return 0;
			} else if(front == rear) {
				d = arr.at(front);
				front = rear = -1;
			} else {
				d = arr.at(front++);
			}
			return d;
		}
		void Queue_Array::display() const {
			if(front == -1) {
				std::cout << "\nStack is empty";
			} else {
				for(int16_t i{front}; i <= rear; ++i) std::cout << arr.at(i) << " ";
			}
		}
	}
}
int main() {
	int op{0}, data{0};
	data_structures::queue_using_array::Queue_Array ob;
	std::cout << "\n1. enqueue(Insertion) ";
	std::cout << "\n2. dequeue(Deletion) ";
	std::cout << "\n3. Display";
	std::cout << "\n4. Exit";
	while(true) {
		std::cout << "\nEnter your choice ";
		std::cin >> op;
		if(op == 1) {
			std::cout << "Enter data ";
			std::cin >> data;
			ob.enqueue(data);
		} else if(op == 2) {
			data = ob.dequeue();
			std::cout << "\ndequeue element is:\t" << data;
		} else if(op == 3) {
			ob.display();
		} else if(op == 4) {
			exit(0);
		} else {
			std::cout << "\nWrong choice ";
		}
	}
	return 0;
}