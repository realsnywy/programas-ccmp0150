#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>   // Para isdigit
#include <stdbool.h> // Para bool, true, false

// --- Constantes ---
#define BLOCK_SIZE_DIGITS 5
#define BLOCK_BASE 100000L // 10^BLOCK_SIZE_DIGITS

// --- Estrutura do Nó ---
typedef struct Node
{
  long int info;      // Bloco de dígitos (ou contagem/sinal no nó cabeça)
  struct Node *left;  // Ponteiro para o nó mais significativo / anterior
  struct Node *right; // Ponteiro para o nó menos significativo / próximo
} Node;

typedef Node *NODEPTR;

// --- Protótipos das Funções ---
NODEPTR createNode(long int value);
void insertLeft(NODEPTR list, long int value);
void deleteNode(NODEPTR node); // Simplesmente remove o nó da lista
void freeList(NODEPTR list);
NODEPTR stringToList(const char *str);
void printList(NODEPTR list);
int compabs(NODEPTR p, NODEPTR q);
NODEPTR addiff(NODEPTR p, NODEPTR q);
NODEPTR addsame(NODEPTR p, NODEPTR q);
NODEPTR addint(NODEPTR p, NODEPTR q);

// --- Funções Auxiliares ---

// Cria um novo nó isolado
NODEPTR createNode(long int value)
{
  NODEPTR newNode = (NODEPTR)malloc(sizeof(Node));
  if (!newNode)
  {
    perror("Erro ao alocar memoria para o no");
    exit(EXIT_FAILURE);
  }
  newNode->info = value;
  newNode->left = newNode; // Inicialmente aponta para si mesmo
  newNode->right = newNode;
  return newNode;
}

// Insere um novo nó com 'value' à esquerda de 'list' (geralmente o nó cabeça)
void insertLeft(NODEPTR list, long int value)
{
  NODEPTR newNode = createNode(value);
  newNode->right = list;
  newNode->left = list->left;
  list->left->right = newNode;
  list->left = newNode;
}

// Remove 'node' da lista (não libera memória, apenas desliga os ponteiros)
void deleteNode(NODEPTR node)
{
  if (node && node->left != node && node->right != node)
  { // Garante que não é um nó isolado ou cabeça de lista vazia
    node->left->right = node->right;
    node->right->left = node->left;
    // O nó agora está isolado, quem chamou deve liberar com free()
  }
}

// Libera todos os nós de uma lista, incluindo o nó cabeça
void freeList(NODEPTR list)
{
  if (!list)
    return;
  NODEPTR current = list->right;
  while (current != list)
  {
    NODEPTR next = current->right;
    free(current);
    current = next;
  }
  free(list); // Libera o nó cabeça
}

// Converte uma string em uma lista de inteiros longos
NODEPTR stringToList(const char *str)
{
  NODEPTR list = createNode(0); // Nó cabeça, info será a contagem/sinal
  int len = strlen(str);
  int start = 0;
  int sign = 1;
  long count = 0;

  if (len == 0 || (len == 1 && str[0] == '-'))
  {
    // String vazia ou apenas "-", representa 0
    list->info = 0; // Contagem 0
    return list;
  }

  if (str[0] == '-')
  {
    sign = -1;
    start = 1;
  }
  else if (str[0] == '+')
  {
    start = 1;
  }

  // Verifica se todos os caracteres restantes são dígitos
  for (int i = start; i < len; i++)
  {
    if (!isdigit(str[i]))
    {
      fprintf(stderr, "Erro: Numero invalido '%s'\n", str);
      freeList(list);
      return NULL; // Retorna NULL para indicar erro
    }
  }

  // Processa a string da direita para a esquerda (menos significativo para mais significativo)
  for (int i = len - 1; i >= start; i -= BLOCK_SIZE_DIGITS)
  {
    char blockStr[BLOCK_SIZE_DIGITS + 1];
    int blockLen = 0;
    int blockStart = i - BLOCK_SIZE_DIGITS + 1;
    if (blockStart < start)
    {
      blockStart = start;
    }
    blockLen = i - blockStart + 1;

    strncpy(blockStr, str + blockStart, blockLen);
    blockStr[blockLen] = '\0';

    long blockValue = atol(blockStr);
    insertLeft(list, blockValue); // Insere à esquerda do cabeça (constrói na ordem correta)
    count++;
  }

  list->info = count * sign; // Armazena contagem e sinal
  return list;
}

// Imprime a lista como um inteiro longo
void printList(NODEPTR list)
{
  if (!list || list->info == 0 || list->right == list)
  {
    printf("0");
    return;
  }

  if (list->info < 0)
  {
    printf("-");
  }

  NODEPTR current = list->left; // Começa pelo mais significativo
  // Imprime o primeiro bloco sem preenchimento extra
  printf("%ld", current->info);
  current = current->left;

  // Imprime os blocos restantes com preenchimento de zeros
  while (current != list)
  {
    printf("%0*ld", BLOCK_SIZE_DIGITS, current->info); // Garante 5 dígitos
    current = current->left;
  }
}

