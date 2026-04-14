#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 40
#define BASE 10

typedef int32_t i32;
typedef ptrdiff_t diff;

typedef struct Node {
  i32 value;
  struct Node *next;
} Node;

typedef struct {
  i32 value;
  i32 position;
  i32 choice;
} Information;

enum {
  beginning = 1,
  end = 2,
  position = 3,
  delete_postion = 6,
  delete_beginning = 4,
  delete_end = 5,
  display = 7,
  quit = 0
};

static void insertAtBeginning(Node **head, Information info);
static void insertAtEnd(Node **head, Information info);
static void insertAtPosition(Node **head, Information info);
static void displayList(Node *head);
static void freeList(Node **head);
static void deleteAtBeginning(Node **head);
static void deleteAtEnd(Node **head);
static void deleteAtPosition(Node **head, Information info);
static i32 sScan();

int main() {
  Node *head = NULL;
  Information info;
  info.choice = 0;
  do {
    printf("\nEnter the option:\n\t1.Insert At beginning\n\t2.Insert At "
           "End\n\t3.Insert At position\n\t4.Delete At beginning\n\t5.Delete "
           "At End\n\t6.Delete At position\n\t7.Display\n\t0.quit\n\t");
    printf("\nYour choice: ");
    info.choice = sScan();
    printf("\n");
    switch (info.choice) {
    case beginning: {
      printf("\n\t\tEnter the value: ");
      info.value = sScan();
      printf("\n");
      insertAtBeginning(&head, info);
      break;
    }
    case end: {
      printf("\n\t\tEnter the value: ");
      info.value = sScan();
      printf("\n");
      insertAtEnd(&head, info);
      break;
    }
    case position: {
      printf("\n\t\tEnter the value: ");
      info.value = sScan();
      printf("\n\t\tEnter the position: ");
      info.position = sScan();
      insertAtPosition(&head, info);
      break;
    }
    case delete_beginning: {
      deleteAtBeginning(&head);
      break;
    }
    case delete_end: {
      deleteAtEnd(&head);
      break;
    }
    case delete_postion: {
      printf("\n\t\tEnter the position: ");
      info.position = sScan();
      deleteAtPosition(&head, info);
      break;
    }
    case display: {
      printf("\n\n");
      displayList(head);
      break;
    }
    case quit: {
      break;
    }
    default: {
      printf("Unexpected error occur!\n");
    }
    }
  } while (info.choice != 0);
  freeList(&head);
  return 0;
}

i32 sScan() {
  char buffer[BUFFER];
  if (fgets(buffer, BUFFER, stdin) == NULL) {
    return 0;
  }
  return (i32)strtol(buffer, NULL, BASE);
}

void insertAtBeginning(Node **head, Information info) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("memory allocation failed!\n");
    return;
  }

  new_node->value = info.value;

  if (*head == NULL) {
    new_node->next = new_node;
    *head = new_node;
  } else {
    Node *temp = *head;

    while (temp->next != *head) {
      temp = temp->next;
    }
    new_node->next = *head;
    temp->next = new_node;
    *head = new_node;
  }
}

void insertAtEnd(Node **head, Information info) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("memory allocation failed!\n");
    return;
  }

  new_node->value = info.value;

  if (*head == NULL) {
    new_node->next = new_node;
    *head = new_node;
  } else {
    Node *temp = *head;

    while (temp->next != *head) {
      temp = temp->next;
    }
    new_node->next = *head;
    temp->next = new_node;
  }
}

void insertAtPosition(Node **head, Information info) {
  if (info.position == 1) {
    insertAtBeginning(head, info);
    return;
  }

  if (info.position < 1) {
    printf("enter the valid range number");
    return;
  }

  if (*head == NULL) {
    printf("out of bound\n");
    return;
  }

  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("memory allocation failed!");
    return;
  }

  new_node->value = info.value;
  new_node->next = NULL;
  diff counter = 1;
  Node *temp = *head;

  while (temp->next != *head && counter < info.position - 1) {
    temp = temp->next;
    counter++;
  }
  if (counter < info.position - 1) {
    printf("out of bound!\n");
    free(new_node);
    return;
  }
  new_node->next = temp->next;
  temp->next = new_node;
}

void deleteAtBeginning(Node **head) {
  if (*head == NULL) {
    printf("\nList is empty\n");
    return;
  }
  Node *temp = *head;
  if (temp->next == *head) {
    free(temp);
    *head = NULL;
  } else {
    Node *temp_2 = *head;
    while (temp_2->next != *head) {
      temp_2 = temp_2->next;
    }
    *head = temp->next;
    temp_2->next = *head;
    free(temp);
  }
}

void deleteAtEnd(Node **head) {
  if (*head == NULL) {
    printf("\nList is empyt\n");
    return;
  }
  Node *temp = *head;
  if (temp->next == *head) {
    free(temp);
    *head = NULL;
  } else {
    Node *previous = NULL;
    while (temp->next != *head) {
      previous = temp;
      temp = temp->next;
    }
    previous->next = *head;
    free(temp);
  }
}

void deleteAtPosition(Node **head, Information info) {
  if (*head == NULL) {
    printf("\nList is empyt\n");
    return;
  }

  if (info.position < 1) {
    printf("enter the valid range number");
    return;
  }

  if (info.position == 1) {
    deleteAtBeginning(head);
    return;
  }
  Node *temp = *head;
  Node *previous = NULL;
  diff counter = 1;
  while (temp->next != *head && counter < info.position) {
    previous = temp;
    temp = temp->next;
    counter++;
  }
  if (counter < info.position) {
    printf("out of bound");
    return;
  }
  previous->next = temp->next;
  free(temp);
}

void displayList(Node *head) {
  if (head == NULL) {
    printf("List is empty!\n");
    return;
  }
  Node *temp = head;
  do {
    printf("%d -> ", temp->value);
    temp = temp->next;
  } while (temp != head);
  printf("back to head: %d\n", head->value);
}

void freeList(Node **head) {
  if (*head == NULL) {
    return;
  }

  Node *current = (*head)->next;
  Node *next_node;

  while (current != *head) {
    next_node = current->next;
    free(current);
    current = next_node;
  }
  free(*head);
  *head = NULL;
}
