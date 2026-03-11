#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER 20
#define BASE 10

typedef struct {
  int length;
  int arr[];
} Array;

static int Sscan();
static void displayArr(Array *arr);
static void fillArr(Array *arr);
static void reverse(Array *arr, int start, int end);
static void leftRotate(Array *arr, int position);
static void rightRotate(Array *arr, int position);

int main() {

  int size = 0;
  int position = 0;
  printf("Enter the size of array: ");
  size = Sscan();
  printf("\n");

  if (size <= 0) {
    printf("Enter the bigger size");
    return 1;
  }
  printf("Enter the position from which it will rotate: ");
  position = Sscan();
  printf("\n");

  if (position < 0) {
    printf("Enter the positive number");
    return 1;
  }

  Array *arr = malloc(sizeof(Array) + (size * sizeof(int)));
  if (arr == NULL) {
    printf("memory allocation failed!");
    return 1;
  }

  arr->length = size;

  fillArr(arr);
  printf("\n");
  printf("Array before rotation\n");
  displayArr(arr);
  printf("\n");

  printf("Array after rotating left\n");
  leftRotate(arr, position);
  displayArr(arr);
  printf("\n");

  printf("Array after rotation right\n");
  rightRotate(arr, position);
  displayArr(arr);
  printf("\n");

  free(arr);
  printf("\n");
  return 0;
}

int Sscan() {
  char buffer[BUFFER];
  if ((fgets(buffer, sizeof(buffer), stdin)) == NULL) {
    return 0;
  }
  return (int)strtol(buffer, NULL, BASE);
}

void fillArr(Array *arr) {
  int counter = 0;
  for (counter = 0; counter < arr->length; counter++) {
    printf("Enter element: ");
    *(arr->arr + counter) = Sscan();
  }
}

void displayArr(Array *arr) {
  for (int counter = 0; counter < arr->length; counter++) {
    printf("%d ", *(arr->arr + counter));
  }
}

void reverse(Array *arr, int start, int end) {
  while (start < end) {
    int temp = arr->arr[start];
    arr->arr[start] = arr->arr[end];
    arr->arr[end] = temp;
    start++;
    end--;
  }
}

void leftRotate(Array *arr, int position) {
  if (position == 0) {
    return;
  }

  position = position % arr->length;

  reverse(arr, 0, position - 1);
  reverse(arr, position, arr->length - 1);
  reverse(arr, 0, arr->length - 1);
}

void rightRotate(Array *arr, int position) {
  if (position == 0) {
    return;
  }

  position = position % arr->length;

  reverse(arr, arr->length - position, arr->length - 1);
  reverse(arr, 0, arr->length - position - 1);
  reverse(arr, 0, arr->length - 1);
}
