#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

void fillArr(int *const arr, int size);
void printArr(int *const arr, int size);

int main() {

  int size;
  printf("Enter the size : ");
  scanf("%d", &size);

  if (size <= 0) {
    printf("Invalid input! ");
    return 1;
  }

  int *const arr = mmap(NULL, sizeof(int) * size, PROT_READ | PROT_WRITE,
                        MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  if (arr == MAP_FAILED) {
    printf("Momory allocation failed ");
    return 1;
  }
  fillArr(arr, size);
  printArr(arr, size);
  munmap(arr, sizeof(int) * size);
  return 0;
}

void fillArr(int *const arr, int size) {
  if (size == 0)
    return;
  printf("Enter the element: ");
  scanf("%d", arr);
  printf("\n");
  fillArr(arr + 1, size - 1);
}

void printArr(int *const arr, int size) {
  if (size == 0)
    return;
  printf("%d ", *arr);
  printArr(arr + 1, size - 1);
}
