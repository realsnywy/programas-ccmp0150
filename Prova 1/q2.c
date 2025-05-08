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

Fila *inverterFileCompilhas(Fila *f)
{
    Fila *filaOriginal = criarFila();
    Fila *filaInvertida = criarFila();
    Pilha *pilhaAux = criarPilha();

    // Copiar a fila original para não modificá-la
    NodeFila *atual = f->front;
    while (atual != NULL)
    {
        enfileirar(filaOriginal, atual->data);
        atual = atual->next;
    }

    // Transferir elementos da fila original para a pilha
    while (!filaVazia(filaOriginal))
    {
        empilhar(pilhaAux, desenfileirar(filaOriginal));
    }

    // Transferir elementos da pilha para a fila invertida
    while (!pilhaVazia(pilhaAux))
    {
        enfileirar(filaInvertida, desempilhar(pilhaAux));
    }

    // Liberar memória auxiliar
    free(filaOriginal);
    free(pilhaAux);

    return filaInvertida;
}
