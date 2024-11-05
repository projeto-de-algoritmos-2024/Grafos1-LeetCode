#include <stdio.h>
#include <stdlib.h>

// Função recursiva DFS (Depth-First Search) para gerar a sequência de De Bruijn
void dfs(int node, int n, int k, int *visited, char *result, int *index) {
    // Calcula o valor de mod para manter o valor do nó no limite de `k^(n-1)`
    int mod = 1;
    for (int i = 0; i < n - 1; i++) mod *= k;

    // Tenta todos os dígitos possíveis (de 0 a k-1)
    for (int i = 0; i < k; i++) {
        // Calcula o próximo nó `next` adicionando o dígito `i` ao nó atual
        int next = node * k + i;

        // Se este nó (combinação) ainda não foi visitado
        if (!visited[next]) {
            // Marca como visitado para evitar repetições
            visited[next] = 1;

            // Chamada recursiva para explorar o próximo nó, reduzindo-o ao valor de n-1 dígitos
            dfs(next % mod, n, k, visited, result, index);

            // Adiciona o dígito `i` ao resultado na posição atual do índice
            result[(*index)++] = '0' + i;
        }
    }
}

// Função principal que gera a sequência de De Bruijn para `n` dígitos e `k` símbolos
char* crackSafe(int n, int k) {
    // Caso especial: se n é 1, basta retornar todos os dígitos de 0 até k-1
    if (n == 1) {
        // Aloca memória para o resultado
        char *result = (char*)malloc(k + 1);
        
        // Preenche a sequência com os dígitos de 0 a k-1
        for (int i = 0; i < k; i++) {
            result[i] = '0' + i;
        }
        
        // Adiciona o caractere nulo no final para marcar o fim da string
        result[k] = '\0';
        return result;
    }

    // Calcula o número total de combinações únicas de n-1 dígitos
    int totalCombinations = 1;
    for (int i = 0; i < n - 1; i++) totalCombinations *= k;

    // Aloca o array `visited` para marcar quais combinações foram visitadas
    int *visited = (int*)calloc(totalCombinations * k, sizeof(int));
    if (!visited) {
        return NULL;
    }

    // Calcula o comprimento final do resultado da sequência de De Bruijn
    int resultLen = totalCombinations * k + n - 1;

    // Aloca a string `result` para armazenar a sequência de De Bruijn
    char *result = (char*)malloc(resultLen + 1);
    if (!result) {
        free(visited);
        return NULL;
    }

    // Adiciona o caractere nulo no final da string para indicar o fim da sequência
    result[resultLen] = '\0';

    // Inicializa o índice que rastreia a posição atual na string `result`
    int index = 0;

    // Inicia a busca DFS a partir do nó inicial 0
    dfs(0, n, k, visited, result, &index);

    // Preenche os últimos `n-1` dígitos com '0' para completar o ciclo da sequência
    for (int i = 0; i < n - 1; i++) result[index++] = '0';

    // Libera a memória do array `visited` pois não é mais necessário
    free(visited);

    // Retorna a sequência de De Bruijn gerada
    return result;
}

// Função de teste para validar a saída da sequência de De Bruijn

/*
int main(int argc, char *argv[]) {
    int n = 2, k = 2;
    char* result = crackSafe(n, k);

    if (result) {
        printf("De Bruijn Sequence for n=%d, k=%d: %s\n", n, k, result);
        free(result);
    } else {
        printf("Failed to generate the sequence.\n");
    }

    return 0;
}
*/
