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

enum MenueOption { Push = 1, Pop = 2, Display = 3, Merge = 4 };

static int sScan();
static void initStack(Stack *stk);
static int isFull(Stack *stk);
static int isEmpty(Stack *stk);
static void displayStack(Stack *stk);

static void push(Stack *stk, int value);
static int pop(Stack *stk);
static int top(Stack *stk);
static int size(Stack *stk);
static int compareTo(int x, int y);

static Stack mergeSortedStacks(Stack *StackA, Stack *StackB);

int main() {
  Stack mystack;
  Information myInfo;
  initStack(&mystack);
  myInfo.value = 0, myInfo.choice = 0;

  do {
    printf("\n1.Push\n2.Pop\n3.Display\n4.Demo Merge Sorted Stacks\n0.Exit\n");
    printf("\n");
    printf("Enter the choice: ");
    myInfo.choice = sScan();
    printf("\n");

    if (myInfo.choice < 0 || myInfo.choice > 4) {
      printf("Please enter the between the provided range!\n");
      continue;
    }

    switch (myInfo.choice) {
    case Push: {
      printf("Enter the value: ");
      myInfo.value = sScan();
      if (!isFull(&mystack)) {
        push(&mystack, myInfo.value);
        printf("\n%d is pushed to stack\n", myInfo.value);
      } else {
        printf("Stack is full!\n");
      }
      break;
    }

    case Pop: {
      if (!isEmpty(&mystack)) {
        int poppedVal = pop(&mystack);
        printf("%d is pop from stack\n", poppedVal);
      } else {
        printf("Stack is empty!\n");
      }
      break;
    }

    case Display: {
      printf("Elements in stack (top to bottom):\n");
      displayStack(&mystack);
      printf("\n");
      break;
    }

    case Merge: {
      Stack stackA, stackB, mergedStack;
      initStack(&stackA);
      initStack(&stackB);

      push(&stackA, 9);
      push(&stackA, 7);
      push(&stackA, 5);
      push(&stackA, 3);

      push(&stackB, 8);
      push(&stackB, 6);
      push(&stackB, 4);
      push(&stackB, 2);

      printf("Stack A:\n");
      displayStack(&stackA);

      printf("Stack B:\n");
      displayStack(&stackB);

      printf("\nMerging Stacks\n");
      mergedStack = mergeSortedStacks(&stackA, &stackB);

      printf("Merged Result Stack (Min on top):\n");
      displayStack(&mergedStack);
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

int isFull(Stack *stk) { return (stk->top == MAX - 1); }

int isEmpty(Stack *stk) { return (stk->top == -1); }

void displayStack(Stack *stk) {
  if (isEmpty(stk)) {
    printf("Stack is empty!\n");
    return;
  }
  for (int i = stk->top; i >= 0; i--) {
    printf("%d\n", stk->arr[i]);
  }
}

void push(Stack *stk, int value) {
  stk->top++;
  stk->arr[stk->top] = value;
}

int pop(Stack *stk) {
  int value = stk->arr[stk->top];
  stk->top--;
  return value;
}

int top(Stack *stk) { return stk->arr[stk->top]; }

int size(Stack *stk) { return stk->top + 1; }

int compareTo(int x, int y) { return x - y; }

Stack mergeSortedStacks(Stack *StackA, Stack *StackB) {
  Stack tempStack, finalStack;
  initStack(&tempStack);
  initStack(&finalStack);

  while (size(StackA) > 0 && size(StackB) > 0) {
    if (compareTo(top(StackA), top(StackB)) <= 0) {
      push(&tempStack, pop(StackA));
    } else {
      push(&tempStack, pop(StackB));
    }
  }

  while (size(StackA) > 0) {
    push(&tempStack, pop(StackA));
  }

  while (size(StackB) > 0) {
    push(&tempStack, pop(StackB));
  }

  while (size(&tempStack) > 0) {
    push(&finalStack, pop(&tempStack));
  }

  return finalStack;
}

int sScan() {
  char buffer[BUFFER];
  if ((fgets(buffer, sizeof(buffer), stdin)) == NULL) {
    return 0;
  }
  return (int)strtol(buffer, NULL, BASE);
}
