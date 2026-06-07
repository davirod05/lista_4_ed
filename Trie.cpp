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
    std::string key = "";
    for (int i = 0; i < (int)text.size(); i++) {
        char c = text[i];
        if (c == ' ') continue;
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        key += c;
    }
    return key;
}

int Trie::charToIndex(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return c - '0' + 26;
}

bool Trie::insert(Game* game) {
    std::string key = toSearchKey(game->getTitle());
    TrieNode* current = root;

    for (int i = 0; i < (int)key.size(); i++) {
        int index = charToIndex(key[i]);
        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }

    current->isEndOfTitle = true;
    current->game = game;
    return true;
}

bool Trie::contains(std::string title) {
    std::string key = toSearchKey(title);
    TrieNode* current = root;

    for (int i = 0; i < (int)key.size(); i++) {
        int index = charToIndex(key[i]);
        if (current->children[index] == nullptr) {
            return false;
        }
        current = current->children[index];
    }

    return current->isEndOfTitle;
}

void Trie::sortResults(std::vector<Game*>& games) {
}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {
}
