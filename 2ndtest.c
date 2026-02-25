#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int length;
  int arr[];
} Array;

void printArr(Array *ptr);
void fillArr(Array *ptr);

int main() {

  int size;
  printf("Enter the size of array : ");
  scanf("%d", &size);
  Array *ptr = malloc(sizeof(Array) + size * sizeof(int));
  if (ptr == NULL) {
    printf("Memory allocation failed ! ");
    return 1;
  }
  ptr->length = size;

  fillArr(ptr);
  printf("\n");
  printArr(ptr);
  free(ptr);
  printf("\n");
  return 0;
}

void fillArr(Array *ptr) {
  int i = 0;
  for (i = 0; i < ptr->length; i++) {
    printf("Enter the element at postion %d: ", i + 1);
    scanf("%d", ptr->arr + i);
  }
}

void printArr(Array *ptr) {
  int i = 0;
  for (i = 0; i < ptr->length; i++) {
    printf("%d ", *(ptr->arr + i));
  }
}
