#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 40
#define MAX 100
#define BASE 10
#define IDX(row, column, size) ((row * size) + column)

typedef int32_t i32;

typedef struct {
  i32 matrix[MAX * MAX];
  i32 vertices;
} Graph;

typedef struct {
  i32 arr[MAX];
  i32 front;
  i32 rear;
} Queue;

static void init(Queue *que) {
  que->rear = 0;
  que->front = 0;
}

static i32 isQueueEmpty(Queue *que) { return (que->front >= que->rear); }
static i32 isQueueFull(Queue *que) { return (que->rear > MAX - 1); }

static void enqueue(Queue *que, i32 value) {
  if (isQueueFull(que)) {
    return;
  }
  que->arr[que->rear++] = value;
}

static i32 dequeue(Queue *que) {
  if (isQueueEmpty(que)) {
    return 0;
  }
  return (que->arr[que->front++]);
}

static void addEdges(Graph *grp, i32 src, i32 dest, i32 weight) {
  grp->matrix[IDX(src, dest, grp->vertices)] = weight;
}

static void display(Graph *grp) {
  for (i32 i = 0; i < grp->vertices; i++) {
    for (i32 j = 0; j < grp->vertices; j++) {
      printf("%d ", grp->matrix[IDX(i, j, grp->vertices)]);
    }
    printf("\n");
  }
}

static void dfsRecursive(Graph *grp, i32 currentVertices, i32 visited[]) {
  visited[currentVertices] = 1;
  printf("%d ", currentVertices);
  for (i32 neighbor = 0; neighbor < grp->vertices; neighbor++) {
    if (grp->matrix[IDX(currentVertices, neighbor, grp->vertices)] > 0 &&
        visited[neighbor] == 0) {
      dfsRecursive(grp, neighbor, visited);
    }
  }
}

static void dfs(Graph *grp, i32 startVertices) {
  i32 visited[MAX] = {0};
  printf("\nDFS Traversal:");
  dfsRecursive(grp, startVertices, visited);
  printf("\n");
}

static void bfs(Graph *grp, i32 startVertices) {
  i32 visited[MAX] = {0};
  Queue tempQue;
  init(&tempQue);

  visited[startVertices] = 1;
  enqueue(&tempQue, startVertices);
  printf("Print BFS: ");

  while (!isQueueEmpty(&tempQue)) {
    i32 currentVertices = dequeue(&tempQue);
    printf("%d ", currentVertices);

    for (i32 neighbor = 0; neighbor < grp->vertices; neighbor++) {
      if (grp->matrix[IDX(currentVertices, neighbor, grp->vertices)] > 0 &&
          visited[neighbor] == 0) {
        visited[neighbor] = 1;
        enqueue(&tempQue, neighbor);
      }
    }
  }
  printf("\n");
}

static i32 getMinDistanceNode(i32 distance[], i32 visited[], i32 vertices) {
  i32 min_val = INT32_MAX;
  i32 min_idx = -1;
  for (i32 count = 0; count < vertices; count++) {
    if (visited[count] == 0 && distance[count] <= min_val) {
      min_val = distance[count];
      min_idx = count;
    }
  }
  return min_idx;
}

static void dijkstra(Graph *grp, i32 startVertices) {
  i32 distance[MAX];
  i32 visited[MAX];
  for (i32 i = 0; i < grp->vertices; i++) {
    distance[i] = INT32_MAX;
    visited[i] = 0;
  }

  distance[startVertices] = 0;
  for (i32 count = 0; count < grp->vertices - 1; count++) {
    i32 closest_vertice = getMinDistanceNode(distance, visited, grp->vertices);
    visited[closest_vertice] = 1;
    for (i32 neighbor = 0; neighbor < grp->vertices; neighbor++) {
      i32 edgeWeight =
          grp->matrix[IDX(closest_vertice, neighbor, grp->vertices)];
      if (!visited[neighbor] && edgeWeight > 0 &&
          distance[closest_vertice] != INT32_MAX &&
          distance[closest_vertice] + edgeWeight < distance[neighbor]) {
        distance[neighbor] = distance[closest_vertice] + edgeWeight;
      }
    }
  }

  printf("\nShortest Distance from vertic %d:\n", startVertices);
  for (i32 i = 0; i < grp->vertices; i++) {
    if (distance[i] == INT32_MAX) {
      printf("Node %d \t Distance: Unreachable \n", i);
    } else {
      printf("Node %d \t Distance: %d\n", i, distance[i]);
    }
  }
}

static i32 sScan() {
  char buffer[BUFFER];
  if (fgets(buffer, BUFFER, stdin) == NULL) {
    return 0;
  }
  return (i32)strtol(buffer, NULL, BASE);
}

int main() {
  Graph myGraph = {.matrix = {0}, .vertices = 0};

  i32 vertics = 0;
  printf("\nEnter the no of vertices: ");
  vertics = sScan();
  myGraph.vertices = vertics;

  i32 choice = 0;
  do {
    printf("\nEnter the "
           "choice\n\t1.Insert\n\t2.display\n\t3.DFS\n\t4.BFS\n\t5."
           "dijkstra\n\t0.quit\n");
    choice = sScan();

    switch (choice) {
    case 1: {
      i32 dest, src, weight;
      printf("\nEnter the source: ");
      src = sScan();
      printf("\n");
      printf("\nEnter the destination: ");
      dest = sScan();
      printf("\n");
      printf("\nEnter the weight: ");
      weight = sScan();
      printf("\n");
      if (dest < myGraph.vertices && src < myGraph.vertices) {

        addEdges(&myGraph, src, dest, weight);
      } else {
        printf("Invalid source and destination\n");
      }
      break;
    }
    case 2: {
      display(&myGraph);
      break;
    }
    case 3: {
      i32 startValue = 0;
      printf("Enter the start vertix: ");
      startValue = sScan();
      if (startValue >= 0 && startValue < myGraph.vertices) {

        dfs(&myGraph, startValue);
      } else {
        printf("\nInvalid vertices\n");
      }
      break;
    }
    case 4: {
      i32 startValue = 0;
      printf("Enter the start vertix: ");
      startValue = sScan();
      if (startValue >= 0 && startValue < myGraph.vertices) {

        bfs(&myGraph, startValue);
      } else {
        printf("\nInvalid vertices\n");
      }
      break;
    }
    case 5: {
      i32 starValue = 0;
      printf("Enter the start vertix: ");
      starValue = sScan();
      dijkstra(&myGraph, starValue);
      break;
    }
    case 0: {
      break;
    }
    }
  } while (choice != 0);
  return 0;
}
