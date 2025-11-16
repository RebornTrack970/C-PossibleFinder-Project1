#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

int main(void) {
    printf("Would you like to use a file or enter your own expression?\n");
    printf("1: Enter in console\n2: File\n");

    int num;
    scanf(" %d",&num);
    int c; while ((c = getchar()) != '\n' && c != EOF) { } //Clear input

    char arr[100];
    if (num==1) {
        printf("Enter your Expression: \n");
        fgets(arr, sizeof(arr), stdin);
    }else if (num==2) {
        printf("Reading Expression from File.");
        FILE *file;
        file = fopen("expression.txt", "r");
        fgets(arr, 100, file);
    }else {
        printf("Unknown Choice Specified. Exiting Program.");
        exit(0);
    }
    //Finish Reading and Parse.

    Node *mainPtr;
    int i=0;
    for (; i<strlen(arr) && arr[i] != '\n' && arr[i] != EOF; i++) {
        if (arr[i]==' ') continue;

    }
    return 0;

}