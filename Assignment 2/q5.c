#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char text[100];
int mask = 0b00010010;
int flagg = 0;

void pause(void) {
    int x;
    printf("\nPress ENTER to continue");
    while ((x = getchar()) != '\n' && x != EOF) { }
    getchar();
}

void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[len - 1 - i];
        str[len - 1 - i] = str[i];
        str[i] = temp;
    }
}

void encode() {
    printf("\nEnter the text to be encoded\n");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    reverseString(text);

    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        text[i] ^= mask;
    }

    printf("\nEncoded text: %s\n", text);
}

void decode() {
    printf("\nEnter the text to be decoded\n");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    int len = strlen(text);

    for (int i = 0; i < len; i++) {
        text[i] ^= mask;
    }

    reverseString(text);

    printf("\nDecoded text: %s\n", text);
}

int main() {
    int x;
    printf("\n   TCS Secure Message System  \n");

    while (flagg == 0) {
        printf("\n1. Encode Message");
        printf("\n2. Decode Message");
        printf("\n3. Exit");
        printf("\nSelect: ");
        scanf("%d", &x);
        getchar();

        switch (x) {
            case 1:
                encode();
                pause();
                system("cls");
                break;
            case 2:
                decode();
                pause();
                system("cls");
                break;
            case 3:
                flagg = 1;
                break;
            default:
                printf("\nInvalid Selection\n");
                pause();
                system("cls");
        }
    }

    system("cls");
    return 0;
}
