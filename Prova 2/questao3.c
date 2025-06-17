#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int key;
  struct Node *prev;
  struct Node *next;
} Node;

void list_InsertRear(Node **head, int key);
void BubbleSort(Node **head);
void list_Print(Node *head);
void list_Free(Node *head);
void Test(const char *desc, int size, int values[size]);

/**
 * Insere um novo nó no final de uma lista duplamente encadeada.
 */
void list_InsertRear(Node **head, int key)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode)
    return;
  newNode->key = key;
  newNode->next = NULL;

  if (*head == NULL)
  {
    newNode->prev = NULL;
    *head = newNode;
    return;
  }

  Node *last = *head;
  while (last->next != NULL)
  {
    last = last->next;
  }

  last->next = newNode;
  newNode->prev = last;
}

/**
 * Ordena uma lista duplamente encadeada usando Bubble Sort, manipulando ponteiros.
 */
void BubbleSort(Node **head)
{
  if (*head == NULL || (*head)->next == NULL)
  {
    return;
  }

  int swapped;
  do
  {
    swapped = 0;
    Node *current = *head;
    while (current != NULL && current->next != NULL)
    {
      Node *nextNode = current->next;
      if (current->key > nextNode->key)
      {
        Node *prevNode = current->prev;
        Node *nextNextNode = nextNode->next;

        if (prevNode == NULL)
        {
          *head = nextNode;
        }
        else
        {
          prevNode->next = nextNode;
        }
        nextNode->prev = prevNode;

        nextNode->next = current;
        current->prev = nextNode;

        current->next = nextNextNode;
        if (nextNextNode != NULL)
        {
          nextNextNode->prev = current;
        }
        swapped = 1;
      }
      current = current->next;
    }
  } while (swapped);
}

void list_Print(Node *head)
{
  while (head)
  {
    printf("%d ", head->key);
    head = head->next;
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

void Test(const char *desc, int size, int values[size])
{
  printf("Teste: %s\n", desc);
  Node *L = NULL;
  for (int i = 0; i < size; i++)
  {
    list_InsertRear(&L, values[i]);
  }
  printf("Lista original: ");
  list_Print(L);
  BubbleSort(&L);
  printf("Lista ordenada: ");
  list_Print(L);
  list_Free(L);
  printf("------------------------\n");
}

int main()
{
  int reverseList[] = {5, 4, 3, 2, 1};
  Test("Lista em ordem reversa", 5, reverseList);

  int duplicates[] = {4, 2, 4, 3, 2};
  Test("Lista com elementos repetidos", 5, duplicates);

  int emptyList[] = {};
  Test("Lista vazia", 0, emptyList);

  return 0;
}
