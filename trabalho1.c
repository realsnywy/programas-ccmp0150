#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó para a lista encadeada (usada no encadeamento)
typedef struct Node
{
  int key;
  struct Node *next;
} Node;

// Estrutura da Tabela de Espalhamento
typedef struct HashTable
{
  int size;     // Tamanho da tabela (número de posições no array)
  Node **table; // Array de ponteiros para os nós (listas encadeadas)
} HashTable;

// Cria e aloca um novo nó com a chave fornecida
Node *createNode(int key)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode)
  {
    perror("Erro ao alocar memoria para o no");
    exit(EXIT_FAILURE);
  }
  newNode->key = key;
  newNode->next = NULL;
  return newNode;
}

// Cria e inicializa uma Tabela de Espalhamento com o tamanho especificado
HashTable *createHashTable(int size)
{
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (!ht)
  {
    perror("Erro ao alocar memoria para a tabela de espalhamento");
    exit(EXIT_FAILURE);
  }
  ht->size = size;
  ht->table = (Node **)malloc(sizeof(Node *) * size);
  if (!ht->table)
  {
    perror("Erro ao alocar memoria para o array da tabela");
    free(ht);
    exit(EXIT_FAILURE);
  }

  // Inicializa cada posição da tabela com NULL
  for (int i = 0; i < size; i++)
  {
    ht->table[i] = NULL;
  }
  return ht;
}

// Função de espalhamento que calcula o índice para uma chave
int hashFunction(int key, int size)
{
  // Usa o resto da divisão para determinar o índice
  return key % size;
}

// Insere uma chave na Tabela de Espalhamento usando encadeamento para colisões
void insert(HashTable *ht, int key)
{
  int index = hashFunction(key, ht->size);
  printf("~~~ INSERINDO CHAVE %d ~~~\n", key);
  printf("Calculando indice para a chave %d: %d %% %d = %d\n", key, key, ht->size, index);

  Node *newNode = createNode(key);

  // Se a posição está vazia, insere o novo nó
  if (ht->table[index] == NULL)
  {
    printf("Posicao %d estava vazia. Chave %d inserida.\n\n", index, key);
    ht->table[index] = newNode;
  }
  else
  {
    // Se já existe um elemento (colisão), adiciona o novo nó no início da lista
    printf("COLISAO detectada na posicao %d! Aplicando encadeamento.\n", index);
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    printf("Chave %d inserida no inicio da lista na posicao %d.\n\n", key, index);
  }
}

// Busca uma chave na Tabela de Espalhamento
void search(HashTable *ht, int key)
{
  int index = hashFunction(key, ht->size);
  printf("~~~ BUSCANDO CHAVE %d ~~~\n", key);
  printf("Calculando indice para a chave %d: %d %% %d = %d\n", key, key, ht->size, index);

  Node *current = ht->table[index];
  int position = 0;

  // Percorre a lista encadeada na posição do índice
  while (current != NULL)
  {
    printf("Verificando no na lista da posicao %d. Chave do no: %d\n", index, current->key);
    if (current->key == key)
    {
      printf("SUCESSO: Chave %d encontrada na posicao %d da tabela (no %d da lista).\n\n", key, index, position);
      return;
    }
    current = current->next;
    position++;
  }

  printf("FALHA: Chave %d NAO encontrada na tabela.\n\n", key);
}

// Imprime o conteúdo da Tabela de Espalhamento
void printTable(HashTable *ht)
{
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("      ESTADO ATUAL DA TABELA\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  for (int i = 0; i < ht->size; i++)
  {
    printf("Indice [%d]: ", i);
    Node *current = ht->table[i];
    if (current == NULL)
    {
      printf("-> VAZIO\n");
    }
    else
    {
      while (current != NULL)
      {
        printf("-> [ %d ] ", current->key);
        current = current->next;
      }
      printf("\n");
    }
  }
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

// Libera toda a memória alocada para a Tabela de Espalhamento
void freeTable(HashTable *ht)
{
  for (int i = 0; i < ht->size; i++)
  {
    Node *current = ht->table[i];
    while (current != NULL)
    {
      Node *temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(ht->table);
  free(ht);
}

// Função principal para demonstrar o uso da Tabela de Espalhamento
int main()
{
  // Define o tamanho da tabela (um número primo é uma boa escolha)
  int table_size = 7;
  HashTable *ht = createHashTable(table_size);

  printf("Tabela de Espalhamento criada com tamanho %d.\n\n", table_size);
  printTable(ht);

  // Demonstração de inserções
  insert(ht, 10);
  insert(ht, 20);
  insert(ht, 3);

  // Inserindo chave que causa colisão com a chave 10 (17 % 7 = 3 e 10 % 7 = 3)
  insert(ht, 17);
  printTable(ht);

  // Inserindo mais chaves
  insert(ht, 8);
  insert(ht, 21); // Colisão com 7, 14, etc. (índice 0)
  insert(ht, 15); // Colisão com 1, 8, etc. (índice 1)
  printTable(ht);

  // Demonstração de buscas
  search(ht, 10); // Busca com sucesso
  search(ht, 17); // Busca com sucesso (item em uma lista)
  search(ht, 50); // Busca com falha
  search(ht, 21); // Busca com sucesso
  search(ht, 1);  // Busca com falha (índice 1, mas chave não está na lista)

  // Libera a memória alocada
  freeTable(ht);
  printf("Memoria da tabela liberada com sucesso.\n");

  return 0;
}
