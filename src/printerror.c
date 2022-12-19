#include <stdio.h>
#include <string.h>

// int main() {
//     for (int i = 0; i < 108; i++) {
//         printf("%s\n", strerror(i));
//     }
// }

int main(){
    
    for(int i; i < 107; i++){
        fprintf(stdout, "\"%s\",\n", strerror(i));
    }
}