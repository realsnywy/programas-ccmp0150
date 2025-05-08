#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
} LinkedList;

LinkedList *criarLista()
{
    LinkedList *lista = (LinkedList *)malloc(sizeof(LinkedList));
    lista->head = NULL;
    return lista;
}

void insertFinal(LinkedList *lista, int valor)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = valor;
    newNode->next = NULL;

    if (lista->head == NULL)
    {
        lista->head = newNode;
    }
    else
    {
        Node *atual = lista->head;
        while (atual->next != NULL)
        {
            atual = atual->next;
        }
        atual->next = newNode;
    }
}

typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *top;
} Stack;

Stack *criarPilha()
{
    Stack *pilha = (Stack *)malloc(sizeof(Stack));
    pilha->top = NULL;
    return pilha;
}

void empilharStack(Stack *pilha, int valor)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->data = valor;
    newNode->next = pilha->top;
    pilha->top = newNode;
}

int desempilharStack(Stack *pilha)
{
    if (pilha->top == NULL)
        return -1;

    StackNode *temp = pilha->top;
    int data = temp->data;
    pilha->top = pilha->top->next;
    free(temp);
    return data;
}

bool pilhaVazia(Stack *pilha)
{
    return pilha->top == NULL;
}

bool ehPalindromoLista(LinkedList *lista)
{
    if (lista->head == NULL || lista->head->next == NULL)
    {
        return true;
    }

    Stack *pilha = criarPilha();
    Node *slow = lista->head;
    Node *fast = lista->head;

    // Empilhar a primeira metade dos elementos
    while (fast != NULL && fast->next != NULL)
    {
        empilharStack(pilha, slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }

    // Se o número de elementos for ímpar, pular o elemento do meio
    if (fast != NULL)
    {
        slow = slow->next;
    }

    // Comparar a segunda metade com os elementos desempilhados
    while (slow != NULL)
    {
        if (desempilharStack(pilha) != slow->data)
        {
            free(pilha);
            return false;
        }
        slow = slow->next;
    }

    free(pilha);
    return true;
}

void liberarLista(LinkedList *lista)
{
    Node *atual = lista->head;
    while (atual != NULL)
    {
        Node *temp = atual;
        atual = atual->next;
        free(temp);
    }
    free(lista);
}

void liberarPilha(Stack *pilha)
{
    while (!pilhaVazia(pilha))
    {
        desempilharStack(pilha);
    }
    free(pilha);
}
