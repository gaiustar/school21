CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE

all : s21_cat

s21_cat : main.o reader.o parser.o
	${CC} ${CFLAGS} main.o reader.o parser.o -g -o s21_cat

main.o : main.c
	${CC} ${CFLAGS} -c main.c

reader.o : reader.c
	${CC} ${CFLAGS} -c reader.c

parser.o : parser.c
	${CC} ${CFLAGS} -c parser.c

test_leak : rebuild
	sh test_leak_cat.sh

test_func : rebuild
	sh test_func_cat.sh
	
check : s21_cat
	cp ../../materials/linters/CPPLINT.cfg ./
	cp ../../materials/linters/.clang-format ./
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	clang-format -n *.c *.h
	rm -f ./.clang-format ./CPPLINT.cfg
		
clean :
	rm -rf *.o s21_cat *.log

rebuild : clean all