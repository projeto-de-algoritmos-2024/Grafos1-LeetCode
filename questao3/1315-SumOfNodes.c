#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h>  // Inclui a biblioteca padrão para alocação de memória e funções utilitárias

// Função auxiliar recursiva que calcula a soma dos valores de nós que têm um avô com valor par
int grandpaAux(struct TreeNode* node, struct TreeNode* parent, struct TreeNode* grandparent) {
    if (node == NULL) return 0;  // Caso base: se o nó for NULL, retorna 0 (não há mais nós para processar)

    int sum = 0;  // Inicializa a variável 'sum' para armazenar a soma dos valores dos nós que atendem à condição

    // Verifica se o avô (grandparent) é não-nulo e tem valor par
    if (grandparent && grandparent->val % 2 == 0) {
        sum += node->val;  // Se o avô for par, adiciona o valor do nó atual à soma
    }

    // Chamada recursiva para o filho esquerdo do nó atual,
    // passando o nó atual como pai e o pai como avô
    sum += grandpaAux(node->left, node, parent);

    // Chamada recursiva para o filho direito do nó atual,
    // passando o nó atual como pai e o pai como avô
    sum += grandpaAux(node->right, node, parent);

    return sum;  // Retorna a soma acumulada dos nós que atendem à condição
}

// Função principal que inicia o cálculo
int sumEvenGrandparent(struct TreeNode* root) {
    return grandpaAux(root, NULL, NULL);  // Chama a função auxiliar com NULL para pai e avô no nó raiz
}
