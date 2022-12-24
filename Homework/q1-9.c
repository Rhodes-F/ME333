#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100


int main(){
    int len; // length of the entered string
    char str[MAXLENGTH]; // input should be no longer than MAXLENGTH
    int mul;
    
    scanf("%s", str);
    len = strlen(str);
    scanf("%d", &mul);

    while(!(mul >= 1 && mul<=8)){
        printf("Enter a shift between 1 and 8");
        scanf("%d", &mul);
    }

    for (int i = 0; i < len; ++i) {
        str[i]= str[i]+mul;
    }

    printf("The result is:%s", str);
    return(0);

}