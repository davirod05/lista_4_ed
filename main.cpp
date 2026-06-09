#include <iostream>
#include <cstdlib>
#include "Trie.hpp"
#include "GamesDatabase.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./app k prefix" << std::endl;
        return 1;
    }

    int k = std::atoi(argv[1]);
    std::string prefix = argv[2];

    Trie trie;
    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    std::vector<Game*> results = trie.autocomplete(prefix, k);

    if (results.empty()) {
        std::cout << "No results found" << std::endl;
        return 0;
    }

    for (int i = 0; i < (int)results.size(); i++) {
        std::cout << results[i]->getTitle() << " | "
                  << results[i]->getShortDescription() << " | "
                  << results[i]->getPopularity() << std::endl;
    }

    return 0;
}
