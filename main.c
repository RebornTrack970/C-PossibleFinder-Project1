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

struct Node* simplfy(struct Node* head) {
    while (1) {
        int pass = 0;
        struct Node* cur = head;
        struct Node* prev = NULL;

        while (cur != NULL && cur->next != NULL && cur->next->next != NULL) {
            if (cur->type == OPERAND && cur->next->type == OPERAND && cur->next->next->type == OPERATOR) {
                cur->data = doCalc(cur->data, cur->next->data, (char)cur->next->next->data);

                struct Node* t2 = cur->next;
                struct Node* t1 = cur->next->next;
                cur->next = t1->next;

                free(t2);
                free(t1);
                pass = 1;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        if (pass == 0) break;
    }
    return head;
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
    list = reverse(simplfy(list)); //simplfy func

    printf("Expression in Simple Form is:\n");
    read(&list); printf("= %d\n",result);




    return 0;

}