#include "BalancedTree.hpp"

BalancedTree::BalancedTree() {
    this->root = NULL;
}

BalancedTree::~BalancedTree(void) {
    delete this->root;
}

void BalancedTree::insert(std::string word, std::string file_str) {
    // First node
    if (this->root == NULL) {
        this->root = new Node(word, file_str);
        return ;
    }

    this->root = this->root->insert(word, file_str);

    //Rebalance root if necessary
    if (Utils::balance(this->root) < -1 || Utils::balance(this->root) > 1)
        this->root->rebalance();
}

Node *BalancedTree::find(const std::string &word) {
    if (this->root == NULL)
        return NULL;
    return this->root->find(word);
}