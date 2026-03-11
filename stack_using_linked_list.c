#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER 20
#define BASE 10

typedef struct Stack {
  int value;
  struct Stack *top;
} Stack;

typedef struct {
  int value;
  int choice;
} Information;

enum Options { Push = 1, Pop = 2, Display = 3 };

static int Sscan();
static void push(Stack **head, Information info);
static void pop(Stack **head);
static void DisplayStack(Stack *head);
static void freeStack(Stack **head);

int main() {
  Stack *head = NULL;
  Information myInfo;

  do {
    printf("\n");
    printf("\n1.Push\n2.Pop\n3.Display\n0.Exit\n");
    printf("Enter choice:");
    myInfo.choice = Sscan();
    printf("\n");

    switch (myInfo.choice) {
    case Push: {
      printf("Enter the number: ");
      myInfo.value = Sscan();
      printf("\n");
      push(&head, myInfo);
      break;
    }
    case Pop: {
      pop(&head);
      break;
    }
    case Display: {
      printf("\n");
      DisplayStack(head);
      break;
    }
    default:
      break;
    }
  } while (myInfo.choice != 0);
  freeStack(&head);
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

void push(Stack **head, Information info) {
  Stack *new_top = (Stack *)malloc(sizeof(Stack));
  if (new_top == NULL) {
    printf("Memory allocation failed!");
    return;
  }
  Stack *temp = *head;
  new_top->value = info.value;
  new_top->top = NULL;
  if (*head == NULL) {
    *head = new_top;
    printf("%d is pushed to Stack!", info.value);
    return;
  }
  while (temp->top != NULL) {
    temp = temp->top;
  }
  temp->top = new_top;
  printf("%d is pushed to Stack!", info.value);
}

void pop(Stack **head) {
  if (*head == NULL) {
    printf("Stack is empty\n");
    return;
  }
  if ((*head)->top == NULL) {
    printf("%d is pop from Stack!\n", (*head)->value);
    free(*head);
    *head = NULL;
    return;
  }
  Stack *temp = *head;
  while (temp->top->top != NULL) {
    temp = temp->top;
  }
  if (temp == NULL) {
    printf("Out of bounce!\n");
    free(temp);
    return;
  }
  Stack *free_emement = temp->top;
  temp->top = NULL;
  printf("%d is pop from Stack!\n", temp->value);
  free(free_emement);
}

void DisplayStack(Stack *head) {
  if (head == NULL) {
    printf("Stack is empty\n");
    return;
  }
  while (head != NULL) {
    printf("%d <- ", head->value);
    head = head->top;
  }
  if (head == NULL) {
    printf("Top");
    return;
  }
}

void freeStack(Stack **head) {
  if (*head == NULL || head == NULL) {
    return;
  }
  Stack *current = *head;
  Stack *next;
  while (current != NULL) {
    next = current->top;
    free(current);
    current = next;
  }
  *head = NULL;
}
