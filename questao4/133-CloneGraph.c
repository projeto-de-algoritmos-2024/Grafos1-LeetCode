#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó no grafo
struct GraphNode {
    int val;
    int numNeighbors;
    struct GraphNode** neighbors;
};

// Função para criar um novo nó do grafo
struct GraphNode* createNode(int val) {
    struct GraphNode* newNode = (struct GraphNode*)malloc(sizeof(struct GraphNode));
    newNode->val = val;
    newNode->numNeighbors = 0;
    newNode->neighbors = NULL;
    return newNode;
}

// Definindo o tamanho máximo para a tabela hash
#define MAX_NODES 101  // Assumindo que o valor dos nós está entre 1 e 100

// Tabela hash para armazenar os nós clonados
struct GraphNode* hashTable[MAX_NODES];

// Inicializa a tabela hash com NULL
void initHashTable() {
    for (int i = 0; i < MAX_NODES; i++) {
        hashTable[i] = NULL;
    }
}

// Busca na tabela hash para obter um nó já clonado
struct GraphNode* getNodeFromHashTable(int val) {
    return hashTable[val];
}

// Adiciona um nó clonado à tabela hash
void addNodeToHashTable(int val, struct GraphNode* node) {
    hashTable[val] = node;
}

// Função principal de clonagem usando DFS
struct GraphNode* cloneGraphDFS(struct GraphNode* node) {
    if (node == NULL) return NULL;

    // Verifica se o nó já foi clonado usando a tabela hash
    if (getNodeFromHashTable(node->val) != NULL) {
        return getNodeFromHashTable(node->val);
    }

    // Cria o nó clonado e adiciona à tabela hash
    struct GraphNode* clone = createNode(node->val);
    addNodeToHashTable(node->val, clone);

    // Aloca espaço para os vizinhos do nó clonado
    clone->numNeighbors = node->numNeighbors;
    clone->neighbors = (struct GraphNode**)malloc(clone->numNeighbors * sizeof(struct GraphNode*));

    // Clona recursivamente cada vizinho
    for (int i = 0; i < node->numNeighbors; i++) {
        clone->neighbors[i] = cloneGraphDFS(node->neighbors[i]);
    }

    return clone;
}

// Função para clonar o grafo, que inicializa a tabela hash e chama a DFS
struct GraphNode* cloneGraph(struct GraphNode* node) {
    // Inicializa a tabela hash para evitar duplicação
    initHashTable();
    return cloneGraphDFS(node);
}