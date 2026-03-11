#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 20
#define BASE 10

typedef struct Node {
  int value;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *head;
  Node *tail;
} LinkedList;

typedef struct {
  int value;
  int position;
  int choice;
} Information;

enum MenueOptions {
  insert_beginning = 1,
  insert_end = 2,
  insert_position = 3,
  delete_beginning = 4,
  delete_end = 5,
  delete_position = 6,
  display = 7,
  quit = 0
};

static int sScan();
static void displayList(LinkedList *list);
static void freeList(LinkedList *list);
static void insertAtBegging(LinkedList *list, Information info);
static void insertAtEnd(LinkedList *list, Information info);
static void insertAtPosition(LinkedList *list, Information info);
static void deleteAtBeginning(LinkedList *list);
static void deleteAtEnd(LinkedList *list);
static void deleteAtPosition(LinkedList *list, Information info);

int main() {
  LinkedList myList;
  myList.head = NULL;
  myList.tail = NULL;

  Information myInfo;
  myInfo.value = 0;
  myInfo.position = 0;
  myInfo.choice = 0;

  printf("\n");
  do {
    printf("1.Insert at beginning\n2.Insert at End\n3.Insert At "
           "position\n4.Delete at beginning\n5.Delete at End\n6.Delete at "
           "Position\n7.Display\n0.Exit\n");

    printf("Enter choice: ");
    myInfo.choice = sScan();
    printf("\n");

    switch (myInfo.choice) {
    case insert_beginning: {
      printf("Enter the value: ");
      myInfo.value = sScan();
      printf("\n");
      insertAtBegging(&myList, myInfo);
      break;
    }

    case insert_end: {
      printf("Enter the value: ");
      myInfo.value = sScan();
      printf("\n");
      insertAtEnd(&myList, myInfo);
      break;
    }

    case insert_position: {
      printf("Enter the value: ");
      myInfo.value = sScan();
      printf("\n");

      printf("Enter the position: ");
      myInfo.position = sScan();
      if (myInfo.position <= 0) {
        printf("Unexpected value!");
        freeList(&myList);
        return 1;
      }

      printf("\n");
      insertAtPosition(&myList, myInfo);
      break;
    }

    case delete_beginning: {
      deleteAtBeginning(&myList);
      break;
    }

    case delete_end: {
      deleteAtEnd(&myList);
      break;
    }

    case delete_position: {
      printf("Enter the position: ");
      myInfo.position = sScan();
      if (myInfo.position <= 0) {
        printf("Unexpected value!");
        freeList(&myList);
        return 1;
      }
      printf("\n");
      deleteAtPosition(&myList, myInfo);
      break;
    }

    case display: {
      printf("\n");
      displayList(&myList);
      printf("\n");
      break;
    }

    case quit: {
      continue;
    }

    default: {
      printf("Does not match!\n");
      break;
    }
    }
  } while (myInfo.choice != 0);

  freeList(&myList);
  printf("\n");
  return 0;
}

int sScan() {
  char buffer[BUFFER_SIZE];
  if ((fgets(buffer, sizeof(buffer), stdin)) == NULL) {
    return 0;
  }
  return (int)strtol(buffer, NULL, BASE);
}

void insertAtBegging(LinkedList *list, Information info) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed!");
    free(new_node);
    return;
  }
  new_node->next = list->head;
  new_node->value = info.value;
  new_node->prev = NULL;
  if (list->head != NULL) {
    list->head->prev = new_node;
  } else {
    list->tail = new_node;
  }
  list->head = new_node;
}

void insertAtEnd(LinkedList *list, Information info) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed!");
    free(new_node);
    return;
  }
  new_node->value = info.value;
  new_node->next = NULL;
  if (list->head == NULL) {
    new_node->prev = NULL;
    list->head = new_node;
    list->tail = new_node;
    return;
  }
  new_node->prev = list->tail;
  list->tail->next = new_node;
  list->tail = new_node;
}

void insertAtPosition(LinkedList *list, Information info) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Memory allocation failed!");
    free(new_node);
    return;
  }

  new_node->next = NULL;
  new_node->value = info.value;
  new_node->prev = NULL;

  if (info.position == 1) {
    new_node->next = list->head;
    if (list->head != NULL) {
      list->head->prev = new_node;
    } else {
      list->tail = new_node;
    }
    list->head = new_node;
    return;
  }

  int counter = 1;
  Node *temp = list->head;
  while (counter < info.position - 1 && temp != NULL) {
    temp = temp->next;
    counter++;
  }
  if (temp != NULL) {
    new_node->next = temp->next;
    new_node->prev = temp;

    if (temp->next != NULL) {
      temp->next->prev = new_node;
    } else {
      list->tail = new_node;
    }
    temp->next = new_node;
  } else {
    printf("Position is out of bound ! \n");
    free(new_node);
  }
}

void deleteAtBeginning(LinkedList *list) {
  if (list == NULL || list->head == NULL) {
    printf("List is empty!");
    return;
  }
  Node *temp = list->head;
  Node *free_element = list->head;
  temp = temp->next;
  if (temp != NULL) {
    temp->prev = NULL;
  } else {
    list->tail = NULL;
  }
  list->head = temp;
  free(free_element);
}

void deleteAtEnd(LinkedList *list) {
  if (list == NULL || list->head == NULL) {
    printf("List is empty!");
    return;
  }
  Node *prev_temp = list->tail;
  Node *free_element = list->tail;
  prev_temp = prev_temp->prev;
  if (prev_temp != NULL) {
    prev_temp->next = NULL;
  } else {
    list->head = NULL;
  }
  list->tail = prev_temp;
  free(free_element);
}

void deleteAtPosition(LinkedList *list, Information info) {
  if (list == NULL || list->head == NULL) {
    printf("List is empty!");
    return;
  }
  Node *temp = list->head;

  if (info.position == 1) {
    temp = temp->next;
    if (temp != NULL) {
      temp->prev = NULL;
    } else {
      list->tail = NULL;
    }
    Node *free_element = list->head;
    list->head = temp;
    free(free_element);
    return;
  }

  int counter = 1;
  Node *previous = NULL;
  while (info.position > counter && temp != NULL) {
    previous = temp;
    temp = temp->next;
    counter++;
  }
  if (temp == NULL) {
    return;
  }
  previous->next = temp->next;
  if (temp->next != NULL) {
    temp->next->prev = previous;
  } else {
    list->tail = previous;
  }
  free(temp);
}

void displayList(LinkedList *list) {
  Node *current = list->head;
  while (current != NULL) {
    printf("%d <-> ", current->value);
    current = current->next;
  }
  if (current == NULL) {
    printf("NULL");
    return;
  }
}

void freeList(LinkedList *list) {
  if (list == NULL || list->head == NULL) {
    return;
  }
  Node *current = list->head;
  Node *next_node;
  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }
  list->head = NULL;
  list->tail = NULL;
}
