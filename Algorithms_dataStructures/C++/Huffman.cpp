#include <iostream>
#include <queue>
using namespace std;

struct MinHeapNode{
	char data;
	unsigned freq;
	MinHeapNode *left, *right;
	MinHeapNode(char data, unsigned freq) {
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};
void deleteAll(const MinHeapNode* const root) {
	if(root) {
		deleteAll(root->left);
		deleteAll(root->right);
		delete root;
	}
}
struct compare {
	bool operator()(const MinHeapNode* const l, const MinHeapNode* const r) const {
		return l->freq > r->freq;
	}
};
void printCodes(struct MinHeapNode* root, const string& str) {
	if(!root) {
		return;
	}
	if(root->data != '$') cout << root->data << ": " << str << "\n";
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}
void HuffmanCodes(const char data[], const int freq[], int size) {
	struct MinHeapNode *left, *right;
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
	for(int i = 0; i < size; ++i) minHeap.push(new MinHeapNode(data[i], freq[i]));
	while(minHeap.size() != 1) {
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		auto* const top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	printCodes(minHeap.top(), "");
	deleteAll(minHeap.top());
}
int main() {
	char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	int freq[] = {5, 9, 12, 13, 16, 45};
	int size = sizeof(arr) / sizeof(arr[0]);
	HuffmanCodes(arr, freq, size);
	return 0;
}