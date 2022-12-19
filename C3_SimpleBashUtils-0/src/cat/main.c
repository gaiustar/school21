#include <stdio.h>

#include "parser.h"
#include "reader.h"

int main(int argc, char **argv) {
  opt options = {0};
  int error = 0;

  error = parser(argc, argv, &options);
  if (!error) reader(argc, argv, &options);

  return 0;
}
