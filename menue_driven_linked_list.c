#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

void insertAtBeginning(Node **head, int value);
void insertAtEnd(Node **head, int value);
void displayList(Node *node);
void deleteAtPosition(Node **head, int value);
void deleteAtBeginning(Node **head);
void deleteAtEnd(Node **head);
void insertAtPosition(Node **head, int value, int position);
void freeList(Node **head);

int main() {
  Node *head = NULL;
  int value, choice, position = 0;
  do {
    printf("Enter choice: ");
    printf("\n");
    printf("1.Insert at the beginning.");
    printf("\n");
    printf("2.Insert at the end.");
    printf("\n");
    printf("3.Insert at the position.");
    printf("\n");
    printf("4.Delete at the beginning.");
    printf("\n");
    printf("5.Delete at the end.");
    printf("\n");
    printf("6.Delete at the position.");
    printf("\n");
    printf("7.Display the list.");
    printf("\n");
    printf("0.Exit");
    printf("\n");
    printf("\n");
    printf("Choice: ");
    scanf("%d", &choice);
    printf("\n");
    switch (choice) {
    case 1: {
      printf("Enter the value: ");
      scanf("%d", &value);
      printf("\n");

      insertAtBeginning(&head, value);
      position++;
      break;
    }
    case 2: {
      printf("Enter the value: ");
      scanf("%d", &value);
      printf("\n");

      insertAtEnd(&head, value);
      position++;
      break;
    }
    case 3: {
      printf("Enter the value: ");
      scanf("%d", &value);
      printf("\n");

      printf("Enter the position: ");
      scanf("%d", &position);
      printf("\n");

      insertAtPosition(&head, value, position);
      position++;
      break;
    }
    case 4: {
      deleteAtBeginning(&head);
      position--;
      break;
    }
    case 5: {
      deleteAtEnd(&head);
      position--;
      break;
    }
    case 6: {
      printf("Enter the value: ");
      scanf("%d", &value);
      printf("\n");
      deleteAtPosition(&head, value);
      position--;
      break;
    }
    case 7: {
      displayList(head);
      printf("\n");
      break;
    }
    default: {
      printf("Invalid number!!");
    }
    }
  } while (choice != 0);
  freeList(&head);
  return 0;
}

void insertAtBeginning(Node **head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL)
    return;
  new_node->value = value;
  new_node->next = *head;
  *head = new_node;
}

void insertAtEnd(Node **head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL)
    return;
  Node *last = *head;
  new_node->value = value;
  new_node->next = NULL;
  if (*head == NULL) {
    *head = new_node;
    return;
  }
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = new_node;
}

void displayList(Node *node) {
  while (node != NULL) {
    printf("%d ->  ", node->value);
    node = node->next;
  }
  if (node == NULL) {
    printf("NULL");
    printf("\n");
    return;
  }
}

void deleteAtPosition(Node **head, int value) {
  Node *temp = *head, *previous = NULL;
  while (temp != NULL && temp->value != value) {
    previous = temp;
    temp = temp->next;
  }

  if (temp == NULL) {
    return;
  }
  previous->next = temp->next;
}
void deleteAtBeginning(Node **head) {
  if (*head == NULL) {
    return;
  }
  Node *temp = *head;
  *head = temp->next;
}

void deleteAtEnd(Node **head) {
  if (*head == NULL) {
    return;
  }
  Node *temp = *head;
  while (temp->next->next != NULL) {
    temp = temp->next;
  }
  temp->next = NULL;
}
void insertAtPosition(Node **head, int value, int position) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    return;
  }
  new_node->value = value;
  new_node->next = NULL;

  if (position == 1) {
    new_node->next = *head;
    *head = new_node;
    return;
  }

  Node *temp = *head;
  for (int i = 1; i < position - 1; i++) {
    if (temp == NULL) {
      return;
    }
    temp = temp->next;
  }
  new_node->next = temp->next;
  temp->next = new_node;
}

void freeList(Node **head) {
  Node *current = *head;
  Node *next_node;
  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }
  *head = NULL;
}
