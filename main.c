#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TYPE {OPERAND,OPERATOR,UNKNOWN};

struct Node {
    int data;
    int type;
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
            return (int)pow(num1, num2);
        default:
            printf("Unknown Operation.");
            return 0;
    }
}

void insert(struct Node** head, int data, int type) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->type = type;
    newNode->next = (*head);
    *head = newNode;
}
void read(struct Node** head) {
    struct Node* temp = *head;
    if (temp->next != NULL) {read(&temp->next);}
    if (temp->type == OPERAND) printf("%d ", temp->data);
    else printf("%c ", (char)temp->data);
}

struct Node* reverse(struct Node* head) {
    struct Node *prev = NULL;
    struct Node *next_node = NULL;
    struct Node *cur = head;
    while (cur != NULL) {
        next_node = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next_node;
    }
    return prev;
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
        if (!isDigit(arr[i])) {
            insert(&list,arr[i],isOperator(arr[i]) ? OPERATOR : UNKNOWN);
            continue;
        }
        int num = 0;
        while (isDigit(arr[i])) {
            num = num * 10 + (arr[i] - '0');
            i++;
        }
        i--;
        insert(&list,num,OPERAND);
    }
    if (arr[i]=='=') result = arr[i+2] - '0'; // if it isnt equal to 0.
    //read(&list);

    list = reverse(list); // Had to reverse... it didnt work otherwise...
    //Try Doing all Operations that we can.
    struct Node *Stack = NULL;
    struct Node *cur = list;
    while (cur != NULL) {
        if (cur->type == OPERAND) {
            insert(&Stack, cur->data, OPERAND); //add to stack if number (learned from the ppt for trees XD)
        }else if (cur->type == OPERATOR) {

        }else { //For unknown, uh, idk for now.

        }
    }

    read(&list);


    return 0;

}