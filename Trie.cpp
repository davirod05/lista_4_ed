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

// Merge sort recursivo
void Trie::sortResults(std::vector<Game*>& games) {
    if (games.size() <= 1) return;

    // Divide o vetor ao meio e ordena cada metade recursivamente
    int mid = games.size() / 2;
    std::vector<Game*> left(games.begin(), games.begin() + mid);
    std::vector<Game*> right(games.begin() + mid, games.end());

    sortResults(left);
    sortResults(right);

    // Intercala as duas metades já ordenadas de volta em games
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < (int)left.size() && j < (int)right.size()) {
        Game* a = left[i];
        Game* b = right[j];
        bool aFirst;
        if (a->getPopularity() != b->getPopularity()) {
            aFirst = a->getPopularity() > b->getPopularity();
        } else {
            // Empate: ordem alfabética pela chave de busca
            aFirst = toSearchKey(a->getTitle()) < toSearchKey(b->getTitle());
        }
        if (aFirst) {
            games[k++] = left[i++];
        }
        else {
            games[k++] = right[j++];
        }
    }
    // Copia os elementos restantes da metade que não esgotou
    while (i < (int)left.size()) games[k++] = left[i++];
    while (j < (int)right.size()) games[k++] = right[j++];
}

// DFS que coleta todos os jogos na subárvore a partir de node
void Trie::collectGames(TrieNode* node, std::vector<Game*>& results) {
    if (node == nullptr) return;
    if (node->isEndOfTitle) results.push_back(node->game); // nó final, então acrescenta em results
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        collectGames(node->children[i], results);
    }
}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {
    std::vector<Game*> results;
    if (k <= 0) return results;

    // Navega até o nó correspondente ao fim do prefixo
    std::string key = toSearchKey(prefix);
    TrieNode* current = root;
    for (int i = 0; i < (int)key.size(); i++) {
        int index = charToIndex(key[i]);
        if (current->children[index] == nullptr) return results; // prefixo não existe na Trie
        current = current->children[index];
    }

    // Coleta todos os jogos na subárvore do prefixo, ordena e limita a k resultados
    collectGames(current, results);
    sortResults(results);

    if ((int)results.size() > k) results.resize(k);
    return results;
}