// --- Funções dos Esboços ---

// Esboço 1: Compara valores absolutos
int compabs(NODEPTR p, NODEPTR q)
{
  NODEPTR r, s;
  long p_count = labs(p->info); // Usa labs para long int
  long q_count = labs(q->info);

  /* compara as contagens */
  if (p_count > q_count)
    return (1);
  if (p_count < q_count)
    return (-1);

  /* as contagens sao iguais */
  if (p_count == 0)
    return 0; // Ambos são zero

  r = p->left; // Nó mais significativo de p
  s = q->left; // Nó mais significativo de q

  /* percorre a lista a partir dos dígitos mais significativos */
  while (r != p)
  { // Poderia ser `while (p_count > 0)` também
    if (r->info > s->info)
      return (1);
    if (r->info < s->info)
      return (-1);
    r = r->left;
    s = s->left;
    // p_count--; // Se usasse a contagem no loop
  } /* fim while */

  /* os valores absolutos sao iguais */
  return (0);
}

// Esboço 2: Subtrai q de p (assume |p| >= |q|)
NODEPTR addiff(NODEPTR p, NODEPTR q)
{
  long count = 0;
  NODEPTR pptr, qptr, r, s, temp_node_to_delete;
  long borrow = 0;
  long diff;
  bool leading_zeros = true; // Flag para rastrear zeros à esquerda

  /* gera um noh de cabecalho para a diferenca */
  r = createNode(0); // Info será definido no final

  /* percorre as duas listas a partir do menos significativo */
  pptr = p->right;
  qptr = q->right;

  // Processa enquanto ambos p e q têm blocos
  while (qptr != q)
  {
    diff = pptr->info - borrow - qptr->info;
    if (diff >= 0)
    {
      borrow = 0;
    }
    else
    {
      diff = diff + BLOCK_BASE;
      borrow = 1;
    } /* fim if */

    insertLeft(r, diff); // Insere o bloco resultante
    count++;

    pptr = pptr->right;
    qptr = qptr->right;
  } /* fim while */

  /* percorre o restante da lista p (se houver) */
  while (pptr != p)
  {
    diff = pptr->info - borrow;
    if (diff >= 0)
    {
      borrow = 0;
    }
    else
    {
      diff = diff + BLOCK_BASE;
      borrow = 1;
    } /* fim if */

    insertLeft(r, diff);
    count++;

    pptr = pptr->right;
  } /* fim while */

  // Remove zeros à esquerda do resultado 'r'
  // Percorre do mais significativo (r->left) para o menos significativo
  NODEPTR current = r->left;
  long original_count = count;
  for (long i = 0; i < original_count && current != r; ++i)
  {
    NODEPTR next = current->left; // Guarda o próximo antes de deletar
    if (current->info == 0 && count > 1)
    { // Não remove o último bloco se for 0
      temp_node_to_delete = current;
      deleteNode(temp_node_to_delete);
      free(temp_node_to_delete); // Libera memória do nó removido
      count--;
    }
    else
    {
      // Encontrou o primeiro dígito não zero, para de remover
      break;
    }
    current = next; // Vai para o próximo (originalmente à esquerda)
  }

  /* insere contagem e sinal no cabecalho */
  // O sinal do resultado de p - q (onde |p| >= |q|) é o sinal de p
  if (p->info > 0)
    r->info = count;
  else
    r->info = -count;

  // Caso especial: se o resultado for 0 após remover zeros
  if (count == 1 && r->left->info == 0)
  {
    r->info = 0; // Representa 0 corretamente
  }

  return (r);
} /* fim addiff */

// Função Faltante: Adiciona p e q (assume mesmo sinal)
NODEPTR addsame(NODEPTR p, NODEPTR q)
{
  long count = 0;
  NODEPTR pptr, qptr, r;
  long carry = 0;
  long sum;

  /* gera um noh de cabecalho para a soma */
  r = createNode(0); // Info será definido no final

  /* percorre as duas listas a partir do menos significativo */
  pptr = p->right;
  qptr = q->right;

  // Processa enquanto ambos p e q têm blocos
  while (pptr != p && qptr != q)
  {
    sum = pptr->info + qptr->info + carry;
    carry = sum / BLOCK_BASE;
    sum = sum % BLOCK_BASE;

    insertLeft(r, sum); // Insere o bloco resultante
    count++;

    pptr = pptr->right;
    qptr = qptr->right;
  } /* fim while */

  // Processa o restante da lista mais longa (se houver)
  NODEPTR remaining = (pptr != p) ? pptr : qptr;
  NODEPTR list_end = (pptr != p) ? p : q;

  while (remaining != list_end)
  {
    sum = remaining->info + carry;
    carry = sum / BLOCK_BASE;
    sum = sum % BLOCK_BASE;

    insertLeft(r, sum);
    count++;

    remaining = remaining->right;
  }

  // Se houver um carry final, adiciona um novo bloco
  if (carry > 0)
  {
    insertLeft(r, carry);
    count++;
  }

  /* insere contagem e sinal no cabecalho */
  // O sinal do resultado é o mesmo de p (ou q, já que têm o mesmo sinal)
  if (p->info >= 0) // Se p é positivo (ou zero) - corrigido para >= 0
    r->info = count;
  else // Se p é negativo
    r->info = -count;

  // Caso especial: Se a soma for zero (embora raro com addsame se inputs != 0)
  // Mas pode acontecer se p e q forem zero
  if (count == 0 || (count == 1 && r->left->info == 0))
  {
    // Se não adicionou blocos (p=0, q=0) ou o único bloco é 0
    r->info = 0;
    // Garante que a lista de resultado para 0 esteja vazia ou com um nó 0
    if (count == 1 && r->left->info == 0)
    {
      // Já está ok
    }
    else if (count > 1)
    {
      // Situação inesperada, mas limpa a lista por segurança se count > 1 mas resultou 0
      NODEPTR current = r->right;
      while (current != r)
      {
        NODEPTR next = current->right;
        free(current);
        current = next;
      }
      r->left = r;
      r->right = r;
    }
    count = 0; // Atualiza a contagem para 0
  }

  return (r);
}

