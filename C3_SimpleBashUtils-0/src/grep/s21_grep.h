#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int empty;
} opt;

void flag_f(char *optarg, int counte, char *pattern, opt *options);
void parser(int argc, char **argv, opt *options, char *pattern, int *status);
void flag_c(opt *options, char **argv, int *count_lines, int *index_files);
void flag_n(opt *options, char **argv, size_t *nline, int *i);
void flag_v(opt *options, int flag_o, char buffer[BUFSIZ]);
void flag_o(opt *options, int status, int *flag_o, regmatch_t match[1],
            regex_t regex, size_t *nmatch, char buffer[BUFSIZ]);
void invers_v(int *status, opt *options);
void process_compile(FILE *f, opt *options, char *pattern, char **argv,
                     int index_files);
void open_file(int argc, char **argv, opt flag, char *pattern);
