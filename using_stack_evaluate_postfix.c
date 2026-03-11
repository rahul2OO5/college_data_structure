#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 40
#define MAX 100

typedef struct {
  int top;
  int arr[MAX];
} Stack;

static void initilize(Stack *stk);
static int isFull(Stack *stk);
static void push(Stack *stk, int value);
static int pop(Stack *stk);
static char *Sscan();
static int postfix(Stack *stk, char *expression);

int main() {
  Stack myStack;
  initilize(&myStack);
  printf("Enter the expression: ");
  char *expression = Sscan();
  printf("\n");

  int value = postfix(&myStack, expression);
  printf("%d is the value", value);

  free(expression);
  printf("\n");
  return 0;
}

void initilize(Stack *stk) { stk->top = -1; }

int isFull(Stack *stk) {
  if (stk->top == MAX - 1) {
    return 1;
  }
  return 0;
}

void push(Stack *stk, int value) {
  if (isFull(stk)) {
    printf("Stack is full!\n");
    return;
  }
  stk->top++;
  stk->arr[stk->top] = value;
}

int pop(Stack *stk) {
  if (stk->top == -1) {
    printf("Stack is already empty!\n");
    return -1;
  }
  int popped_value = stk->arr[stk->top];
  stk->top--;
  return popped_value;
}

char *Sscan() {
  char *buffer = (char *)malloc(BUFFER * sizeof(char));
  if (buffer == NULL) {
    printf("memory allocation failed!\n");
    return NULL;
  }
  if ((fgets(buffer, BUFFER, stdin)) == NULL) {
    free(buffer);
    return NULL;
  }
  buffer[strcspn(buffer, "\n")] = '\0';
  return buffer;
}

int postfix(Stack *stk, char *expression) {
  for (int count = 0; expression[count] != '\0'; count++) {
    if (isdigit(expression[count])) {
      push(stk, expression[count] - '0');
    } else {
      int value_1 = pop(stk);
      int value_2 = pop(stk);

      switch (expression[count]) {
      case '+': {
        push(stk, value_2 + value_1);
        break;
      }
      case '-': {
        push(stk, value_2 - value_1);
        break;
      }
      case '*': {
        push(stk, value_2 * value_1);
        break;
      }
      case '/': {
        push(stk, value_2 / value_1);
        break;
      }
      }
    }
  }
  return pop(stk);
}
