#include <stdio.h>

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point top_left;
  Point bottom_right;
} Rectangle;

int area(Rectangle *rect);

int main() {
  Rectangle rect;
  Rectangle *ptr_r = &rect;

  printf("Enter the lenght(x) of rectangle: ");
  scanf("%d", &(ptr_r)->top_left.x);
  printf("Enter the length(y) of rectangle: ");
  scanf("%d", &(ptr_r)->top_left.y);

  printf("Enter the lenght(x) of rectangle: ");
  scanf("%d", &(ptr_r)->bottom_right.x);
  printf("Enter the length(y) of rectangle: ");
  scanf("%d", &(ptr_r)->bottom_right.y);

  int rect_area = area(ptr_r);
  printf("Area of the rectangle: %d", rect_area);
  return 0;
}

int area(Rectangle *rect) {
  int length = rect->bottom_right.x - rect->top_left.x;
  int breadth = rect->bottom_right.y - rect->top_left.y;

  int area = length * breadth;
  return area;
}
