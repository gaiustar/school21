#include "s21_grep.h"

void flag_f(char *optarg, int counte, char *pattern, opt *options) {
  FILE *f = NULL;
  if ((f = fopen(optarg, "r")) == NULL) {
    printf("%s: No such file or directory\n", optarg);
  } else {
    while (feof(f) == 0) {
      if (counte != 0) {
        strcat(pattern, "|");
      }
      size_t lenght = strlen(pattern);
      size_t lenght_result;
      fgets(pattern + lenght, BUFSIZ, f);
      char *ch = strrchr(
          pattern,
          '\n');  // strrchr – поиск последнего вхождения символа в строку
      if (ch != NULL) {
        *ch = '\0';
      }
      lenght_result = strlen(pattern);
      if (lenght_result == lenght) {
        options->empty++;
      }
      counte++;
    }
    fclose(f);
  }
}

int main(int argc, char **argv) {
  int status = 0;
  char pattern[1024] = {0};
  opt options = {0};
  if (argc > 1) {
    parser(argc, argv, &options, pattern, &status);
    if (options.e == 0 && options.f == 0) {
      strcat(pattern, argv[optind]);
      optind++;
    }
    open_file(argc, argv, options, pattern);
  }
  return 0;
}

void parser(int argc, char **argv, opt *options, char *pattern, int *status) {
  int opt = 0;
  int counte = 0;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
        if (counte != 0) {
          strcat(pattern, "|");
        }
        if (*optarg == 0) {
          options->empty++;
        }
        strcat(pattern, optarg);
        // printf("%s", pattern);
        // printf("%s", optarg);
        counte++; //счетчик паттернов
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        flag_f(optarg, counte, pattern, options);
        break;
      case 'o':
        options->o = 1;
        break;
      case '?':
        *status = 1;
        break;
      default:
        fprintf(
            stderr,
            "usage: grep [-abcDEFGHhiiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
            "[-C[num]]\n"
            "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n"
            "\t[--context[=num]] [--directories=action] [--label] "
            "[--line-buffered]\n"
            "\t[--null] [pattern] [file ...]\n");
    }
    if (*status != 0) break;
  }
  if (options->empty != 0) {
    options->o = 0;
  }
}

void flag_c(opt *options, char **argv, int *count_lines, int *index_files) {
  if (options->c == 1) {
    if ((*index_files) > 1 && options->h == 0) {
      printf("%s:", argv[optind]);
    }
    if (options->l == 1 && (*count_lines) != 0) {
      printf("1\n");
    } else {
      printf("%d\n", (*count_lines));
    }
  }
  if (options->l == 1 && (*count_lines) != 0) {
    printf("%s\n", argv[optind]);
  }
}

void flag_n(opt *options, char **argv, size_t *nline, int *index_files) {
  if ((*index_files) > 1 && options->h == 0) {
    printf("%s:", argv[optind]);
  }
  if (options->n == 1) {
    printf("%lu:", (*nline));  // unsigned long
  }
}

void flag_v(opt *options, int options_o, char buffer[BUFSIZ]) {
  if (options->o == 0 || options->v == 1) {
    printf("%s", buffer);
  }
  if (buffer[strlen(buffer) - 1] != '\n' && options_o == 0) {
    printf("\n");
  }
}

void flag_o(opt *options, int status, int *options_o, regmatch_t match[1],
            regex_t regex, size_t *nmatch, char buffer[BUFSIZ]) {
  if (options->o == 1 && options->v == 0) {
    (*options_o) = 1;
    char *word = buffer;
    while (status == 0) {
      if (match[0].rm_eo == match[0].rm_so) {
        break;
      }
      printf("%.*s\n", (int)(match[0].rm_eo - match[0].rm_so),
             word + match[0].rm_so);  //* целочисленное значение, указывающее
                                      //минимальную ширину поля
      word += match[0].rm_eo;
      status = regexec(&regex, word, (*nmatch), match, REG_NOTBOL);
    }
  }
}

void invers_v(int *status, opt *options) {
  if (options->v == 1) {
    if ((*status) == 1) {  //если нет совпадений, то инверсия для флага v
      (*status) = 0;
    } else {
      *status = 1;
    }
  }
}

void process_compile(FILE *f, opt *options, char *pattern, char **argv,
                     int index_files) {
  regex_t regex;
  regmatch_t match[1] = {0};
  int result_func = 0, count_lines = 0, status;
  size_t nmatch = 1, nline = 1;
  char buffer[BUFSIZ] = {0};
  if (options->i == 1) {
    status = regcomp(&regex, pattern, REG_ICASE);
  } else {
    status = regcomp(&regex, pattern, REG_EXTENDED);
  }
  if (status != 0) {
    result_func = 1;
    while (feof(f) == 0) {
      if (fgets(buffer, BUFSIZ, f)) {
        printf("%s", buffer);
      }
    }
  }
  if (!result_func) {
    while (feof(f) == 0) {
      if (fgets(buffer, BUFSIZ, f)) {
        int options_o = 0;
        status = regexec(&regex, buffer, nmatch, match, 0);
        invers_v(&status, options);
        if (status == 0) {
          if (options->c == 0 && options->l == 0) {
            flag_n(options, argv, &nline, &index_files);
            flag_o(options, status, &options_o, match, regex, &nmatch, buffer);
            flag_v(options, options_o, buffer);
          }
          count_lines++;
        }
        nline++;
      }
    }
    flag_c(options, argv, &count_lines, &index_files);
  }
  regfree(&regex);
}

void open_file(int argc, char **argv, opt options, char *pattern) {
  int index_files = argc - optind;
  while (optind < argc) {
    FILE *f = NULL;
    if ((f = fopen(argv[optind], "r")) == NULL) {
      if (options.s == 0) {
        printf("%s: No such file or directory\n", argv[optind]);
      }
    } else {
      process_compile(f, &options, pattern, argv, index_files);
      fclose(f);
    }
    optind++;  // индекс текущего параметра
  }
}
