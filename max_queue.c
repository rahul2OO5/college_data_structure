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

enum {
  insert_element = 1,
  delete_element = 2,
  print = 3,
  find_max = 4,
  quit = 0
};

static i32 sScan();
static void enqueue(Queue *que, Information info);
static i32 dequeue(Queue *que);
static void display(Queue *que);
static void freeElement(Queue *que);
static i32 size(Queue *que);
static i32 findMax(Queue *que);

int main() {
  Queue myQue;
  Information myinfo;
  myQue.front = NULL;
  myQue.rear = NULL;
  myinfo.choice = 0;

  do {
    printf("\nEnter the "
           "choice:\n\t1.enqueue\n\t2.dequeue\n\t3.display\n\t4.find "
           "max\n\t0.quit\n");
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
      i32 val = dequeue(&myQue);
      if (val != -1) {
        printf("\nDequeued: %d\n", val);
      }
      break;
    }
    case print: {
      printf("\n\n");
      display(&myQue);
      break;
    }
    case find_max: {
      if (myQue.front != NULL) {
        i32 maxVal = findMax(&myQue);
        printf("\nMax element in queue is: %d\n", maxVal);
      } else {
        printf("\nQueue is empty!\n");
      }
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

i32 dequeue(Queue *que) {
  if (que->front == NULL) {
    printf("\nQueue is empty!\n");
    return -1;
  }

  Node *temp = que->front;
  i32 val = temp->value;

  if (que->front == que->rear) {
    que->front = NULL;
    que->rear = NULL;
  } else {
    que->front = que->front->next;
  }

  free(temp);
  return val;
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
  printf("NULL\n");
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

i32 size(Queue *que) {
  i32 count = 0;
  Node *current = que->front;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}

i32 findMax(Queue *que) {
  i32 originalSize = size(que);

  if (originalSize == 0) {
    return -1;
  }

  i32 maxElement = dequeue(que);
  Information info;
  info.value = maxElement;
  enqueue(que, info);

  for (i32 i = 1; i < originalSize; i++) {
    i32 current = dequeue(que);

    if (current > maxElement) {
      maxElement = current;
    }

    info.value = current;
    enqueue(que, info);
  }

  return maxElement;
}
