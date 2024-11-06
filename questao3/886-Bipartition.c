#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 3000

// Estrutura de fila para BFS
typedef struct {
    int *data;
    int front, rear;
} Queue;

// Função para inicializar a fila
void initQueue(Queue *q, int size) {
    q->data = (int*)malloc(sizeof(int) * size);
    q->front = 0;
    q->rear = 0;
}

// Função para verificar se a fila está vazia
bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

// Função para enfileirar
void enqueue(Queue *q, int value) {
    q->data[q->rear++] = value;
}

// Função para desenfileirar
int dequeue(Queue *q) {
    return q->data[q->front++];
}

// Função para liberar a memória da fila
void freeQueue(Queue *q) {
    free(q->data);
}

// Função para verificar a bipartição
bool possibleBipartition(int n, int** dislikes, int dislikesSize, int* dislikesColSize) {
    // Grafo de aversões
    int graph[MAX_NODES][MAX_NODES] = {0};
    
    // Preenchendo o grafo com as aversões
    for (int i = 0; i < dislikesSize; i++) {
        int u = dislikes[i][0];
        int v = dislikes[i][1];
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    // Array de cores para armazenar o grupo de cada pessoa (0 = não colorido, 1 e -1 são os grupos)
    int color[MAX_NODES] = {0};

    // Realizando BFS para colorir o grafo
    Queue q;
    initQueue(&q, n + 1);

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {  // Se a pessoa não foi colorida
            enqueue(&q, i);
            color[i] = 1;  // Atribuindo o primeiro grupo

            while (!isEmpty(&q)) {
                int node = dequeue(&q);
                
                for (int j = 1; j <= n; j++) {
                    if (graph[node][j]) {  // Se existe uma relação de aversão entre node e j
                        if (color[j] == 0) {  // Se j não foi colorido
                            color[j] = -color[node];  // Atribuir a cor oposta
                            enqueue(&q, j);
                        } else if (color[j] == color[node]) {  // Se j e node têm a mesma cor
                            freeQueue(&q);
                            return false;
                        }
                    }
                }
            }
        }
    }

    freeQueue(&q);
    return true;
}