// Esboço 3: Ponto de entrada para adição
NODEPTR addint(NODEPTR p, NODEPTR q)
{
  // Se um dos operandos for NULL (erro na conversão)
  if (!p || !q)
  {
    fprintf(stderr, "Erro: Operando invalido para addint.\n");
    return NULL;
  }

  // Trata adição com zero de forma mais robusta, criando cópia
  if (p->info == 0)
  {
    // Cria uma cópia de q
    NODEPTR q_copy = createNode(q->info);
    NODEPTR current_q = q->right;
    while (current_q != q)
    {
      insertLeft(q_copy, current_q->info);
      current_q = current_q->right;
    }
    return q_copy;
  }
  if (q->info == 0)
  {
    // Cria uma cópia de p
    NODEPTR p_copy = createNode(p->info);
    NODEPTR current_p = p->right;
    while (current_p != p)
    {
      insertLeft(p_copy, current_p->info);
      current_p = current_p->right;
    }
    return p_copy;
  }

  /* verifica se os inteiros tem sinais identicos */
  bool p_is_neg = (p->info < 0);
  bool q_is_neg = (q->info < 0);

  if (p_is_neg == q_is_neg)
  { // Sinais iguais
    return (addsame(p, q));
  }
  else
  { // Sinais diferentes
    /* verifica qual deles tem o valor absoluto maior */
    int comparison = compabs(p, q);
    if (comparison > 0)
    {                        // |p| > |q|
      return (addiff(p, q)); // Resultado tem o sinal de p
    }
    else if (comparison < 0)
    {                        // |p| < |q|
      return (addiff(q, p)); // Resultado tem o sinal de q
    }
    else
    { // |p| == |q|
      // Sinais opostos e valores absolutos iguais -> resultado é 0
      NODEPTR result = createNode(0); // Nó cabeça para zero
      result->info = 0;               // Contagem zero
      return result;
    }
  }
} /* fim addint */

// --- Função Principal ---
int main()
{
  char numStr1[1024];
  char numStr2[1024];

  printf("Calculadora de Soma de Inteiros Longos\n");
  printf("Use blocos de %d digitos.\n", BLOCK_SIZE_DIGITS);

  printf("Digite o primeiro numero: ");
  if (fgets(numStr1, sizeof(numStr1), stdin) == NULL)
  {
    fprintf(stderr, "Erro ao ler o primeiro numero.\n");
    return 1;
  }
  numStr1[strcspn(numStr1, "\n")] = 0; // Remove a nova linha

  printf("Digite o segundo numero: ");
  if (fgets(numStr2, sizeof(numStr2), stdin) == NULL)
  {
    fprintf(stderr, "Erro ao ler o segundo numero.\n");
    return 1;
  }
  numStr2[strcspn(numStr2, "\n")] = 0; // Remove a nova linha

  NODEPTR num1 = stringToList(numStr1);
  NODEPTR num2 = stringToList(numStr2);

  if (!num1 || !num2)
  {
    fprintf(stderr, "Erro ao converter numeros para listas.\n");
    freeList(num1); // Libera o que foi possível alocar
    freeList(num2);
    return 1;
  }

  printf("\nNumero 1: ");
  printList(num1);
  printf("\nNumero 2: ");
  printList(num2);
  printf("\n");

  // Chama addint para obter a soma
  NODEPTR sum = addint(num1, num2);

  if (sum)
  {
    printf("\nSoma: ");
    printList(sum);
    printf("\n");
    freeList(sum); // Libera o resultado
  }
  else
  {
    printf("\nErro durante a adicao.\n");
  }

  // Libera memória das listas originais SEMPRE
  freeList(num1);
  freeList(num2);

  return 0;
}
