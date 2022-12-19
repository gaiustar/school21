CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

SRCS = s21_strcmp.c s21_strncmp.c s21_strlen.c
OBJS = $(SRCS:.c=.o)

all :

s21_string.a :
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rc s21_string.a $(OBJS)
	ranlib s21_string.a

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@
	
test: s21_string.a
	$(CC) $(CFLAGS) -c check*.c main.c
	ar rc check_test.a check*.o
	ranlib check_test.a
	$(CC) $(CFLAGS) --coverage -o test check_test.a $(SRCS) main.o -lcheck
	./test

# c - Захват данных о покрытии
#The . is the current directory
#--no-external для игнорирования данных о покрытии для внеш исходных файлов

gcov_report:
	$(CC) --coverage -lcheck check*.c s21*.c -o ./gcov
	./gcov
	lcov -t "./gcov" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

clang :
	# cp ../../materials/linters/CPPLINT.cfg ./
	# cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	cp ../../materials/linters/.clang-format ./
	clang-format -n *.c *.h
	rm -f ./.clang-format ./CPPLINT.cfg
		

leaks_linux:
	valgrind sh $./test --leak-check=full

leaks_mac:
	CK_FORK=no leaks --atExit -- ./test

clean :
	rm -rf *.o *.a *.gcov *.gch *.gcda *.gcno *.info *.out

rebuild : clean all