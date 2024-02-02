#include "Node.hpp"

//*******PUBLIC*******//

Node::Node(std::string word, std::string file_name) : word(word) {
    // [1] is useless but I want to emphasize that it is a tab
    this->file_paths = new std::string[1];
    this->nb_files = 1;
    this->file_paths[0] = file_name;
    this->left = NULL;
    this->right = NULL;
}

Node::~Node(void) {
    // recursively delete all nodes below it 
    if (this->left != NULL)
        delete this->left;
    if (this->right != NULL)
        delete this->right;
    delete [] this->file_paths;
}

Node* Node::insert(std::string word, std::string file_str) {
    // Word already stock in this node
    if (this->word == word) {
        for (int i = 0; i < this->nb_files; i++) {
            // Already found in this file 
            if (this->file_paths[i] == file_str)
                return this;
        }
        // Word found for the first time in this file
        // Increase tab size (create a new one bigger, copy and delete old one)
        std::string *temp = this->file_paths;
        this->file_paths = new std::string[this->nb_files + 1];
        for (int i = 0; i < this->nb_files; i++)
            this->file_paths[i] = temp[i];
        delete [] temp;
        // Insert file name at the end of tab
        this->file_paths[this->nb_files] = file_str;
        this->nb_files++;
        return this;
    }

    // Compare string to know if it must be insert in left or right subtree
    if (this->word.compare(word) < 0) {
        if (this->left == NULL) 
            this->left = new Node(word, file_str);
        else
            this->left = this->left->insert(word, file_str);
    } else {
        if (this->right == NULL) 
            this->right = new Node(word, file_str);
        else
            this->right = this->right->insert(word, file_str);
    }

    // Rebalance node if needed (recursively rebalance the whole tree)
    return this->rebalance();
}

Node*   Node::rebalance() {
    // Left subtree is too high, and left child has a left child
    if (Utils::balance(this) < -1 && Utils::balance(this->left) == -1)
        return this->rotateRight();
    // Right subtree is too high, and right child has a right child
    if (Utils::balance(this) > 1 && Utils::balance(this->right) == 1)
        return this->rotateLeft();
    // Left subtree is too high, and left child has a right child
    else if (Utils::balance(this) < -1 && Utils::balance(this->left) == 1)
        return this->rotateLeftRight();
    // Right subtree is too high, and right child has a left child
    else if (Utils::balance(this) > 1 && Utils::balance(this->right) == -1)
        return this->rotateRightLeft();   
    return this;
}

Node* Node::find(const std::string &word) {
    // Word found
    if (this->word == word)
        return this;
    // Word should be before in alphabetic order
    else if (this->word.compare(word) < 0) {
        // NULL mean not found
        if (this->left == NULL) 
            return NULL;
        else
            return this->left->find(word);
    // Word should be after in alphabetic order
    } else {
        if (this->right == NULL) 
            return NULL;
        else
            return this->right->find(word);
    }
}

void Node::print() {
    std::cout << this->word << std::endl;
    if (this->left != NULL)
        this->left->print();
    if (this->right != NULL)    
        this->right->print();
}

//*******PRIVATE*******//

// Rotations used to rebalance a node

Node*   Node::rotateLeft() {
    Node *r = this->right;

    this->right = r->left;
    r->left = this;

    return r;
}

Node*   Node::rotateRight() {
    Node *l = this->left;

    this->left = l->right;
    l->right = this;

    return l;
}

Node*   Node::rotateRightLeft() {
    this->right = this->right->rotateRight();
    return this->rotateLeft();;
}

Node*   Node::rotateLeftRight() {
    this->left = this->left->rotateLeft();
    return this->rotateRight();
}

//*****UTILS*****

int Utils::min(int a, int b) {
    if (a < b)
		return a;
	return b;
}

int Utils::max(int a, int b) {
    if (a > b)
		return a;
	return b;
}

int Utils::height(Node* node) {
    // Empty tree
    if (node == NULL)
        return 0;
 
    return (1 + max(height(node->left), height(node->right)));
}

int Utils::balance(Node* root) {
    int left_height;
    int right_height;
 
    // Empty tree
    if (root == NULL)
        return true;
 
    left_height = height(root->left);
    right_height = height(root->right);
 
    return (right_height - left_height);
}