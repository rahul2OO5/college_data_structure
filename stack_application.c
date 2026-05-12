#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef int32_t i32;

typedef struct {
  i32 top;
  char arr[MAX];
} Stack;

static void init(Stack *stk);
static void push(Stack *stk, char value);
static i32 isFull(Stack *stk);
static char pop(Stack *stk);

int main() {
  Stack myStack;
  init(&myStack);

  char *string = "abcd111xy";
  i32 size = strlen(string);

  char temp[size + 1];
  memset(temp, 0, size + 1);

  i32 temp_index = 0;

  for (i32 i = 0; i < size; i++) {
    if (isalpha(string[i])) {
      push(&myStack, string[i]);
    }
    if (isdigit(string[i])) {
      while (myStack.top != -1) {
        temp[temp_index] = pop(&myStack);
        temp_index++;
      }
      temp[temp_index] = string[i];
      temp_index++;
    }
  }

  while (myStack.top != -1) {
    temp[temp_index] = pop(&myStack);
    temp_index++;
  }

  for (i32 j = 0; j < size + 1; j++) {
    if (temp[j] != '\0') {
      printf("%c", temp[j]);
    }
  }

  printf("\n");
  return 0;
}

void init(Stack *stk) { stk->top = -1; }
i32 isFull(Stack *stk) {
  if (stk->top >= MAX - 1) {
    return 1;
  }
  return 0;
}

void push(Stack *stk, char value) {
  if (isFull(stk)) {
    return;
  }
  stk->top++;
  stk->arr[stk->top] = value;
}

char pop(Stack *stk) {
  if (stk->top == -1) {
    return '\0';
  }
  char popValue = stk->arr[stk->top];
  stk->top--;
  return popValue;
}
