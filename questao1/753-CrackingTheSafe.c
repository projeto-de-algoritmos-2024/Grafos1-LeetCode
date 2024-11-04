#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int node, int n, int k, int *visited, char *result, int *index) {
    int mod = 1;
    for (int i = 0; i < n - 1; i++) mod *= k; // Ajusta a base para o número correto
    
    for (int i = 0; i < k; i++) {
        int next = node * k + i; // Calcula o próximo nó
        
        if (!visited[next]) {
            visited[next] = 1; // Marca o nó como visitado
            dfs(next % mod, n, k, visited, result, index); // Move-se para o próximo nó
            result[(*index)++] = '0' + i; // Adiciona o dígito correto ao resultado
        }
    }
}

char* crackSafe(int n, int k) {
    if (n == 1) {
        char *result = (char*)malloc(k + 1);
        for (int i = 0; i < k; i++) {
            result[i] = '0' + i;
        }
        result[k] = '\0';
        return result;
    }

    int totalCombinations = 1;
    for (int i = 0; i < n - 1; i++) totalCombinations *= k;

    int *visited = (int*)calloc(totalCombinations * k, sizeof(int)); // Ajusta o tamanho do array para todos os estados
    if (!visited) {
        fprintf(stderr, "Erro ao alocar memória para o array de combinações visitadas.\n");
        return NULL;
    }
    
    int resultLen = totalCombinations * k + n - 1; // Calcula o comprimento do resultado
    char *result = (char*)malloc(resultLen + 1); // Aloca memória para o resultado
    if (!result) {
        fprintf(stderr, "Erro ao alocar memória para o resultado.\n");
        free(visited);
        return NULL;
    }
    result[resultLen] = '\0'; // Termina a string com '\0'
    
    int index = 0;
    dfs(0, n, k, visited, result, &index); // Inicia o DFS
    for (int i = 0; i < n - 1; i++) result[index++] = '0'; // Adiciona os zeros finais

    free(visited);
    return result;
}