#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **dados;      // ponteiro duplo para armazenar elementos de qualquer tipo na pilha
    int topo;          // índice do topo da pilha
    int tamanho;       // quantidade atual de elementos na pilha
    int capacidade;    // capacidade total atual da pilha
} Pilha;

// Função para criar uma nova pilha com capacidade inicial especificada
Pilha* criarPilha(int capacidadeInicial) {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));  // aloca memória para a estrutura da pilha
    if (pilha == NULL) return NULL;  // verifica se a alocação foi bem-sucedida

    // Aloca memória para armazenar os dados (elementos) da pilha
    pilha->dados = (void **) malloc(sizeof(void*) * capacidadeInicial);
    if (pilha->dados == NULL) {  // se a alocação falhar
        free(pilha);             // libera a memória alocada para a estrutura
        return NULL;            // retorna NULL para indicar falha
    }
    pilha->topo = -1;                  // define como -1 pois a pilha está vazia
    pilha->tamanho = 0;               
    pilha->capacidade = capacidadeInicial; 

    return pilha;  // retorna o ponteiro para a pilha criada
}

// Função que dobra a capacidade da pilha quando ela está cheia
void dobrarCapacidade(Pilha *pilha) {
    int novaCapacidade = pilha->capacidade * 2;  // define a nova capacidade como o dobro da capacidade atual
    void **novosDados = (void **) malloc(sizeof(void*) * novaCapacidade);  // aloca memória para a nova capacidade

    // Realoca os elementos da pilha antiga para a nova área de memória
    for (int i = 0; i < pilha->tamanho; i++) {
        novosDados[i] = pilha->dados[i];  // copia os elementos para a nova posição
    }

    free(pilha->dados);         // libera a memória antiga da pilha
    pilha->dados = novosDados;  // aponta os dados para a nova área de memória alocada
    pilha->capacidade = novaCapacidade;  // atualiza a capacidade da pilha
    printf("Capacidade dobrada para: %d\n", novaCapacidade);  // exibe a nova capacidade
}

// Função para inserir um novo elemento na pilha (push)
int empurrarNaPilha(Pilha *pilha, void *elemento) {
    if (pilha->tamanho == pilha->capacidade) {  // verifica se a pilha está cheia
        dobrarCapacidade(pilha);               // chama a função para dobrar a capacidade se necessário
    }

    pilha->topo++;  // move o índice do topo para o próximo índice disponível
    pilha->dados[pilha->topo] = elemento;  // armazena o elemento no topo da pilha
    pilha->tamanho++;                    // aumenta o tamanho da pilha
    return 1;  // retorna 1 para indicar sucesso
}

// Função para remover um elemento do topo da pilha (pop)
void* removerDaPilha(Pilha *pilha) {
    if (pilha->tamanho == 0) {  // verifica se a pilha está vazia
        return NULL;  // retorna NULL se a pilha estiver vazia
    }

    void *itemRemovido = pilha->dados[pilha->topo];  // armazena o item a ser removido
    pilha->topo--;  // move o índice do topo para o elemento anterior
    pilha->tamanho--;  // diminui o tamanho da pilha

    return itemRemovido;  // retorna o item removido
}

// Função para exibir o conteúdo da pilha
void imprimirPilha(Pilha *pilha) {
    printf("Pilha: ");
    for (int i = pilha->topo; i >= 0; i--) {  // percorre os elementos atuais na pilha de cima para baixo
        if (pilha->dados[i] != NULL) {         // verifica se o dado não é NULL
            printf("%d ", *(int*)pilha->dados[i]);  // exibe o valor do elemento
        }
    }
    printf("\nCapacidade: %d, Tamanho: %d, Topo: %d\n",
           pilha->capacidade, pilha->tamanho, pilha->topo);  // exibe os detalhes da pilha
}

int main() {
    int capacidadeInicial = 3;                // define a capacidade inicial da pilha
    Pilha *pilha = criarPilha(capacidadeInicial);  // cria a pilha com a capacidade inicial
    if (pilha == NULL) {                        // verifica se a criação foi bem-sucedida
        printf("Erro ao criar a pilha.\n");     // exibe mensagem de erro se necessário
        return 1;                              // retorna 1 para indicar erro
    }

    // Insere elementos na pilha e testa o redimensionamento automático
    int elementos[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        empurrarNaPilha(pilha, &elementos[i]);
        printf("Inserindo elemento %d na pilha:\n", elementos[i]);
        imprimirPilha(pilha);
    }

    // Testa a remoção dos elementos da pilha para verificar a operação de pop
    printf("\nRemovendo elementos da pilha:\n");
    for (int i = 0; i < 5; i++) {
        void *item = removerDaPilha(pilha);
        if (item != NULL) {
            printf("Elemento removido: %d\n", *(int*)item);
        } else {
            printf("Pilha vazia, nada a remover.\n");
        }
        imprimirPilha(pilha);
    }

    // Testa o redimensionamento novamente com novos valores
    printf("\nTestando o redimensionamento da pilha:\n");
    for (int i = 60; i < 70; i++) {
        empurrarNaPilha(pilha, &i);
        printf("Inserindo elemento %d na pilha:\n", i);
        imprimirPilha(pilha);
    }

    // Libera a memória alocada após o uso para evitar vazamento
    free(pilha->dados);
    free(pilha);
    return 0;
}
