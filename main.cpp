#include "FileIndexer.hpp"

void sort_string_tab(std::string tab[], int len);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage : ./file_indexer directory_path" << std::endl;
        return 1;
    }

    try {
        
        FileIndexer indexer(argv[1]);

        //indexer.printTreeContent();

        std::string word;
        std::cout << "What word do you want to search for ? (Not case sensitive)" << std::endl;
        std::cin >> word;

        Node *found = indexer.find(Utils::str_tolower(word));
        if (found) {
            sort_string_tab(found->file_paths, found->nb_files);
            for (int i = 0; i < found->nb_files; i++)
                std::cout << found->file_paths[i] << std::endl;
        } else {
            std::cout << "No .txt file contains this word in this directory" << std::endl;
        }
        
        
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

// Simple bubble sort as it is use to sort names of files list which I believe won't contain thausands of elements
void sort_string_tab(std::string tab[], int len) {
    int         i, j;
    bool        swapped;
    std::string temp;
    
    for (i = 0; i < len - 1; i++) {
        swapped = false;
        for (j = 0; j < len - i - 1; j++) {
            if (tab[j].compare(tab[j + 1]) > 0) {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                swapped = true;
            }
        }
 
        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}