#ifndef SRC_CAT_PARSER_H_
#define SRC_CAT_PARSER_H_

#include <getopt.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;

static struct option const long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                             {"number", 0, 0, 'n'},
                                             {"squeeze-blank", 0, 0, 's'},
                                             {0, 0, 0, 0}};

int parser(int argc, char **argv, opt *options);

#endif  // SRC_CAT_PARSER_H_
