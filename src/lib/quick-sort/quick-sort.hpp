#pragma once

// Função auxiliar para trocar dois elementos
template <typename T>
void swap(T *a, T *b)
{
  T temp = *a;
  *a = *b;
  *b = temp;
}

// Função que realiza a partição e retorna o índice do pivô
template <typename T>
int partition(T arr[], int low, int high)
{
  T pivot = arr[high]; // Escolhe o último elemento como pivô
  int i = (low - 1);   // Índice do menor elemento

  for (int j = low; j < high; j++)
  {
    // Se o elemento atual é menor ou igual ao pivô
    if (arr[j] <= pivot)
    {
      i++; // Incrementa o índice do menor elemento
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

// Função principal do Quick Sort
template <typename T>
void quickSort(T arr[], int low, int high)
{
  if (low < high)
  {
    // Índice de partição
    int pi = partition(arr, low, high);

    // Ordena os elementos antes e depois da partição
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}