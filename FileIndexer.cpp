#include "FileIndexer.hpp"

FileIndexer::FileIndexer(const std::string &path) {
    indexFileFromDir(path);
}

FileIndexer::~FileIndexer() {}

void FileIndexer::indexFileFromDir(const std::string &path) {
    DIR *dir;
    struct dirent *dir_content;

    dir = opendir(path.c_str());
    if (dir != NULL) {
        dir_content = readdir(dir);
        // Browse through directory contents
        while (dir_content != NULL) {
            switch (dir_content->d_type)
            {
            // Is a regular file
            case DT_REG:
                if (Utils::isTxtFile(dir_content->d_name))
                    parseTxtFile(path + "/" + dir_content->d_name);
                break;
            // Is a directory
            case DT_DIR:
                if (!Utils::isExcludedDirName(dir_content->d_name))
                    indexFileFromDir(path + "/" + dir_content->d_name);
                break;
            default:
                break;
            }
            dir_content = readdir(dir); 
        }
        closedir(dir);
    } else {
        throw std::runtime_error("Not a directory");
    }
}

void FileIndexer::parseTxtFile(const std::string &path) {
    std::ifstream       infile(path.c_str());
    std::string         line;
    std::string         str;
    std::stringstream   ss;

    if (infile.fail()) {
        throw std::runtime_error("Couldn't open file");
    }

    // Read file line by line
    while(std::getline(infile, line))
    {
        ss << line;
        // read line word by word (word = at least one char, separate by space or end of line/file)
        while(std::getline(ss, str, ' ')) {
            str = Utils::str_tolower(str);
            this->tree.insert(str, path);
        }
        ss.clear();
    }
}

Node *FileIndexer::find(const std::string &word) {
    return this->tree.find(word);
}

void FileIndexer::printTreeContent() {
    this->tree.root->print();
}

//*****UTILS*****

// To exclude special directories . and ..
int Utils::isExcludedDirName(const char *dir_name) {
    std::string dir_str(dir_name);

    if (dir_str == "." || dir_str == "..")
        return 1;
    return 0;
}

// Check if file is a .txt
bool Utils::isTxtFile(char * file_name) {
    std::string file_str(file_name);

    if(file_str.substr(file_str.find_last_of(".") + 1) == "txt")
        return true;
    return false;
}

// Used to normalize words in lowercase only
std::string Utils::str_tolower(std::string str) {
    std::string s;

    for (size_t i = 0; i < strlen(str.c_str()); i++)
        s.push_back(tolower(str[i]));
    return s;
}