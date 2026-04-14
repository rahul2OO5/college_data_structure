#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 40
#define BASE 10

typedef int32_t i32;

typedef struct Node {
  i32 value;
  struct Node *next;
} Node;

typedef struct {
  Node *front;
  Node *rear;
} Queue;

typedef struct {
  i32 value;
  i32 choice;
} Information;

enum { insert_element = 1, delete_element = 2, print = 3, quit = 0 };

static i32 sScan();
static void enqueue(Queue *que, Information info);
static void dequeue(Queue *que);
static void display(Queue *que);
static void freeElement(Queue *que);

int main() {
  Queue myQue;
  Information myinfo;
  myQue.front = NULL;
  myQue.rear = NULL;
  myinfo.choice = 0;

  do {
    printf("\nEnter the "
           "choice:\n\t1.enqueue\n\t2.dequeue\n\t3.display\n\t0.quit\n");
    printf("\nChoice: ");
    myinfo.choice = sScan();
    printf("\n");

    switch (myinfo.choice) {
    case insert_element: {
      printf("\n\t\tEnter the value: ");
      myinfo.value = sScan();
      enqueue(&myQue, myinfo);
      printf("\n");
      break;
    }
    case delete_element: {
      dequeue(&myQue);
      break;
    }
    case print: {
      printf("\n\n");
      display(&myQue);
      break;
    }
    case quit: {
      break;
    }
    default: {
      printf("Unexprected error occur!");
    }
    }

  } while (myinfo.choice != 0);
  freeElement(&myQue);
  return 0;
}

i32 sScan() {
  char buffer[BUFFER];
  if (fgets(buffer, BUFFER, stdin) == NULL) {
    return 0;
  }
  return (i32)strtol(buffer, NULL, BASE);
}

void enqueue(Queue *que, Information info) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("\nmemory allocation failed\n");
    return;
  }
  new_node->value = info.value;
  new_node->next = NULL;
  if (que->rear == NULL) {
    que->rear = new_node;
    que->front = new_node;
  } else {
    que->rear->next = new_node;
    que->rear = new_node;
  }
}

void dequeue(Queue *que) {
  if (que->front == NULL) {
    printf("\nQueue is empty!\n");
    return;
  }

  Node *temp = que->front;

  if (que->front == que->rear) {
    que->front = NULL;
    que->rear = NULL;
    free(temp);
    return;
  }
  que->front = que->front->next;

  free(temp);
}

void display(Queue *que) {
  Node *current = que->front;
  if (current == NULL) {
    printf("\nqueue is empty\n");
    return;
  }
  while (current != NULL) {
    printf("%d -> ", current->value);
    current = current->next;
  }
}

void freeElement(Queue *que) {
  if (que == NULL || que->front == NULL) {
    return;
  }
  Node *current = que->front;
  Node *next_node;
  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }
  que->front = NULL;
  que->rear = NULL;
}
