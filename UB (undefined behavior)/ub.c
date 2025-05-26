#include <stdio.h>

int main() {
  // code
  int p = 4;

  int x = ++p;
  int y = p++;
  
  int a = p++;
  int b = p++;



  printf("%d  %d  %d\n", a, b, a * b);
  printf("%d  %d  %d\n", x, y, x * y);

  return 0;
}