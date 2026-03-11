#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define BUFFER 20
#define BASE 10

typedef struct Stack {
  int top;
  int arr[MAX];
} Stack;

typedef struct {
  int value;
  int choice;
} Information;

enum MenueOption { Push = 1, Pop = 2, Display = 3 };

static int sScan();
static void initStack(Stack *stk);
static int isFull(Stack *stk);
static void displayStack(Stack *stk);
static void push(Stack *stk, int value);
static void pop(Stack *stk);

int main() {
  Stack mystack;
  Information myInfo;
  initStack(&mystack);
  myInfo.value = 0, myInfo.choice = 0;
  do {
    printf("\n1.Push\n2.Pop\n3.Display\n0.Exit\n");
    printf("\n");
    printf("Enter the choice: ");
    myInfo.choice = sScan();
    printf("\n");

    if (myInfo.choice < 0 || myInfo.choice > 3) {
      printf("Please enter the between the provided range!");
      continue;
    }

    switch (myInfo.choice) {
    case Push: {
      printf("Enter the value: ");
      myInfo.value = sScan();
      printf("\n");
      push(&mystack, myInfo.value);
      printf("\n");
      break;
    }

    case Pop: {
      pop(&mystack);
      printf("\n");
      break;
    }

    case Display: {
      printf("Elements in stack:\n");
      displayStack(&mystack);
      printf("\n");
      break;
    }
    default: {
      break;
    }
    }
  } while (myInfo.choice != 0);
  printf("\n");
  return 0;
}

void initStack(Stack *stk) { stk->top = -1; }

int isFull(Stack *stk) {
  if (stk->top == MAX - 1) {
    return 1;
  }
  return 0;
}

void displayStack(Stack *stk) {
  if (stk->top == -1) {
    printf("Stack is empty!\n");
    return;
  }
  for (int i = stk->top; i >= 0; i--) {
    printf("%d ", stk->arr[i]);
  }
}

void push(Stack *stk, int value) {
  if (isFull(stk)) {
    printf("Stack is full!\n");
    return;
  }
  stk->top++;
  stk->arr[stk->top] = value;
  printf("%d is pushed to stack\n", value);
}

void pop(Stack *stk) {
  if (stk->top == -1) {
    printf("Stack is empty!\n");
    return;
  }
  printf("%d is pop from stack\n", stk->arr[stk->top]);
  stk->top--;
}

int sScan() {
  char buffer[BUFFER];
  if ((fgets(buffer, sizeof(buffer), stdin)) == NULL) {
    return 0;
  }
  return (int)strtol(buffer, NULL, BASE);
}
