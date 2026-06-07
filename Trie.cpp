#include "Trie.hpp"

TrieNode::TrieNode() : isEndOfTitle(false), game(nullptr) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        children[i] = nullptr;
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        delete children[i];
    }
}

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

std::string Trie::toSearchKey(std::string text) {
}

bool Trie::insert(Game* game) {
}

bool Trie::contains(std::string title) {
}

void Trie::sortResults(std::vector<Game*>& games) {
}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {
}
