#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 40
#define BASE 10

typedef int32_t i32;

typedef struct Tree {
  i32 value;
  struct Tree *left;
  struct Tree *right;
} Tree;

typedef struct {
  i32 value;
  i32 choice;
} Information;

enum {
  Insert = 1,
  Inorder = 2,
  Postorder = 3,
  Preorder = 4,
  quit = 0

};

static i32 sScan();
static struct Tree *init(Information info);
static struct Tree *insertion(Tree *parent, Information info);
static void inorder(Tree *parent);
static void preorder(Tree *parent);
static void postorder(Tree *parent);

int main() {
  Tree *parent = NULL;
  Information myInfo;
  myInfo.value = 0, myInfo.choice = 0;
  printf("\nEnter the value of parent: ");
  myInfo.value = sScan();
  parent = init(myInfo);
  printf("\n");

  do {
    printf("\n \e[38;5;166m Enter the choice: "
           "\n\t1.Insert\n\t2.Inorder\n\t3.Postorder\n\t4.preorder\n\t0.quit "
           "\e[0m\n");
    printf("\e[38;5;166m Enter choice: \e[0m");
    myInfo.choice = sScan();
    printf("\n");

    switch (myInfo.choice) {
    case Insert: {
      printf("\n\t\t\e[38;5;197m Enter value: \e[0m ");
      myInfo.value = sScan();
      printf("\n");
      insertion(parent, myInfo);
      break;
    }
    case Inorder: {
      inorder(parent);
      printf("\n");
      break;
    }

    case Postorder: {
      postorder(parent);
      printf("\n");
      break;
    }
    case Preorder: {
      preorder(parent);
      printf("\n");
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

  return 0;
}

i32 sScan() {
  char buffer[BUFFER];

  if (fgets(buffer, BUFFER, stdin) == NULL) {
    return 0;
  }
  return (i32)strtol(buffer, NULL, BASE);
}

struct Tree *init(Information info) {
  Tree *new_child = (Tree *)malloc(sizeof(Tree));
  if (new_child == NULL) {
    printf("\nmemory allocation failed\n");
    return 0;
  }
  new_child->value = info.value;
  new_child->left = NULL;
  new_child->right = NULL;

  return new_child;
}

struct Tree *insertion(Tree *parent, Information info) {
  if (parent == NULL) {
    return init(info);
  } else if (info.value < parent->value) {
    parent->left = insertion(parent->left, info);
  } else if (info.value >= parent->value) {
    parent->right = insertion(parent->right, info);
  }
  return parent;
}

void inorder(Tree *parent) {
  if (parent != NULL) {
    inorder(parent->left);
    printf("\e[38;5;196m %d  \e[0m", parent->value);
    inorder(parent->right);
  }
}

void preorder(Tree *parent) {
  if (parent != NULL) {
    printf("\e[38;5;191m %d  \e[0m", parent->value);
    preorder(parent->left);
    preorder(parent->right);
  }
}

void postorder(Tree *parent) {
  if (parent != NULL) {
    postorder(parent->left);
    postorder(parent->right);
    printf("\e[32m %d  \e[0m", parent->value);
  }
}
