#include <stdio.h>
#include <string.h>

int main(void) {
    char str[200];
    char ch;
    int index = 0;

    printf("Enter String: ");

    while (1) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        str[index++] = ch;
    }
    str[index] = '\0'; 

    int i = 0;
    int length = strlen(str);


if (length<2){
    printf("\nInvalid String");
    return 0;
}
    if(str[i]!='a'){
         printf("\nInvalid String");
         return 0;
    }
    while (i < length && str[i] == 'a') {
        i++; 
    }

   
    if (i < length && str[i] == 'b' && (i + 1 < length) && str[i + 1] == 'b' && (i + 2 == length)) {
 
printf("\nValid String");

        
    } else {
        printf("\nInvalid String");
    }

    return 0;
}
