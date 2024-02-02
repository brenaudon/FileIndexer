#ifndef BALANCEDTREE_HPP
# define BALANCEDTREE_HPP

# include <string>
# include "Node.hpp"

class BalancedTree {
public:
    Node *root;

    BalancedTree();
    ~BalancedTree(void);

    void    insert(std::string word, std::string file_str);
    Node    *find(const std::string &word);

private:

};


#endif