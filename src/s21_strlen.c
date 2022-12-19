#include "s21_string.h"
#include <string.h>
#include <stdio.h>

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  for (; *(str + length); length++)
    ;
  return length;
}

int main() {
  char str[] = "hello";
  printf("%ld\n", strlen(str));
  printf("---------\n");
  printf("%ld", s21_strlen(str));
  
  return 0;
}