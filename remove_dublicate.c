
#include <stdio.h>

void printArr(int *const arr, int size);
void fillArr(int *const arr, int size);
void delete(int *const arr, int *size, int index);
void removeDuplicate(int *const arr, int *size);

int main() {
  int size;
  int *ptr = &size;
  printf("Enter size: ");
  scanf("%d", ptr);

  int arr[size];
  fillArr(arr, size);
  printArr(arr, size);

  printf("\n");
  removeDuplicate(arr, ptr);
  printf("\n");
  printArr(arr, size);
  return 0;
}

void fillArr(int *const arr, int size) {
  if (size == 0)
    return;
  printf("Enter element: ");
  scanf("%d", arr);
  fillArr(arr + 1, size - 1);
}

void printArr(int *const arr, int size) {
  if (size == 0)
    return;
  printf("%d ", *arr);
  printArr(arr + 1, size - 1);
}

void delete(int *const arr, int *size, int index) {
  for (int i = index; i < *size - 1; i++)
    *(arr + i) = *(arr + i + 1);

  (*size)--;
}

void removeDuplicate(int *const arr, int *size) {

  for (int i = 0; i < *size; i++) {
    for (int j = i + 1; j < *size; j++) {
      if (*(arr + i) == *(arr + j)) {
        delete(arr, size, i);
        i--;
        break;
      }
    }
  }
}
