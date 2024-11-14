#include <iostream>
struct Node{
	int data;
	int next;
};
Node AvailArray[100];
int head = -1;
int avail = 0;
void initialise_list() {
	for(int i = 0; i <= 98; i++) {
		AvailArray[i].next = i + 1;
	}
	AvailArray[99].next = -1;
}
int getnode() {
	int NodeIndexToBeReturned = avail;
	avail = AvailArray[avail].next;
	return NodeIndexToBeReturned;
}
void freeNode(int nodeToBeDeleted) {
	AvailArray[nodeToBeDeleted].next = avail;
	avail = nodeToBeDeleted;
}
void insertAtTheBeginning(int data) {
	int newNode = getnode();
	AvailArray[newNode].data = data;
	AvailArray[newNode].next = head;
	head = newNode;
}
void insertAtTheEnd(int data) {
	int newNode = getnode();
	int temp = head;
	while(AvailArray[temp].next != -1) {
		temp = AvailArray[temp].next;
	}
	AvailArray[newNode].data = data;
	AvailArray[newNode].next = -1;
	AvailArray[temp].next = newNode;
}
void display() {
	int temp = head;
	while(temp != -1) {
		std::cout << AvailArray[temp].data << "->";
		temp = AvailArray[temp].next;
	}
	std::cout << "-1" << std::endl;
}
int main() {
	initialise_list();
	int x, y, z;
	for(;;) {
		std::cout << "1. Insert At The Beginning" << std::endl;
		std::cout << "2. Insert At The End" << std::endl;
		std::cout << "3. Display" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cout << "Enter Your Choice" << std::endl;
		std::cin >> z;
		switch(z) {
			case 1:
				std::cout << "Enter the number you want to enter" << std::endl;
				std::cin >> x;
				insertAtTheBeginning(x);
				break;
			case 2:
				std::cout << "Enter the number you want to enter" << std::endl;
				std::cin >> y;
				insertAtTheEnd(y);
				break;
			case 3:
				std::cout << "The linked list contains the following element in order" << std::endl;
				display();
				break;
			case 4:
				return 0;
			default:
				std::cout << "The entered choice is not correct" << std::endl;
		}
	}
	return 0;
}