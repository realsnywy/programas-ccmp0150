#include <stdio.h>

#define MAX 100

int Partition(int arr[], int low, int high);
void Quicksort(int n, int arr[n]);
void PrintArray(int n, int arr[n]);

/**
 * Particiona o sub-array usando o esquema de Lomuto.
 */
int Partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;

  return (i + 1);
}

/**
 * Ordena um array usando Quicksort iterativo.
 */
void Quicksort(int n, int arr[n])
{
  int stack[MAX];
  int top = -1;
  int low, high, p;

  if (n > 1)
  {
    stack[++top] = 0;
    stack[++top] = n - 1;
  }

  while (top >= 0)
  {
    high = stack[top--];
    low = stack[top--];

    p = Partition(arr, low, high);

    if (p - 1 > low)
    {
      stack[++top] = low;
      stack[++top] = p - 1;
    }

    if (p + 1 < high)
    {
      stack[++top] = p + 1;
      stack[++top] = high;
    }
  }
}

void PrintArray(int n, int arr[n])
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main()
{
  int v[] = {29, 10, 14, 37, 13, 5, 2, 18};
  int n = 8;

  printf("Vetor original:\n");
  PrintArray(n, v);

  Quicksort(n, v);

  printf("Vetor ordenado:\n");
  PrintArray(n, v);

  return 0;
}
