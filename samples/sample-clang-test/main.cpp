#include <stdio.h>
int a;
void func() {
    printf("hello\n");
}
int main() {
  a = 0;
  a = 2;
  func();
  func();
  func();
}

