#include <stdio.h>

int main(void) {
    printf("Would you like to use a file or enter your own expression?\n");
    printf("1: file\n2: enter in console\n");
    int num;
    scanf("%d",&num);
    char arr[30];
    if (num==1) {
        fgets(arr, sizeof(arr), stdin);
    }else if (num==2) {

    }else {
        printf("Unknown Choice Spesified. Exiting Program.");
        exit(0);
    }
    return 0;

}