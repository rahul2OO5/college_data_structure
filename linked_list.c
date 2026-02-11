#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

void insertAtBeginning(Node **head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = *head;
  *head = new_node;
}

void insertAtEnd(Node **head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
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

void deleteNode(Node **head, int key) {
  Node *temp = *head, *prev = NULL;

  if (temp != NULL && temp->value == key) {
    *head = temp->next;
    free(temp);
    return;
  }

  while (temp != NULL && temp->value != key) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL)
    return;

  prev->next = temp->next;
  free(temp);
}

void printList(Node *node) {
  while (node != NULL) {
    printf("%d -> ", node->value);
    node = node->next;
  }
  printf("NULL\n");
}

int main() {
  Node *head = NULL;

  insertAtEnd(&head, 10);
  insertAtBeginning(&head, 20);
  insertAtEnd(&head, 30);

  printf("Linked List: ");
  printList(head);
  deleteNode(&head, 10);

  printf("After deletion: ");
  printList(head);
  return 0;
}
