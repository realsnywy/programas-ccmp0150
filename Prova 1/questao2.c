#include <stdio.h>
#include <stdlib.h>

typedef struct NodeFila
{
    int data;
    struct NodeFila *next;
} NodeFila;

typedef struct Fila
{
    NodeFila *front;
    NodeFila *rear;
} Fila;

Fila *criarFila()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->front = f->rear = NULL;
    return f;
}

void enfileirar(Fila *f, int data)
{
    NodeFila *newNode = (NodeFila *)malloc(sizeof(NodeFila));
    newNode->data = data;
    newNode->next = NULL;

    if (f->rear == NULL)
    {
        f->front = f->rear = newNode;
    }
    else
    {
        f->rear->next = newNode;
        f->rear = newNode;
    }
}

int desenfileirar(Fila *f)
{
    if (f->front == NULL)
        return -1;

    NodeFila *temp = f->front;
    int data = temp->data;
    f->front = f->front->next;

    if (f->front == NULL)
    {
        f->rear = NULL;
    }

    free(temp);
    return data;
}

int filaVazia(Fila *f)
{
    return f->front == NULL;
}

typedef struct NodePilha
{
    int data;
    struct NodePilha *next;
} NodePilha;

typedef struct Pilha
{
    NodePilha *top;
} Pilha;

Pilha *criarPilha()
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->top = NULL;
    return p;
}

void empilhar(Pilha *p, int data)
{
    NodePilha *newNode = (NodePilha *)malloc(sizeof(NodePilha));
    newNode->data = data;
    newNode->next = p->top;
    p->top = newNode;
}

int desempilhar(Pilha *p)
{
    if (p->top == NULL)
        return -1;

    NodePilha *temp = p->top;
    int data = temp->data;
    p->top = p->top->next;
    free(temp);
    return data;
}

int pilhaVazia(Pilha *p)
{
    return p->top == NULL;
}

void imprimirFila(Fila *f)
{
    NodeFila *atual = f->front;
    while (atual != NULL)
    {
        printf("%d ", atual->data);
        atual = atual->next;
    }
    printf("\n");
}

Fila *inverterFileComPilhas(Fila F)
{
    Fila *filaInvertida = criarFila();
    Pilha *pilhaAux = criarPilha();

    NodeFila *atual = F.front;
    while (atual != NULL)
    {
        empilhar(pilhaAux, atual->data);
        atual = atual->next;
    }

    while (!pilhaVazia(pilhaAux))
    {
        enfileirar(filaInvertida, desempilhar(pilhaAux));
    }

    free(pilhaAux);
    return filaInvertida;
}

int main()
{
    Fila *filaOriginal = criarFila();
    enfileirar(filaOriginal, 1);
    enfileirar(filaOriginal, 2);
    enfileirar(filaOriginal, 3);
    enfileirar(filaOriginal, 4);

    printf("Fila Original: ");
    imprimirFila(filaOriginal);

    Fila *filaInvertida = inverterFileComPilhas(*filaOriginal);
    printf("Fila Invertida: ");
    imprimirFila(filaInvertida);

    // Liberar memória
    NodeFila *atual = filaInvertida->front;
    while (atual != NULL)
    {
        NodeFila *temp = atual;
        atual = atual->next;
        free(temp);
    }
    free(filaInvertida);

    atual = filaOriginal->front;
    while (atual != NULL)
    {
        NodeFila *temp = atual;
        atual = atual->next;
        free(temp);
    }
    free(filaOriginal);

    return 0;
}
