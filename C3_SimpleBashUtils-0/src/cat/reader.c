#include "reader.h"

#include <stdio.h>

void reader(int argc, char **argv, opt *options) {
  while (optind < argc) {
    FILE *stream;
    stream = fopen(argv[optind], "r");
    if (stream == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[optind]);
    } else {
      int ch;
      int cur = 0;
      int prev = 0;
      int EOL = 1;
      int str_count = 1;
      while ((ch = getc(stream)) != EOF) {
        if (options->s) {
          if (ch == '\n') {
            if (cur == 1) {
              continue;
            }
            if (prev == 1) {
              cur = 1;
            }
            prev = 1;
          }
          if (ch != '\n') {
            prev = 0;
            cur = 0;
          }
        }

        if (options->b) {
          if (EOL == 1 && ch != '\n') {
            printf("%6d\t", str_count++);
          }
          if (ch != '\n') {
            EOL = 0;
          } else {
            EOL = 1;
          }
        }

        if (options->n && !options->b) {
          if (EOL == 1) {
            printf("%6d\t", str_count++);
          }
          if (ch != '\n')
            EOL = 0;
          else
            EOL = 1;
        }

        if (options->e) {
          if (ch == '\n') printf("$");
        }

        if (options->v) {
          if (ch >= 0 && ch < 32 && ch != '\t' && ch != '\n') {
            printf("^");
            ch = ch + 64;
          }
          if (ch == 127) {
            printf("^");
            ch = '?';
          }
        }
        if (options->t) {
          if (ch == '\t') {
            printf("^I");
            continue;
          }
        }
        putchar(ch);
      }
    }
    optind++;  // индекс текущего параметра
  }
}
