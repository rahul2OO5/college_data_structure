#include <stdio.h>

void value(int *arr, int *array, int left, int right, int buffer_value,
           int size) {
  int mid = (left + right) / 2;

  if (left == mid || right == mid)
    return;

  int positon = buffer_value + 2;

  if (positon < size)
    array[mid] = arr[positon];
  else
    return;

  value(arr, array, left, mid, 2 * buffer_value + 1, size);
  value(arr, array, mid, right, 2 * buffer_value + 2, size);
}

void fillArr(int *arr, int size) {
  if (size == 0)
    return;
  printf("Enter element : ");
  scanf("%d", arr);
  fillArr(arr + 1, size - 1);
}

void printArr(int *arr, int size) {
  if (size == 0)
    return;
  printf("%d ", *arr);
  printArr(arr + 1, size - 1);
}

int main() {
  int size;
  printf("Enter the size of array ");
  scanf("%d", &size);
  printf("\n");
  int arr[size];
  int array[size];

  fillArr(arr, size);
  printArr(arr, size);
  printf("\n");

  array[0] = arr[0];
  if (size > 1) {
    array[size - 1] = arr[1];
    array[size - 2] = arr[size - 1];
  }

  printf("\n");
  value(arr, array, 0, size - 1, 0, size);

  printArr(array, size);

  return 0;
}
