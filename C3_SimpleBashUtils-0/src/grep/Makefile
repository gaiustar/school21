CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE

all : s21_grep

s21_grep : s21_grep.c
	${CC} ${CFLAGS} s21_grep.c -o s21_grep

s21_grep.o : s21_grep.c
	${CC} ${CFLAGS} -c s21_grep.c

check : s21_grep
	cp ../../materials/linters/CPPLINT.cfg ./
	cp ../../materials/linters/.clang-format ./
	# cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	clang-format -n *.c *.h
	rm -f ./.clang-format ./CPPLINT.cfg
		
test_func : rebuild
	sh test_func_grep.sh

test_leak : rebuild
	sh test_leak_grep.sh

clean :
	rm -rf *.o s21_grep *.log

rebuild : clean all