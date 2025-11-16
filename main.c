#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;

};

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int doCalc(int num1, int num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        case '^':
            return pow(num1, num2);
        default:
            printf("Unkown Operation.");
            return 0;
    }
}

void insert(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = (*head);
    *head = newNode;
}
void read(struct Node** head) {
    struct Node* temp = *head;
    if (temp->next != NULL) {read(&temp->next);}
    printf("%c", temp->data);
}

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
    //Finish Reading and Parse into Linked List.
    int result = 0;
    struct Node *list = NULL;
    int i=0;
    for (; i<strlen(arr) && arr[i] != '\n' && arr[i] != EOF && arr[i] != '='; i++) {
        if (arr[i]==' ') continue;
        insert(&list,arr[i]);
    }
    if (arr[i]=='=') result = arr[i+2] - '0'; // if it isnt equal to 0.
    //read(&list);

    //Try Doing all Operations that we can.
    struct Node head = *list;
    while (head.next.next != NULL) {
        if (isDigit(head.data) && isDigit(head.next->data) && isOperator(head.next->next->data)) {

        }
    }


    return 0;

}