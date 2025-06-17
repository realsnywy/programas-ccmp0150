#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int key;
  struct Node *prev;
  struct Node *next;
} Node;

void list_InsertSorted(Node **head, int key);
Node *list_GetNodeAt(Node *head, int index);
Node *BinarySearch(Node *head, int key);
int list_GetSize(Node *head);
void list_Print(Node *head);
void list_Free(Node *head);

/**
 * Insere um novo nó em uma lista duplamente encadeada de forma ordenada.
 */
void list_InsertSorted(Node **head, int key)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode)
    return;
  newNode->key = key;
  newNode->prev = NULL;
  newNode->next = NULL;

  if (*head == NULL)
  {
    *head = newNode;
    return;
  }

  if (key < (*head)->key)
  {
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
    return;
  }

  Node *current = *head;
  while (current->next != NULL && current->next->key < key)
  {
    current = current->next;
  }

  newNode->next = current->next;
  if (current->next != NULL)
  {
    current->next->prev = newNode;
  }
  current->next = newNode;
  newNode->prev = current;
}

/**
 * Retorna o ponteiro para o nó na posição 'index' da lista.
 */
Node *list_GetNodeAt(Node *head, int index)
{
  Node *current = head;
  int count = 0;
  while (current != NULL && count < index)
  {
    current = current->next;
    count++;
  }
  return current;
}

/**
 * Realiza uma busca binária iterativa em uma lista duplamente encadeada ordenada.
 */
Node *BinarySearch(Node *head, int key)
{
  int size = list_GetSize(head);
  int low = 0;
  int high = size - 1;
  Node *midNode = NULL;

  while (low <= high)
  {
    int mid = low + (high - low) / 2;
    midNode = list_GetNodeAt(head, mid);

    if (midNode == NULL)
      return NULL;

    if (midNode->key == key)
    {
      return midNode;
    }

    if (midNode->key < key)
    {
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }
  return NULL;
}

int list_GetSize(Node *head)
{
  int size = 0;
  while (head)
  {
    size++;
    head = head->next;
  }
  return size;
}

void list_Print(Node *head)
{
  Node *current = head;
  while (current)
  {
    printf("%d ", current->key);
    current = current->next;
  }
  printf("\n");
}

void list_Free(Node *head)
{
  while (head)
  {
    Node *temp = head;
    head = head->next;
    free(temp);
  }
}

int main()
{
  Node *head = NULL;
  list_InsertSorted(&head, 30);
  list_InsertSorted(&head, 10);
  list_InsertSorted(&head, 20);
  list_InsertSorted(&head, 40);
  list_InsertSorted(&head, 25);

  printf("Lista ordenada:\n");
  list_Print(head); // Saida Esperada: 10 20 25 30 40

  printf("\nTestes de busca binaria:\n");
  int searchKeys[] = {25, 10, 35, 40, 5};
  for (int i = 0; i < 5; i++)
  {
    Node *result = BinarySearch(head, searchKeys[i]);
    if (result)
    {
      printf("Chave %d encontrada no no com endereco %p\n", searchKeys[i], (void *)result);
    }
    else
    {
      printf("Chave %d nao encontrada.\n", searchKeys[i]);
    }
  }

  list_Free(head);
  return 0;
}
