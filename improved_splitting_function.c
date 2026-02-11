#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct {
  int left;
  int right;
} buffer;

void putNumber(int number);
void cPrint(const char *format, ...);
void fillArr(int *const arr, int size);
void printArr(const int *const arr, int size);
int input(int *num);
void pattern(int size, int *const source, int *const destination);

int main() {
  int size;
  int *ptr = &size;
  size = input(ptr);
  cPrint("\n");

  int *source = mmap(NULL, sizeof(int) * size, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  int *destination = mmap(NULL, sizeof(int) * size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (source == MAP_FAILED || destination == MAP_FAILED) {
    cPrint("Memory allocation failed!");
    return -1;
  }

  fillArr(source, size);
  cPrint("\n");
  printArr(source, size);
  cPrint("\n");

  pattern(size, source, destination);
  printArr(destination, size);
  cPrint("\n");

  munmap(source, sizeof(int) * size);
  munmap(destination, sizeof(int) * size);
  return 0;
}

void putNumber(int number) {
  if (number < 0) {
    write(1, "-", 1);
    number = -number;
  }
  if (number >= 10) {
    putNumber(number / 10);
  }
  char digit = (number % 10) + '0';
  write(1, &digit, 1);
}

void cPrint(const char *format, ...) {
  va_list args;
  va_start(args, format);
  for (int i = 0; format[i] != '\0'; i++) {
    if (format[i] == '%') {
      i++;
      if (format[i] == '\0')
        break;
      if (format[i] == 'd') {
        int value = va_arg(args, int);
        putNumber(value);
      } else if (format[i] == 's') {
        char *str = va_arg(args, char *);
        int len = 0;
        while (str[len])
          len++;
        write(1, str, len);
      } else {
        write(1, &format[i], 1);
      }
    } else {
      write(1, &format[i], 1);
    }
  }
  va_end(args);
}

void fillArr(int *const arr, int size) {
  if (size == 0)
    return;
  char temp[20];
  cPrint("Enter Element: ");
  fflush(stdout);
  int bytes = read(0, temp, 19);
  if (bytes > 0) {
    temp[bytes] = '\0';
    *arr = atoi(temp);
  }
  cPrint("\n");
  fillArr(arr + 1, size - 1);
}

void printArr(const int *const arr, int size) {
  if (size == 0)
    return;
  cPrint("%d ", *arr);
  printArr(arr + 1, size - 1);
}

int input(int *num) {
  char temp[20];
  cPrint("Enter number: ");
  fflush(stdout);
  int number = read(0, temp, 19);
  if (number > 0) {
    temp[number] = '\0';
    *num = atoi(temp);
  }
  return *num;
}

void pattern(int size, int *const source, int *const destination) {
  buffer *bfs = mmap(NULL, sizeof(buffer) * size, PROT_WRITE | PROT_READ,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  for (int i = 0; i < size; i++)
    destination[i] = 0;
  if (size > 0)
    destination[0] = source[0];
  if (size > 1)
    destination[size - 1] = source[1];

  int front = 0, back = 0;
  if (size > 2) {
    bfs[back].left = 0;
    bfs[back].right = size - 1;
    back++;
  }

  int index = 2;
  while (front < back && index < size) {
    buffer current = bfs[front++];
    int mid = (current.left + current.right) / 2;

    if (mid != current.left && mid != current.right) {
      destination[mid] = source[index++];
    }

    if (mid - current.left > 1) {
      bfs[back].left = current.left;
      bfs[back].right = mid;
      back++;
    }

    if (current.right - mid > 1) {
      bfs[back].left = mid;
      bfs[back].right = current.right;
      back++;
    }
  }
  munmap(bfs, sizeof(buffer) * size);
}
