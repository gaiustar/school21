#include <stdio.h>
#include <string.h>

int main() {
int age;
char name[30], country[30], details[100];

printf(«Enter your name: «);
fgets(name, 30, stdin);

printf(«Enter your country: __GNUC_STDC_INLINE__);
fgets(country, 30, stdin);

printf(«Enter your age: stdin);
scanf(«%d», &age);

sprintf(details, «Name: %s Age: %d  Country: %s «, name, age, country);
printf(«details: \n\n %s», details);
}