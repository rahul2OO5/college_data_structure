#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define BUFFER 40
#define BASE 10

typedef int32_t i32;

typedef struct Node {
  i32 dest;
  i32 weight;
  struct Node *next;
} Node;

typedef struct {
  i32 vertices;
  Node *head[MAX];
} Graph;

typedef struct {
  i32 arr[MAX];
  i32 front;
  i32 rear;
} Queue;

static void initQueue(Queue *que) {
  que->rear = 0;
  que->front = 0;
}
static i32 isQueueEmpty(Queue *que) { return (que->front >= que->rear); }
static i32 isQueueFull(Queue *que) { return (que->rear >= MAX); }
static void enqueue(Queue *que, i32 value) {
  if (isQueueFull(que))
    return;
  que->arr[que->rear++] = value;
}
static i32 dequeue(Queue *que) {
  if (isQueueEmpty(que))
    return 0;
  return (que->arr[que->front++]);
}

static void initGraph(Graph *grp, i32 vertices) {
  grp->vertices = vertices;
  for (i32 i = 0; i < vertices; i++) {
    grp->head[i] = NULL;
  }
}

static Node *createNode(i32 dest, i32 weight) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("memory allocation failed\n");
    exit(1);
  }
  newNode->dest = dest;
  newNode->weight = weight;
  newNode->next = NULL;
  return newNode;
}

static void addEdge(Graph *grp, i32 src, i32 dest, i32 weight) {
  Node *newNode = createNode(dest, weight);
  newNode->next = grp->head[src];
  grp->head[src] = newNode;
}

static void display(Graph *grp) {
  for (i32 i = 0; i < grp->vertices; i++) {
    Node *temp = grp->head[i];
    printf("Vertex: %d ", i);

    while (temp != NULL) {
      printf("-> (Dest: %d, Weight: %d) ", temp->dest, temp->weight);
      temp = temp->next;
    }
    printf("\n");
  }
}

static void dfsRecursive(Graph *grp, i32 currentVertex, i32 visited[]) {
  visited[currentVertex] = 1;
  printf("%d ", currentVertex);

  Node *temp = grp->head[currentVertex];
  while (temp != NULL) {
    if (visited[temp->dest] == 0) {
      dfsRecursive(grp, temp->dest, visited);
    }
    temp = temp->next;
  }
}

static void dfs(Graph *grp, i32 startVertex) {
  i32 visited[MAX] = {0};
  printf("\nDFS Traversal: ");
  dfsRecursive(grp, startVertex, visited);
  printf("\n");
}

static void bfs(Graph *grp, i32 startVertex) {
  i32 visited[MAX] = {0};
  Queue tempQue;
  initQueue(&tempQue);

  visited[startVertex] = 1;
  enqueue(&tempQue, startVertex);
  printf("\nBFS Traversal: ");

  while (!isQueueEmpty(&tempQue)) {
    i32 currentVertex = dequeue(&tempQue);
    printf("%d ", currentVertex);

    Node *temp = grp->head[currentVertex];
    while (temp != NULL) {
      if (visited[temp->dest] == 0) {
        visited[temp->dest] = 1;
        enqueue(&tempQue, temp->dest);
      }
      temp = temp->next;
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

static void dijkstra(Graph *grp, i32 startVertex) {
  i32 distance[MAX];
  i32 visited[MAX] = {0};

  for (i32 i = 0; i < grp->vertices; i++) {
    distance[i] = INT32_MAX;
  }
  distance[startVertex] = 0;

  for (i32 count = 0; count < grp->vertices - 1; count++) {
    i32 closest_vertice = getMinDistanceNode(distance, visited, grp->vertices);

    if (closest_vertice == -1)
      break;

    visited[closest_vertice] = 1;

    Node *temp = grp->head[closest_vertice];
    while (temp != NULL) {
      i32 neighbor = temp->dest;
      i32 edgeWeight = temp->weight;

      if (!visited[neighbor] && distance[closest_vertice] != INT32_MAX &&
          distance[closest_vertice] + edgeWeight < distance[neighbor]) {

        distance[neighbor] = distance[closest_vertice] + edgeWeight;
      }
      temp = temp->next;
    }
  }

  printf("\nShortest Distances from Vertex %d:\n", startVertex);
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
  Graph myGraph;

  i32 vertics = 0;
  printf("\nEnter the no of vertices: ");
  vertics = sScan();

  initGraph(&myGraph, vertics);

  i32 choice = 0;
  do {
    printf("\nEnter choice\n\t1.Insert Edge\n\t2.Display "
           "Graph\n\t3.DFS\n\t4.BFS\n\t5.Dijkstra\n\t0.Quit\nChoice: ");
    choice = sScan();

    switch (choice) {
    case 1: {
      i32 dest, src, weight;
      printf("Enter the source: ");
      src = sScan();
      printf("Enter the destination: ");
      dest = sScan();
      printf("Enter the weight: ");
      weight = sScan();

      if (dest >= 0 && dest < myGraph.vertices && src >= 0 &&
          src < myGraph.vertices) {
        addEdge(&myGraph, src, dest, weight);
        printf("Edge added successfully.\n");
      } else {
        printf("Invalid source or destination.\n");
      }
      break;
    }
    case 2: {
      printf("\nAdjacency List Representation:\n");
      display(&myGraph);
      break;
    }
    case 3: {
      i32 startValue = 0;
      printf("Enter the start vertex: ");
      startValue = sScan();
      if (startValue >= 0 && startValue < myGraph.vertices) {
        dfs(&myGraph, startValue);
      } else {
        printf("Invalid vertex.\n");
      }
      break;
    }
    case 4: {
      i32 startValue = 0;
      printf("Enter the start vertex: ");
      startValue = sScan();
      if (startValue >= 0 && startValue < myGraph.vertices) {
        bfs(&myGraph, startValue);
      } else {
        printf("Invalid vertex.\n");
      }
      break;
    }
    case 5: {
      i32 startValue = 0;
      printf("Enter the start vertex: ");
      startValue = sScan();
      if (startValue >= 0 && startValue < myGraph.vertices) {
        dijkstra(&myGraph, startValue);
      } else {
        printf("Invalid vertex.\n");
      }
      break;
    }
    case 0: {
      printf("Exiting...\n");
      break;
    }
    default:
      printf("Invalid choice.\n");
    }
  } while (choice != 0);

  return 0;
}
