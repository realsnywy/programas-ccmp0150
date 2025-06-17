#include <stdio.h>

void BubbleShellSort(int n, int arr[]);
void PrintArray(int n, int arr[n]);

/**
 * Ordena um array usando o algoritmo híbrido Bubble-Shell Sort.
 */
void BubbleShellSort(int n, int arr[])
{
  for (int gap = n / 2; gap > 0; gap /= 2)
  {
    int swapped;
    do
    {
      swapped = 0;
      for (int i = 0; i + gap < n; i++)
      {
        if (arr[i] > arr[i + gap])
        {
          int temp = arr[i];
          arr[i] = arr[i + gap];
          arr[i + gap] = temp;
          swapped = 1;
        }
      }
    } while (swapped);
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
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = 7;

  printf("Array original:\n");
  PrintArray(n, arr);

  BubbleShellSort(n, arr);

  printf("Array ordenado com Bubble-Shell Sort:\n");
  PrintArray(n, arr);

  return 0;
}
