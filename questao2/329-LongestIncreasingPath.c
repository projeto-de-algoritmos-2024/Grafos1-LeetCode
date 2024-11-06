#include <stdlib.h>

int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // Direções de movimento

// Função auxiliar para calcular o máximo entre dois inteiros
int max(int a, int b) {
    return a > b ? a : b;
}

// Função DFS com memorização
int dfs(int **matrix, int rows, int cols, int row, int col, int **memo) {
    if (memo[row][col] != -1) return memo[row][col];  // Retorna se já calculado

    int maxLength = 1;  // Caminho mínimo é 1 (a célula em si)

    // Explora todas as quatro direções
    for (int i = 0; i < 4; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        // Verifica se o movimento está dentro dos limites e é válido
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
            matrix[newRow][newCol] > matrix[row][col]) {
            maxLength = max(maxLength, 1 + dfs(matrix, rows, cols, newRow, newCol, memo));
        }
    }

    memo[row][col] = maxLength;  // Armazena o resultado
    return maxLength;
}

// Função principal para encontrar o caminho crescente mais longo
int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) return 0;

    int rows = matrixSize;
    int cols = matrixColSize[0];

    // Aloca a matriz de memoização
    int *memo = (int *)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        memo[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            memo[i][j] = -1;  // Inicializa todas as células como não calculadas
        }
    }

    int maxPath = 0;

    // Calcula o caminho mais longo a partir de cada célula
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            maxPath = max(maxPath, dfs(matrix, rows, cols, i, j, memo));
        }
    }

    // Libera a memória da matriz de memoização
    for (int i = 0; i < rows; i++) {
        free(memo[i]);
    }
    free(memo);

    return maxPath;
}