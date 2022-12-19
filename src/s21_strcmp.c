// Сравнивает строку, на которую указывает str1 со строкой, на которую указывает
// str2 (функция возвращает 0,если str1=str2, >1 если str1>str2 и <1, если str1<str2)

#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  for (; *str1 && *str1 == *str2; str1++, str2++)
    ;
  return *str1 - *str2;
}

int main() {
  char str1[50] = "hello";
  char str2[50] = "hello";

  char str3[50] = "hello"; //104  h 
  char str4[50] = "world!"; // 119  w

  char str5[50] = "world!"; // 119  w
  char str6[50] = "hello"; //104  h 

  char str7[50] = "hello"; // 32
  char str8[50] = "Hello"; // 32
  
  printf("strcmp = %d\n", strcmp(str1, str2));
  printf("%d\n", *str1 - *str2);
  printf("---------\n");
  printf("s21_strcmp = %d\n", s21_strcmp(str1, str2));
  printf("%d\n", *str1 - *str2);

  printf("strcmp = %d\n", strcmp(str3, str4));
  printf("%d\n", *str3 - *str4);
  printf("---------\n");
  printf("s21_strcmp = %d\n", s21_strcmp(str3, str4));
  printf("%d\n", *str3 - *str4);

  printf("strcmp = %d\n", strcmp(str5, str6));
  printf("%d\n", *str5 - *str6);
  printf("---------\n");
  printf("s21_strcmp = %d\n", s21_strcmp(str5, str6));
  printf("%d\n", *str5 - *str6);

  printf("strcmp = %d\n", strcmp(str7, str8));
  printf("%d\n", *str7 - *str8);
  printf("---------\n");
  printf("s21_strcmp = %d\n", s21_strcmp(str7, str8));
  printf("%d\n", *str7 - *str8);
}