# Lista 4 — Sistema de Autocomplete de Jogos com Trie

Trabalho da disciplina de Estrutura de Dados. Implementa um sistema de autocomplete de jogos usando uma **Trie** como estrutura principal de busca.

---

## Descrição

O programa recebe um prefixo pela linha de comando e retorna até `k` jogos cujo título começa com esse prefixo, ordenados por popularidade. A busca é case-insensitive e ignora espaços em branco.

---

## Organização dos arquivos

| Arquivo | Descrição |
|---|---|
| `main.cpp` | Ponto de entrada; carrega os jogos, insere na Trie e exibe os resultados |
| `Game.hpp` / `Game.cpp` | Classe `Game` com título, descrição curta e popularidade |
| `Trie.hpp` / `Trie.cpp` | Classes `TrieNode` e `Trie`; toda a lógica de inserção, busca e autocomplete |
| `GamesDatabase.hpp` / `GamesDatabase.cpp` | Lista estática de jogos usada como catálogo inicial |

---

## Compilação

```bash
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```

---

## Execução

```bash
./app k prefixo
```

- `k` — número máximo de sugestões a exibir
- `prefixo` — prefixo do título a buscar (entre aspas se tiver espaço)

---

## Exemplos de uso

**Busca simples:**
```bash
./app 3 ha
```
```
Hades | Roguelike de acao baseado na mitologia grega | 95
Half Life | FPS classico de ficcao cientifica | 92
Halo | FPS futurista com campanha e multiplayer | 85
```

**Prefixo com espaço (equivalente ao anterior sem espaço):**
```bash
./app 5 "half l"
```
```
Half Life | FPS classico de ficcao cientifica | 92
```

**Sem resultados:**
```bash
./app 3 zelda
```
```
No results found
```

**Argumentos inválidos:**
```bash
./app
```
```
Usage: ./app k prefix
```

---

## Detalhes de implementação

- **Alfabeto:** 36 caracteres — letras `a–z` (índices 0–25) e dígitos `0–9` (índices 26–35)
- **Chave de busca (`toSearchKey`):** converte o texto para minúsculas e remove todos os espaços antes de inserir ou buscar na Trie
- **Ordenação (`sortResults`):** implementada manualmente (sem `std::sort`); ordena por popularidade decrescente e, em caso de empate, por ordem alfabética da chave de busca
- **Autocomplete:** segue o prefixo na Trie e coleta todos os jogos da subárvore correspondente, sem percorrer o array original
