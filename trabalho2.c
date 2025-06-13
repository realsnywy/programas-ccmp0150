#include <stdio.h>
#include <stdlib.h>

// Protótipos das funções de ordenação e utilitários
void shellsort(int arr[], int n);
void mergesort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void printArray(int arr[], int size);

int main()
{
  int arr_shell[] = {12, 34, 54, 2, 3, 7, 5, 9, 8};
  int n_shell = sizeof(arr_shell) / sizeof(arr_shell[0]);

  printf("### Demonstração do Shellsort ###\n");
  printf("Array original: ");
  printArray(arr_shell, n_shell);
  printf("\nIniciando o Shellsort...\n");
  shellsort(arr_shell, n_shell);
  printf("\nArray final ordenado pelo Shellsort: ");
  printArray(arr_shell, n_shell);

  printf("\n--------------------------------------------\n\n");

  int arr_merge[] = {12, 34, 54, 2, 3, 7, 5, 9, 8};
  int n_merge = sizeof(arr_merge) / sizeof(arr_merge[0]);

  printf("### Demonstração do Mergesort ###\n");
  printf("Array original: ");
  printArray(arr_merge, n_merge);
  printf("\nIniciando o Mergesort...\n");
  mergesort(arr_merge, 0, n_merge - 1);
  printf("\nArray final ordenado pelo Mergesort: ");
  printArray(arr_merge, n_merge);

  return 0;
}

// Imprime todos os elementos de um array na mesma linha
void printArray(int arr[], int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// Ordena um array usando o algoritmo Shellsort
void shellsort(int arr[], int n)
{
  for (int gap = n / 2; gap > 0; gap /= 2)
  {
    printf("\nGap atual = %d\n", gap);
    // Para cada elemento a partir do índice 'gap', aplica inserção considerando o intervalo
    for (int i = gap; i < n; i++)
    {
      int temp = arr[i];
      int j;
      // Move elementos maiores que temp para frente, considerando o gap
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
      {
        arr[j] = arr[j - gap];
      }
      arr[j] = temp;
    }
    printf("Array após o gap %d: ", gap);
    printArray(arr, n);
  }
}

// Ordena recursivamente um array usando o algoritmo Mergesort
void mergesort(int arr[], int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;

    // Mostra a divisão atual do array
    printf("Dividindo: ");
    for (int i = l; i <= r; i++)
      printf("%d ", arr[i]);
    printf("\n");

    mergesort(arr, l, m);
    mergesort(arr, m + 1, r);

    // Mostra as duas metades antes de intercalar
    printf("Intercalando as metades: ");
    for (int i = l; i <= m; i++)
      printf("%d ", arr[i]);
    printf("e ");
    for (int i = m + 1; i <= r; i++)
      printf("%d ", arr[i]);
    printf("\n");

    merge(arr, l, m, r);

    // Mostra o resultado da intercalação
    printf("Resultado da intercalação: ");
    printArray(&arr[l], r - l + 1);
  }
}

// Intercala dois subarrays ordenados em um único subarray ordenado
void merge(int arr[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  // Copia os elementos para arrays temporários
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  // Combina os arrays temporários de volta ao array original
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  // Copia os elementos restantes de L[], se houver
  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  // Copia os elementos restantes de R[], se houver
  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}
