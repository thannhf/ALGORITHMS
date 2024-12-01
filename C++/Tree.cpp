#include <iostream>
#include <list>

struct node {
    int val;
    node* left;
    node* right;
};

// Function to create the tree
void CreateTree(node* curr, node*& n, int x, char pos) {
    if (n != NULL) {
        char ch;
        std::cout << "\nLeft or Right of " << n->val << " (l/r): ";
        std::cin >> ch;
        if (ch == 'l') {
            CreateTree(n, n->left, x, ch);
        } else if (ch == 'r') {
            CreateTree(n, n->right, x, ch);
        }
    } else {
        node* t = new node;
        t->val = x;
        t->left = NULL;
        t->right = NULL;
        if (pos == 'l') {
            curr->left = t;
        } else if (pos == 'r') {
            curr->right = t;
        }
    }
}

// Breadth-First Traversal (BFT)
void BFT(node* n) {
    if (n == NULL) return;
    std::list<node*> queue;
    queue.push_back(n);

    while (!queue.empty()) {
        node* current = queue.front();
        std::cout << current->val << " ";
        queue.pop_front();

        if (current->left != NULL) {
            queue.push_back(current->left);
        }

        if (current->right != NULL) {
            queue.push_back(current->right);
        }
    }
    std::cout << std::endl;
}

// Preorder Traversal
void Pre(node* n) {
    if (n != NULL) {
        std::cout << n->val << " ";
        Pre(n->left);
        Pre(n->right);
    }
}

// Inorder Traversal
void In(node* n) {
    if (n != NULL) {
        In(n->left);
        std::cout << n->val << " ";
        In(n->right);
    }
}

// Postorder Traversal
void Post(node* n) {
    if (n != NULL) {
        Post(n->left);
        Post(n->right);
        std::cout << n->val << " ";
    }
}

int main() {
    int value;
    int ch;
    node* root = new node;

    std::cout << "\nEnter the value of root node: ";
    std::cin >> value;
    root->val = value;
    root->left = NULL;
    root->right = NULL;

    do {
        std::cout << "\nMenu:";
        std::cout << "\n1. Insert";
        std::cout << "\n2. Breadth First Traversal";
        std::cout << "\n3. Preorder Traversal";
        std::cout << "\n4. Inorder Traversal";
        std::cout << "\n5. Postorder Traversal";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter Your Choice: ";
        std::cin >> ch;

        switch (ch) {
            case 1: {
                int x;
                char pos;
                std::cout << "\nEnter the value to be inserted: ";
                std::cin >> x;
                std::cout << "\nLeft or Right of Root (l/r): ";
                std::cin >> pos;
                if (pos == 'l') {
                    CreateTree(root, root->left, x, pos);
                } else if (pos == 'r') {
                    CreateTree(root, root->right, x, pos);
                }
                break;
            }
            case 2:
                std::cout << "\nBreadth First Traversal: ";
                BFT(root);
                break;
            case 3:
                std::cout << "\nPreorder Traversal: ";
                Pre(root);
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "\nInorder Traversal: ";
                In(root);
                std::cout << std::endl;
                break;
            case 5:
                std::cout << "\nPostorder Traversal: ";
                Post(root);
                std::cout << std::endl;
                break;
            case 0:
                std::cout << "\nExiting...";
                break;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
        }
    } while (ch != 0);

    return 0;
}