#include "s21_string.h"
#include <string.h>

char *s21_strerror(int errnum){
static const char *error[] = {0};

#ifdef __APPLE__
    sprintf(*error, "%s%d", "Unknown error: ", errnum);
#elif __linux__
    sprintf(*error, "%s%d", "Unknown error ", errnum);
#endif

return error;
}

int main() {
  char str[] = "hello";
  printf("%d\n", strerror(errnum));
  printf("---------\n");
  printf("%d", s21_strerror(errnum));
  
  return 0;
}   

