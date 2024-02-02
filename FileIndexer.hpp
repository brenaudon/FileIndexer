#ifndef FILEINDEXER_HPP
# define FILEINDEXER_HPP

# include <dirent.h>
# include <iostream>
# include <string>
# include <filesystem>
# include <sstream>
# include <fstream>
# include "BalancedTree.hpp"

class FileIndexer {
public:
    FileIndexer(const std::string &path);
    ~FileIndexer(void);

    Node    *find(const std::string &word);
    void    printTreeContent();
    
private:
    BalancedTree tree;

    void parseTxtFile(const std::string &path);
    void indexFileFromDir(const std::string &path);
};

namespace Utils {
    int         isExcludedDirName(const char *dir_name);
    bool        isTxtFile(char * file_name);
    std::string str_tolower(std::string str);
};

#endif