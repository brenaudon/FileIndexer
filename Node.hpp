#ifndef NODE_HPP
# define NODE_HPP

# include <string>
# include <stdlib.h>
# include <iostream>
# include <cstring>

class Node {
public:
    std::string     word;
    std::string     *file_paths;
    int             nb_files;
    Node            *left;
    Node            *right;

    Node(std::string word, std::string file_name);
    ~Node(void);

    Node    *insert(std::string word, std::string file_str);
    Node    *rebalance();
    Node    *find(const std::string &word);

    void print();

private:
    Node    *rotateLeft();
    Node    *rotateRight();
    Node    *rotateRightLeft();
    Node    *rotateLeftRight();
    
};

namespace Utils {
    int min(int a, int b);
    int max(int a, int b);
    int height(Node* node);
    int balance(Node* root);
};

#endif