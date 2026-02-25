#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

void displayList(Node *head);
void freeList(Node **head);
void insertAtBeginning(Node **head, int value);
void insertAtEnd(Node **head, int value);
void insertAtPostion(Node **head, int value, int position);
void deleteAtBeginning(Node **head);
void deleteAtPosition(Node **head, int position);
void deleteAtEnd(Node **head);

int main() {
  Node *head = NULL;
  insertAtBeginning(&head, 21);
  insertAtEnd(&head, 23);
  insertAtPostion(&head, 22, 2);
  deleteAtBeginning(&head);
  deleteAtEnd(&head);
  deleteAtPosition(&head, 1);
  displayList(head);
  freeList(&head);
  printf("\n");
  return 0;
}

void insertAtBeginning(Node **head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed !");
    return;
  }
  new_node->value = value;
  new_node->next = *head;
  *head = new_node;
}

void insertAtEnd(Node **head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed!");
    return;
  }
  new_node->value = value;
  new_node->next = NULL;

  if (*head == NULL) {
    *head = new_node;
    return;
  }

  Node *temp = *head;

  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = new_node;
}

void insertAtPostion(Node **head, int value, int position) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("memory allocation failed!");
    return;
  }

  new_node->value = value;
  new_node->next = NULL;

  if (position == 1) {
    new_node->next = *head;
    *head = new_node;
    return;
  }

  int i = 1;
  Node *temp = *head;
  while (temp != NULL && i < position - 1) {
    temp = temp->next;
    i++;
  }
  if (temp == NULL) {
    printf("Out of bounce !!");
    free(new_node);
    return;
  }
  new_node->next = temp->next;
  temp->next = new_node;
}

void deleteAtBeginning(Node **head) {
  if (*head == NULL) {
    printf("List is empty!");
    return;
  }
  Node *temp = *head;
  Node *first_value = *head;
  *head = temp->next;
  free(first_value);
}

void deleteAtEnd(Node **head) {
  if (*head == NULL) {
    printf("List is empty!");
    return;
  }
  Node *temp = *head;
  while (temp->next->next != NULL) {
    temp = temp->next;
  }
  if (temp == NULL) {
    printf("Out of bounce!");
    free(temp);
    return;
  }
  Node *Last_value = temp->next;
  temp->next = NULL;
  free(Last_value);
}

void deleteAtPosition(Node **head, int position) {
  if (*head == NULL || position < 1) {
    printf("List is empty!");
    return;
  }
  if (position == 1) {
    Node *temp1 = *head;
    *head = temp1->next;
    free(temp1);
    return;
  }
  Node *temp = *head, *previous = NULL;
  int i = 1;
  while (temp != NULL && i < position) {
    previous = temp;
    temp = temp->next;
    i++;
  }
  if (temp == NULL) {
    printf("Out of bounce!");
    return;
  }
  previous->next = temp->next;
  free(temp);
}

void displayList(Node *head) {
  while (head != NULL) {
    printf("%d -> ", head->value);
    head = head->next;
  }

  if (head == NULL) {
    printf("NULL");
    return;
  }
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
