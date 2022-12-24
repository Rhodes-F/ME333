#include <stdio.h>
#include <string.h>

typedef struct {
   int  id;
   char  brand[50];
   float  miles[10];
} car;


int main( ) {

   struct car car1;

   car1.id = 1;
   car1.brand = 0; 
   for (int i = 0; i <= 9; ++i){
        car1.miles[i] = 0.0;
   }
   getBrand(car1.brand);
   printf("The result is:%s", car1.brand);
}

void getBrand(char *str);

void getBrand(char *str){

    printf("Enter the brand of the car:");
    scanf("%s",car1.brand);
}

void calcmilescar(car car){
    for (int i = 0; i < 9; ++i){
        car.miles[i+1] = car.miles[i]*2;
    }
}

void calcmilesref(car*car){
    for (int i = 0; i < 9; ++i){
        car->miles[i+1] = car->miles[i]*2;
    }
}

#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100


int main(){
    int len; // length of the entered string
    char str[MAXLENGTH]; // input should be no longer than MAXLENGTH
    int mul;
    // here, any other variables you need
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


