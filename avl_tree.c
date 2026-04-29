#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int32_t i32;

// We added 'height' to the struct
typedef struct Node {
  i32 value;
  i32 height;
  struct Node *children[2];
} Node;

// ==========================================
// UTILITY FUNCTIONS
// ==========================================

static inline i32 getMax(i32 a, i32 b) { return (a > b) ? a : b; }

static inline i32 getHeight(Node *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

// Balance is Left Height - Right Height
static inline i32 getBalance(Node *node) {
  if (node == NULL)
    return 0;
  return getHeight(node->children[0]) - getHeight(node->children[1]);
}

Node *initNode(i32 value) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("\nMemory allocation failed!\n");
    return NULL;
  }
  newNode->value = value;
  newNode->height = 1; // New nodes start with a height of 1
  newNode->children[0] = NULL;
  newNode->children[1] = NULL;
  return newNode;
}

static Node *findMin(Node *root) {
  while (root != NULL && root->children[0] != NULL) {
    root = root->children[0];
  }
  return root;
}

// ==========================================
// AVL ROTATIONS (Branchless Magic!)
// ==========================================
// dir = 0: Rotate Left  (Right child goes up)
// dir = 1: Rotate Right (Left child goes up)
static Node *rotate(Node *root, i32 dir) {
  Node *newRoot = root->children[1 - dir];

  // Perform rotation
  root->children[1 - dir] = newRoot->children[dir];
  newRoot->children[dir] = root;

  // Update heights (must update original root first, then newRoot)
  root->height =
      1 + getMax(getHeight(root->children[0]), getHeight(root->children[1]));
  newRoot->height = 1 + getMax(getHeight(newRoot->children[0]),
                               getHeight(newRoot->children[1]));

  return newRoot;
}

// ==========================================
// INSERTION & DELETION
// ==========================================

Node *insert(Node *root, i32 value) {
  // 1. Standard BST Insertion
  if (root == NULL) {
    return initNode(value);
  }
  if (root->value == value) {
    return root; // Duplicates not allowed
  }

  // Branchless traversal
  i32 pos = (root->value < value);
  root->children[pos] = insert(root->children[pos], value);

  // 2. Update height of current node
  root->height =
      1 + getMax(getHeight(root->children[0]), getHeight(root->children[1]));

  // 3. Get balance factor to check if it became unbalanced
  i32 balance = getBalance(root);

  // 4. The Repair Phase (Rotations)
  // Left Heavy
  if (balance > 1) {
    if (getBalance(root->children[0]) < 0) {
      // Left-Right Case
      root->children[0] = rotate(root->children[0], 0); // Rotate Left
    }
    // Left-Left Case
    return rotate(root, 1); // Rotate Right
  }

  // Right Heavy
  if (balance < -1) {
    if (getBalance(root->children[1]) > 0) {
      // Right-Left Case
      root->children[1] = rotate(root->children[1], 1); // Rotate Right
    }
    // Right-Right Case
    return rotate(root, 0); // Rotate Left
  }

  return root;
}

Node *deleteNode(Node *root, i32 value) {
  // 1. Standard BST Deletion
  if (root == NULL)
    return NULL;

  if (root->value == value) {
    // 0 or 1 child
    if (root->children[0] == NULL || root->children[1] == NULL) {
      Node *temp = root->children[0] ? root->children[0] : root->children[1];
      if (temp == NULL) { // 0 children
        temp = root;
        root = NULL;
      } else {         // 1 child
        *root = *temp; // Copy contents
      }
      free(temp);
    } else {
      // 2 children
      Node *temp = findMin(root->children[1]);
      root->value = temp->value;
      root->children[1] = deleteNode(root->children[1], temp->value);
    }
  } else {
    // Branchless search
    i32 pos = (root->value < value);
    root->children[pos] = deleteNode(root->children[pos], value);
  }

  // If tree had only one node, return
  if (root == NULL)
    return root;

  // 2. Update Height
  root->height =
      1 + getMax(getHeight(root->children[0]), getHeight(root->children[1]));

  // 3. Get Balance
  i32 balance = getBalance(root);

  // 4. The Repair Phase (Same as insertion!)
  if (balance > 1) {
    if (getBalance(root->children[0]) < 0) {
      root->children[0] = rotate(root->children[0], 0);
    }
    return rotate(root, 1);
  }
  if (balance < -1) {
    if (getBalance(root->children[1]) > 0) {
      root->children[1] = rotate(root->children[1], 1);
    }
    return rotate(root, 0);
  }

  return root;
}

// ==========================================
// TREE CHECKERS
// ==========================================

bool isTreeBalanced(Node *root) {
  if (root == NULL)
    return true;

  i32 balance = getBalance(root);
  // An AVL tree requires every node to have a balance of -1, 0, or 1.
  if (abs(balance) > 1)
    return false;

  return isTreeBalanced(root->children[0]) && isTreeBalanced(root->children[1]);
}

void inorder(Node *root) {
  if (root != NULL) {
    inorder(root->children[0]);
    printf("\e[38;5;196m %d \e[0m", root->value);
    inorder(root->children[1]);
  }
}

void preorder(Node *root) {
  if (root != NULL) {
    printf("\e[38;5;191m %d \e[0m", root->value);
    preorder(root->children[0]);
    preorder(root->children[1]);
  }
}

// ==========================================
// MAIN FUNCTION (TESTING)
// ==========================================

int main() {
  Node *root = NULL;

  // Inserting nodes that would create a skewed line in a normal BST
  // The AVL tree will automatically rotate to keep it perfectly balanced!
  i32 valuesToInsert[] = {10, 20, 30, 40, 50, 25};
  i32 numValues = sizeof(valuesToInsert) / sizeof(valuesToInsert[0]);

  printf("Inserting values into AVL Tree...\n");
  for (i32 i = 0; i < numValues; i++) {
    root = insert(root, valuesToInsert[i]);
  }

  printf("\nPreorder Traversal (shows the new structure after rotations):\n");
  preorder(root);
  printf("\n");

  printf("\nIs the tree strictly balanced? %s\n",
         isTreeBalanced(root) ? "Yes!" : "No!");

  printf("\nDeleting 30...\n");
  root = deleteNode(root, 30);

  printf("\nPreorder Traversal after deletion:\n");
  preorder(root);
  printf("\n");

  return 0;
}
