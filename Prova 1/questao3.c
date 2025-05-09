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

void insertrFinal(LinkedList *lista, int valor)
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

void empilhar(Stack *pilha, int valor)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->data = valor;
    newNode->next = pilha->top;
    pilha->top = newNode;
}

int desempilhar(Stack *pilha)
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
    Node *atual = lista->head;

    // Empilhar todos os elementos
    while (atual != NULL)
    {
        empilhar(pilha, atual->data);
        atual = atual->next;
    }

    // Comparar com a lista
    atual = lista->head;
    while (atual != NULL)
    {
        if (atual->data != desempilhar(pilha))
        {
            liberarPilha(pilha);
            return false;
        }
        atual = atual->next;
    }

    liberarPilha(pilha);
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
        desempilhar(pilha);
    }
    free(pilha);
}

int main()
{
    // Teste 1: Palindrome
    LinkedList *lista1 = criarLista();
    insertrFinal(lista1, 1);
    insertrFinal(lista1, 2);
    insertrFinal(lista1, 2);
    insertrFinal(lista1, 1);
    printf("Lista 1 eh palindrome? %s\n", ehPalindromoLista(lista1) ? "Sim" : "Nao");
    liberarLista(lista1);

    // Teste 2: Não palindrome
    LinkedList *lista2 = criarLista();
    insertrFinal(lista2, 1);
    insertrFinal(lista2, 2);
    insertrFinal(lista2, 3);
    printf("Lista 2 eh palindrome? %s\n", ehPalindromoLista(lista2) ? "Sim" : "Nao");
    liberarLista(lista2);

    // Teste 3: Palindrome com comprimento impar
    LinkedList *lista3 = criarLista();
    insertrFinal(lista3, 1);
    insertrFinal(lista3, 2);
    insertrFinal(lista3, 1);
    printf("Lista 3 eh palindrome? %s\n", ehPalindromoLista(lista3) ? "Sim" : "Nao");
    liberarLista(lista3);

    // Teste 4: Lista vazia
    LinkedList *lista4 = criarLista();
    printf("Lista 4 eh palindrome? %s\n", ehPalindromoLista(lista4) ? "Sim" : "Nao");
    liberarLista(lista4);

    // Teste 5: Lista com um elemento
    LinkedList *lista5 = criarLista();
    insertrFinal(lista5, 5);
    printf("Lista 5 eh palindrome? %s\n", ehPalindromoLista(lista5) ? "Sim" : "Nao");
    liberarLista(lista5);

    return 0;
}
