#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *prev;
  struct Node *next;
} Node;

void displayList(Node *head);
void freeList(Node **head);
void insertAtBeginning(Node **head, int value);
void insertAtEnd(Node **head, int value);
void insertAtPosition(Node **head, int value, int position);
void deleteAtBeginning(Node **head);
void deleteAtPosition(Node **head, int position);

int main() {
  Node *head = NULL;

  insertAtBeginning(&head, 21);
  insertAtEnd(&head, 23);
  insertAtPosition(&head, 22, 2);

  printf("After Insertions:\n");
  displayList(head);

  deleteAtBeginning(&head);
  deleteAtPosition(&head, 2);

  printf("After Deletions:\n");
  displayList(head);

  freeList(&head);
  return 0;
}

void insertAtBeginning(Node **head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed!\n");
    return;
  }
  new_node->value = value;
  new_node->prev = NULL;
  new_node->next = *head;

  if (*head != NULL) {
    (*head)->prev = new_node;
  }
  *head = new_node;
}

void insertAtEnd(Node **head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed!\n");
    return;
  }
  new_node->value = value;
  new_node->next = NULL;

  if (*head == NULL) {
    new_node->prev = NULL;
    *head = new_node;
    return;
  }

  Node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = new_node;
  new_node->prev = temp;
}

void insertAtPosition(Node **head, int value, int position) {
  if (position < 1) {
    printf("Invalid position!\n");
    return;
  }

  if (position == 1) {
    insertAtBeginning(head, value);
    return;
  }

  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed!\n");
    return;
  }
  new_node->value = value;

  int i = 1;
  Node *temp = *head;

  while (temp != NULL && i < position - 1) {
    temp = temp->next;
    i++;
  }

  if (temp == NULL) {
    printf("Out of bounds!!\n");
    free(new_node);
    return;
  }

  new_node->next = temp->next;
  new_node->prev = temp;

  if (temp->next != NULL) {
    temp->next->prev = new_node;
  }
  temp->next = new_node;
}

void deleteAtBeginning(Node **head) {
  if (*head == NULL) {
    printf("List is empty!\n");
    return;
  }

  Node *temp = *head;
  *head = temp->next;

  if (*head != NULL) {
    (*head)->prev = NULL;
  }
  free(temp);
}

void deleteAtPosition(Node **head, int position) {
  if (*head == NULL || position < 1) {
    printf("List is empty or invalid position!\n");
    return;
  }

  if (position == 1) {
    deleteAtBeginning(head);
    return;
  }

  Node *temp = *head;
  int i = 1;

  while (temp != NULL && i < position) {
    temp = temp->next;
    i++;
  }

  if (temp == NULL) {
    printf("Out of bounds!\n");
    return;
  }

  temp->prev->next = temp->next;

  if (temp->next != NULL) {
    temp->next->prev = temp->prev;
  }

  free(temp);
}

void displayList(Node *head) {
  while (head != NULL) {
    printf("%d <-> ", head->value);
    head = head->next;
  }
  printf("NULL\n");
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
