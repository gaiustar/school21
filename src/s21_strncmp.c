// Сравнивает не более первых n байтов str1 и str2

#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {

  for (s21_size_t count = 0; n > count && *str1 == *str2; count++, str1++, str2++)
    ;
  return *str1 - *str2;
}

int main() {
  s21_size_t count = 7;
  char str1[50] = "hello";
  char str2[50] = "hello";

  char str3[50] = "hello";
  char str4[50] = "hello world!";

  char str5[50] = "hello world!";
  char str6[50] = "hello";
  
  printf("strncmp = %d\n", strncmp(str1, str2, count));
  printf("%d\n", *str1 - *str2);
  printf("---------\n");
  printf("s21_strncmp = %d\n", s21_strncmp(str1, str2, count));
  printf("%d\n", *str1 - *str2);

  printf("strncmp = %d\n", strncmp(str3, str4, count));
  printf("%d\n", *str3 - *str4);
  printf("---------\n");
  printf("s21_strncmp = %d\n", s21_strncmp(str3, str4, count));
  printf("%d\n", *str3 - *str4);

  printf("strncmp = %d\n", strncmp(str5, str6, count));
  printf("%d\n", *str5 - *str6);
  printf("---------\n");
  printf("s21_strncmp = %d\n", s21_strncmp(str5, str6, count));
  printf("%d\n", *str5 - *str6);
}