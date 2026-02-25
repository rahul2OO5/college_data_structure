#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int roll_number;
  float marks;
  char name[21];
} Student;

void fillStudent(Student *ptr, int size);
float highestMarks(Student *ptr, int size);

int main() {
  int size;
  printf("Enter the size: ");
  scanf("%d", &size);
  if (size <= 0) {
    printf("Invalid input!");
    return 1;
  }

  Student *ptr = malloc(sizeof(Student) * size);
  if (ptr == NULL) {
    printf("Memory allocation failed");
    return 1;
  }

  fillStudent(ptr, size);
  printf("\n");
  float topMarks = highestMarks(ptr, size);
  printf("Highest Marks is %f ", topMarks);
  free(ptr);
  printf("\n");
  return 0;
}

void fillStudent(Student *ptr, int size) {
  int i = 0;
  for (i = 0; i < size; i++) {
    printf("Enter the name: ");
    scanf(" %20[^\n]", (ptr + i)->name);
    printf("\n");
    printf("Enter roll No. ");
    scanf("%d", &(ptr + i)->roll_number);
    printf("\n");
    printf("Enter the marks: ");
    scanf("%f", &(ptr + i)->marks);
  }
}

float highestMarks(Student *ptr, int size) {
  int i = 0;
  float max = ptr->marks;
  for (i = 0; i < size; i++) {
    if (max < (ptr + i)->marks)
      max = (ptr + i)->marks;
  }
  return max;
}
