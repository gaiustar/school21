#include <stdio.h>
#define MSG "helloVika"

int main() {
  char words[] = "hello";
  const char *p = "Как у тебя дела?";
  printf("%s", words);
  puts(words);
  puts(MSG);
  words[0] = 'P';
  puts(words);
  puts(p);
  printf("%s, %p, %c\n", "Мы", "-", *"космические бродяги");
  return 0;
}