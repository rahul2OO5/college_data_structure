#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 40
#define BASE 10

typedef int32_t i32;

typedef struct Node {
  i32 value;
  struct Node *children[2];
} Node;

typedef struct {
  i32 value;
  i32 choice;
} Information;

enum {
  Insert = 1,
  Inorder = 2,
  Postorder = 3,
  Preorder = 4,
  Search = 5,
  Height = 6,
  Delete = 7,
  BST = 8,
  quit = 0

};

static i32 sScan();
static struct Node *init(Information info);
static struct Node *insertion(Node *root, Information info);
static void inorder(Node *root);
static void preorder(Node *root);
static void postorder(Node *root);
static void freeTree(Node *root);
static bool search(Node *root, Information info);
static inline i32 getMax(i32 num1, i32 num2);
static i32 getHeight(Node *root);
static Node *findMin(Node *root);
static Node *delete(Node *root, Information info);
static bool isUtil(Node *root, i32 minValue, i32 maxValue);
static bool isBST(Node *root);

int main() {
  Node *root = NULL;
  Information myInfo;
  myInfo.value = 0, myInfo.choice = 0;
  printf("\nEnter the value for root: ");
  myInfo.value = sScan();
  root = init(myInfo);
  printf("\n");

  do {
    printf("\n \e[38;5;166m Enter the choice: "
           "\n\t1.Insert\n\t2.Inorder\n\t3.Postorder\n\t4.preorder\n\t5."
           "Search\n\t6.Height\n\t7.Delete\n\t8.isBsd\n\t0.quit "
           "\e[0m\n");
    printf("\e[38;5;166m Enter choice: \e[0m");
    myInfo.choice = sScan();
    printf("\n");

    switch (myInfo.choice) {
    case Insert: {
      printf("\n\t\t\e[38;5;197m Enter value: \e[0m ");
      myInfo.value = sScan();
      printf("\n");
      root = insertion(root, myInfo);
      break;
    }
    case Inorder: {
      inorder(root);
      printf("\n");
      break;
    }

    case Postorder: {
      postorder(root);
      printf("\n");
      break;
    }
    case Preorder: {
      preorder(root);
      printf("\n");
      break;
    }
    case Search: {
      printf("\n\t\t\e[38;5;197m Enter value: \e[0m ");
      myInfo.value = sScan();
      printf("\n");
      if (search(root, myInfo)) {
        printf("\n\n\t\e[38;5;197m %d found in tree\e[0m\n", myInfo.value);
      } else {
        printf("\n\n\t\e[38;5;197m %d not found in tree\e[0m\n", myInfo.value);
      }
      break;
    }
    case Height: {
      i32 maxHeight = getHeight(root);
      printf("\n\n\t\e[38;5;197m height of tree is %d \e[0m\n", maxHeight);
      break;
    }
    case Delete: {
      printf("\n\t\t\e[38;5;197m Enter value: \e[0m ");
      myInfo.value = sScan();
      printf("\n");
      root = delete(root, myInfo);
      break;
    }
    case BST: {
      if (isBST(root)) {
        printf("\n\t\e[32m The tree is a valid Binary Search Tree. \e[0m\n");
      } else {
        printf(
            "\n\t\e[31m The tree is NOT a valid Binary Search Tree! \e[0m\n");
      }
      break;
    }

    case quit: {
      break;
    }
    default: {
      printf("\nUnexpected error occur\n");
    }
    }

  } while (myInfo.choice != 0);

  freeTree(root);

  return 0;
}

i32 sScan() {
  char buffer[BUFFER];
  if (fgets(buffer, BUFFER, stdin) == NULL) {
    return 0;
  }
  return (i32)strtol(buffer, NULL, BASE);
}

struct Node *init(Information info) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("\nMemory alloction failed!\n");
    return NULL;
  }
  new_node->value = info.value;
  new_node->children[0] = NULL;
  new_node->children[1] = NULL;
  return new_node;
}

struct Node *insertion(Node *root, Information info) {
  if (root == NULL) {
    return init(info);
  }
  i32 pos = (root->value <= info.value);
  root->children[pos] = insertion(root->children[pos], info);
  return root;
}

bool search(Node *root, Information info) {
  if (root == NULL) {
    return false;
  }
  if (root->value == info.value) {
    return true;
  }
  i32 pos = (root->value <= info.value);
  return search(root->children[pos], info);
}

void inorder(Node *root) {
  if (root != NULL) {
    inorder(root->children[0]);
    printf("\e[38;5;196m %d  \e[0m", root->value);
    inorder(root->children[1]);
  }
}

void preorder(Node *root) {
  if (root != NULL) {
    printf("\e[38;5;191m %d  \e[0m", root->value);
    preorder(root->children[0]);
    preorder(root->children[1]);
  }
}

void postorder(Node *root) {
  if (root != NULL) {
    postorder(root->children[0]);
    postorder(root->children[1]);
    printf("\e[32m %d  \e[0m", root->value);
  }
}

void freeTree(Node *root) {
  if (root != NULL) {
    freeTree(root->children[0]);
    freeTree(root->children[1]);
    free(root);
  }
}

inline i32 getMax(i32 num1, i32 num2) { return (num1 > num2) ? num1 : num2; }

i32 getHeight(Node *root) {
  if (root == NULL) {
    return -1;
  }
  i32 leftHeight = getHeight(root->children[0]);
  i32 rightHeight = getHeight(root->children[1]);
  return 1 + getMax(leftHeight, rightHeight);
}

Node *findMin(Node *root) {
  while (root != NULL & root->children[0] != NULL) {
    root = root->children[0];
  }
  return root;
}

Node *delete(Node *root, Information info) {
  if (root == NULL) {
    return NULL;
  }
  if (root->value == info.value) {
    if (root->children[0] == NULL) {
      Node *temp = root->children[1];
      free(root);
      return temp;
    } else if (root->children[1] == NULL) {
      Node *temp = root->children[0];
      free(root);
      return temp;
    }
    Node *temp = findMin(root->children[1]);
    root->value = temp->value;
    Information tempInfo;
    tempInfo.value = temp->value;
    tempInfo.choice = 0;
    root->children[1] = delete(root->children[1], tempInfo);
  } else {
    i32 pos = (root->value < info.value);
    root->children[pos] = delete(root->children[pos], info);
  }
  return root;
}

bool isUtil(Node *root, i32 minValue, i32 maxValue) {
  if (root == NULL) {
    return true;
  }
  if (root->value <= minValue || root->value >= maxValue) {
    return false;
  }
  return isUtil(root->children[0], minValue, root->value) &&
         isUtil(root->children[1], root->value, maxValue);
}

bool isBST(Node *root) { return isUtil(root, INT32_MIN, INT32_MAX); }

void levelOrder(Node *root) {
  if (root == NULL) {
    return;
  }

  i32 MAX_Q_SIZE = 1000;
  Node **queue = (Node **)malloc(MAX_Q_SIZE * sizeof(Node *));
  if (queue == NULL) {
    printf("memory allocation failed\n");
    return;
  }
  i32 front = 0, rear = 0;
  queue[rear++] = root;
  while (rear > front) {
    Node *current = queue[front++];
    printf("\e[38;5;51m %d  \e[0m", current->value);
    for (i32 i = 0; i < 2; i++) {
      if (current->children[i] != NULL) {
        if (rear < MAX_Q_SIZE) {
          queue[rear++] = current->children[i];
        } else {
          printf("queue overflow");
          free(queue);
          return;
        }
      }
    }
  }
  free(queue);
}
