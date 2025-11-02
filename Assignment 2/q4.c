#include <stdio.h>
#include<stdlib.h>

float stack[10];
int i = 0;
int TopPointer = (sizeof(stack) / sizeof(stack[0])) - 1;
int EndPointer = 0;
int flag = 0;

void push() {
    if (i <= TopPointer) {
        printf("\nEnter a float element to push in: ");
        scanf("%f", &stack[i]);
        printf("Element added successfully\n");
        i++;
    } else {
        printf("\"OVERFLOW\" : Stack is Full\n");
    }
}

float pop() {
    if (i != EndPointer) {
        i--;
        float temp = stack[i];
        stack[i] = 0;
        return temp;
    } else {
        printf("\"UNDERFLOW\" : Stack is Empty\n");
        return -1;
    }
}

float peek() {
    if (i > 0)
        return stack[i - 1];
    else {
        printf("Stack is empty\n");
        return -1;
    }
}

void display() {
    if (i == 0) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements:\n");
    for (int j = i - 1; j >= 0; j--) {
        printf("Element %d: %f\n", j+1, stack[j]);
    }
}
void pause(void) {
    int x;
    printf("\nPress ENTER to continue");
    while ((x = getchar()) != '\n' && x != EOF) { }
    getchar();
}

int main() {
    int num;
    printf("~~~~~~~~~~~ Welcome to Float Stack ~~~~~~~\n");

    while (flag == 0) {
        printf("\nEnter:\n");
        printf("1. Display Stack\n");
        printf("2. Display Last Element Inserted\n");
        printf("3. PUSH an Element\n");
        printf("4. POP an Element\n");
        printf("5. Exit Menu\n");
        printf("Choice: ");
        scanf("%d", &num);

        switch (num) {
            case 1:
                display();
                pause();
                system("cls");
                break;

            case 2: {
                float last = peek();
                if (last != -1){
                    printf("Last element is: %f\n", last);
                }
                pause();
                system("cls");
                break;
            }

            case 3:
                push();
                pause();
                system("cls");
                break;

            case 4: {
                float last = pop();
                if (last != -1){
                    printf("Element popped: %f\n", last);
                }
                pause();
                system("cls");
                break;
            }

            case 5:
                flag = 1;
                break;

            default:
                printf("Invalid choice entered\n");
                pause();
                system("cls");
        }
    }
    return 0;
    system("cls");
}
