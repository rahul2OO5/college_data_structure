#include <stdio.h>

void printArr(int *const arr, int size);
void fillArr(int *const arr, int size);
int max(int first_num, int second_num);
int min(int first_num, int second_num);
void delete(int *const arr, int *size, int index);
void removeNumber(int *const arr, int *size);

int main() {
  int size;
  int *ptr = &size;
  printf("Enter size: ");
  scanf("%d", ptr);

  int arr[size];
  fillArr(arr, size);
  printArr(arr, size);

  printf("\n");
  removeNumber(arr, ptr);
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

int max(int first_num, int second_num) {
  return (first_num > second_num) ? first_num : second_num;
}

int min(int first_num, int second_num) {
  return (first_num < second_num) ? first_num : second_num;
}

void delete(int *const arr, int *size, int index) {
  for (int i = index; i < *size - 1; i++)
    *(arr + i) = *(arr + i + 1);

  (*size)--;
}

void removeNumber(int *const arr, int *size) {
  while (1) {
    int even_index = -1;
    int odd_index = -1;

    for (int i = 0; i < *size; i++) {
      if (*(arr + i) % 2 == 0 && even_index == -1)
        even_index = i;
      if (*(arr + i) % 2 != 0 && odd_index == -1)
        odd_index = i;
      if (even_index != -1 && odd_index != -1)
        break;
    }

    if (even_index == -1)
      break;

    int add = *(arr + even_index) + *(arr + odd_index);
    int big_num = max(even_index, odd_index);
    int small_num = min(even_index, odd_index);

    *(arr + big_num) = add;
    delete(arr, size, small_num);

    even_index = -1;
    odd_index = -1;

    for (int i = *size - 1; i >= 0; i--) {
      if (*(arr + i) % 2 == 0 && even_index == -1)
        even_index = i;
      if (*(arr + i) % 2 != 0 && odd_index == -1)
        odd_index = i;
      if (even_index != -1 && odd_index != -1)
        break;
    }

    if (even_index == -1)
      break;

    int add1 = *(arr + even_index) + *(arr + odd_index);
    int big_num1 = max(even_index, odd_index);
    int small_num1 = min(even_index, odd_index);

    *(arr + small_num1) = add1;
    delete(arr, size, big_num1);
  }
}
