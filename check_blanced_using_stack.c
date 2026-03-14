#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
// #define BUFFER 40
#define MAX 100

typedef struct {
  int top;
  int arr[MAX];
} Stack;

void init(Stack *stk) { stk->top = -1; }

int isEmpty(Stack *stk) { return stk->top == -1; }

int isFull(Stack *stk) { return stk->top == MAX - 1; }

void push(Stack *stk, char value) {
  if (!isFull(stk)) {
    stk->arr[++stk->top] = value;
  }
}

char pop(Stack *stk) {
  if (!(isEmpty(stk))) {
    return stk->arr[stk->top--];
  }
  return '\0';
}

int isMatching(char opener, char closer) {
  if (opener == '(' && closer == ')') {
    return 1;
  }
  if (opener == '{' && closer == '}') {
    return 1;
  }
  if (opener == '[' && closer == ']') {
    return 1;
  }
  return 0;
}

int areBalanced(Stack *stk, char *expression) {

  for (int i = 0; expression[i] != '\0'; i++) {
    if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
      push(stk, expression[i]);
    }

    else if (expression[i] == ')' || expression[i] == '}' ||
             expression[i] == ']') {
      if (isEmpty(stk)) {
        return 0;
      }
      char popped_opener = pop(stk);

      if (!(isMatching(popped_opener, expression[i]))) {
        return 0;
      }
    }
  }
  return isEmpty(stk);
}

int main() {
  Stack myStk;
  init(&myStk);

  char expression1[] = "{[()]}";
  char expression2[] = "{[(])}";

  printf("Expression: %s is %s\n", expression1,
         areBalanced(&myStk, expression1) ? "Balanced" : "Not Balanced");

  printf("Expression: %s is %s\n", expression2,
         areBalanced(&myStk, expression2) ? "Balanced" : "Not Balanced");

  return 0;
}
