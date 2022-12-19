#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

int parser(int argc, char *argv[], opt *options) {
  int error = 0;
  int opt = 0;
  int option_index = 0;

  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':  // нумерует только непустые строки
        options->b = 1;
        break;
      case 'e':  // отображает символы конца строки как $
        options->e = 1;
        options->v = 1;
        break;
      case 'n':  // нумерует все выходные строки
        options->n = 1;
        break;
      case 's':  // сжимает несколько смежных пустых строк
        options->s = 1;
        break;
      case 't':  // отображает табы как ^I
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      /* GNU */
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      default:
        error = 1;
        fprintf(stderr, "usage: cat [-benstuv] [file ...]\n");
    }
  }
  return error;
}
