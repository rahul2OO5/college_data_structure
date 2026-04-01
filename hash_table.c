#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 20
#define BUFFER 40
#define BASE 10

typedef int64_t i64;
typedef uint64_t u64;

typedef struct Node {
  char *key;
  i64 value;
  struct Node *next;
} Node;

typedef struct HashTable {
  Node **holder;
} HashTable;

static u64 hash(const char *key);
static HashTable *createTable();
static void insert(HashTable *table, const char *key, i64 value);
static i64 search(HashTable *table, const char *key);
static void freeTable(HashTable *table);

int main() {
  HashTable *myTable = createTable();

  insert(myTable, "Alice", 25);
  insert(myTable, "Bob", 30);
  insert(myTable, "Charlie", 35);

  insert(myTable, "Elcia", 40);

  printf("Alice's age: %lld\n", search(myTable, "Alice"));
  printf("Bob's age: %lld\n", search(myTable, "Bob"));
  printf("Elcia's age: %lld\n", search(myTable, "Elcia"));
  printf("David's age: %lld\n", search(myTable, "David"));

  freeTable(myTable);

  return 0;
}

u64 hash(const char *key) {
  u64 hashValue = 0;
  for (i64 counter = 0; key[counter] != '\0'; counter++) {
    hashValue += key[counter];
  }
  return hashValue % TABLE_SIZE;
}

HashTable *createTable() {
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));

  table->holder = (Node **)malloc(TABLE_SIZE * sizeof(Node *));

  for (i64 counter = 0; counter < TABLE_SIZE; counter++) {
    table->holder[counter] = NULL;
  }
  return table;
}

void insert(HashTable *table, const char *key, i64 value) {
  u64 index = hash(key);

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->key = strdup(key);
  newNode->value = value;

  newNode->next = table->holder[index];
  table->holder[index] = newNode;
}

i64 search(HashTable *table, const char *key) {
  u64 index = hash(key);

  Node *current = table->holder[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->value;
    }
    current = current->next;
  }
  return -1;
}

void freeTable(HashTable *table) {
  for (i64 counter = 0; counter < TABLE_SIZE; counter++) {
    Node *current = table->holder[counter];

    while (current != NULL) {
      Node *temp = current;
      current = current->next;
      free(temp->key);
      free(temp);
    }
  }
  free((void *)table->holder);
  free(table);
}
