#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define BUFFER 40
#define BASE 10

typedef int32_t i32;

typedef struct {
  i32 top;
  i32 arr[MAX];
} Stack;

static void init(Stack *stk) { stk->top = -1; }

static i32 isFull(Stack *stk) {
  if (stk->top >= MAX - 1) {
    return 1;
  }
  return 0;
}

static void push(Stack *stk, i32 value) {
  if (isFull(stk)) {
    printf("Stack is full");
    return;
  }
  stk->arr[++stk->top] = value;
}

static i32 pop(Stack *stk) {
  if (stk->top == -1) {
    printf("Stack is empty");
    return 0;
  }
  return stk->arr[stk->top--];
}

static i32 peek(Stack *stk) {
  if (stk->top == -1) {
    return 1;
  }
  return stk->arr[stk->top];
}

static i32 isEmpty(Stack *stk) { return (stk->top == -1); }

static void merg(Stack *stk1, Stack *stk2, Stack *result) {
  while (!isEmpty(stk1) && !isEmpty(stk2)) {
    i32 pop_value1 = peek(stk1);
    i32 pop_value2 = peek(stk2);

    if (!isFull(result)) {
      if (pop_value2 > pop_value1) {
        push(result, pop(stk2));
      } else {
        push(result, pop(stk1));
      }
    }
  }

  while (!isEmpty(stk1)) {
    push(result, pop(stk1));
  }
  while (!isEmpty(stk2)) {
    push(result, pop(stk2));
  }
}

int main() {
  Stack stack1;
  Stack stack2;
  Stack result;
  init(&stack1);
  init(&stack2);
  init(&result);

  i32 inline_value1[] = {1, 2, 3, 4, 5};
  for (i32 i = 0; i < 5; i++) {
    push(&stack1, inline_value1[i]);
  }

  i32 inline_value2[] = {6, 7, 8, 9, 10};
  for (i32 i = 0; i < 5; i++) {
    push(&stack2, inline_value2[i]);
  }

  merg(&stack1, &stack2, &result);
  for (i32 i = 0; i <= result.top; i++) {
    printf("%d ", result.arr[i]);
  }

  printf("\n");
  return 0;
}
