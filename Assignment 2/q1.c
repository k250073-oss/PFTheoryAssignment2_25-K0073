#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int flagg =0;

char title[100][50] = {
    "Pirate of the carrabean",
    "Kill Bill Volum 2",
    "1984",
    "John Wick",
    "Shades of Gray",
    "Around the World",
    "Jurrasic World",
    "The Hobbit",
    "Thor Love n Thunder",
    "Mission Impossible"
};

int isbn[100] = {1001, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999, 1010};
int quantity[100] = {10, 5, 8, 3, 12, 6, 9, 7, 14, 15};
float price[100] = {499.99f, 299.50f, 199.75f, 250.00f, 150.25f, 320.00f, 275.50f, 400.75f, 600.00f, 350.40f};
int IX[100] = {1,2,3,4,5,6,7,8,9,10};

float bill = 0.0f;

void pause(void) {
    int x;
    printf("\nPress ENTER to continue");
    while ((x = getchar()) != '\n' && x != EOF) { }
    getchar();
}

int KhaliJaga(void) {
    for (int i = 0; i < 100; i++) {
        if (IX[i] == 0) return i;
    }
    return -1;
}

void AddNewBook() {
    int indexer = KhaliJaga();
    if (indexer == -1) {
        printf("Inventory Full\n");
        return;
    }

    int code;
    printf("Book Addition\n");
    printf("Enter ISBN: ");
    if (scanf("%d", &code) != 1) {
        printf("Invalid input.\n");

        while (getchar() != '\n') {}
        return;
    }

    for (int i = 0; i < 100; i++) {
        if (isbn[i] == code && IX[i] != 0) {
            printf("ISBN already in use. Book at corresponding ISBN is: %s\n", title[i]);
            return;
        }
    }

    while (getchar() != '\n' && getchar() != EOF) {                  };

    printf("Enter Book Name: ");
    if (fgets(title[indexer], sizeof(title[indexer]), stdin) == NULL) {
        title[indexer][0] = '\0';
    } else {
        title[indexer][strcspn(title[indexer], "\n")] = '\0';
    }

    printf("Enter Price: ");
    if (scanf("%f", &price[indexer]) != 1) {
        printf("Invalid price input.\n");

        while (getchar() != '\n') {}
        return;
    }

    printf("Enter Available Stock: ");
    if (scanf("%d", &quantity[indexer]) != 1) {
        printf("Invalid quantity input.\n");
        while (getchar() != '\n') {}
        return;
    }

    isbn[indexer] = code;
    IX[indexer] = indexer + 1;

    printf("Book Added Successfully at index %d\n", indexer);
}


void ProcessSale() {
    int code, qty;
    int found = 0;

    printf("Sales Processing\n");
    printf("Enter Book ISBN for Sales Entry: ");
    if (scanf("%d", &code) != 1) {
        printf("Invalid ISBN input.\n");
        while (getchar() != '\n') {}
        return;
    }

    for (int i = 0; i < 100; i++) {
        if (IX[i] != 0 && isbn[i] == code) {
            found = 1;
            printf("Book Name at Corresponding ISBN is: %s\n", title[i]);
            printf("Enter Purchase Quantity: ");
            if (scanf("%d", &qty) != 1) {
                printf("Invalid quantity.\n");
                while (getchar() != '\n') {}
                break;
            }
            if (qty <= 0) {
                printf("Quantity must be positive.\n");
                break;
            }
            if (quantity[i] - qty < 0) {
                printf("Quantity Not Available or Book Already Out of Stock\n");
            } else {
                quantity[i] -= qty;
                bill += price[i] * qty;
                printf("Purchase Success\n");
                printf("Your Current Total Bill is: %.2f\n", bill);
            }
            break;
        }
    }

    if (!found) {
        printf("Invalid ISBN entered or book not found.\n");
    }
}


void StockReport() {
    int flag = 0;
    printf("Stock Reports\n");
    printf("Book Stocks Below 5 are:\n");
    for (int i = 0; i < 100; i++) {
        if (IX[i] != 0 && quantity[i] < 5) {
            flag = 1;
            printf("\nBook Name: %s\n", title[i]);
            printf("ISBN: %d\n", isbn[i]);
            printf("Quantity Remaining: %d\n", quantity[i]);
        }
    }
    if (!flag) {
        printf("\nNo books with stock below 5.\n");
    }
}

void DisplayInventory() {
    printf("%-6s %-30s %-12s %-10s %-10s\n", "IX", "Book Names", "Book ISBN", "Quantity", "Price");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for (int i = 0; i < 100; i++) {
        if (IX[i] != 0) {
            printf("%-6d %-30s %-12d %-10d %-10.2f\n",
                   IX[i], title[i], isbn[i], quantity[i], price[i]);
        }
    }
}

void EditInventory() {
    int mode;
    printf("Inventory Modification\n");
    printf("Use Book ISBN or Index Position to Modify the Records\n");
    printf("Press 0 for ISBN and 1 for IX Position: ");
    if (scanf("%d", &mode) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n') {}
        return;
    }

    if (mode == 0) {
        int code;
        printf("Enter ISBN: ");
        if (scanf("%d", &code) != 1) {
            printf("Invalid ISBN.\n");
            while (getchar() != '\n') {}
            return;
        }
        int found = 0;
        for (int i = 0; i < 100; i++) {
            if (IX[i] != 0 && isbn[i] == code) {
                found = 1;
                int y;
                printf("Enter the corresponding digit to change:\n");
                printf("1. Book Name\n2. ISBN\n3. Quantity\n4. Price\n5. Indexing (set to 0 to make empty)\n");
                if (scanf("%d", &y) != 1) {
                    printf("Invalid choice.\n");
                    while (getchar() != '\n') {}
                    break;
                }
                while (getchar() != '\n') {}

                if (y == 1) {
                    char new[50];
                    printf("Enter new book title: ");
                    if (fgets(new, sizeof(new), stdin) == NULL) new[0] = '\0';
                    new[strcspn(new, "\n")] = '\0';
                    strcpy(title[i], new);
                } else if (y == 2) {
                    int newIsbn;
                    printf("Enter new ISBN: ");
                    if (scanf("%d", &newIsbn) == 1) {
                        isbn[i] = newIsbn;
                    } else {
                        printf("Invalid ISBN input.\n");
                        while (getchar() != '\n') {}
                    }
                } else if (y == 3) {
                    int newQty;
                    printf("Enter new Quantity: ");
                    if (scanf("%d", &newQty) == 1) {
                        quantity[i] = newQty;
                    } else {
                        printf("Invalid quantity.\n");
                        while (getchar() != '\n') {}
                    }
                } else if (y == 4) {
                    float newPrice;
                    printf("Enter new price: ");
                    if (scanf("%f", &newPrice) == 1) {
                        price[i] = newPrice;
                    } else {
                        printf("Invalid price.\n");
                        while (getchar() != '\n') {}
                    }
                } else if (y == 5) {
                    int newIx;
                    printf("Enter new Index Number (enter 0 to mark empty): ");
                    if (scanf("%d", &newIx) == 1) {
                        if (newIx == 0) {
                            
                            IX[i] = 0;
                            isbn[i] = 0;
                            quantity[i] = 0;
                            price[i] = 0.0f;
                            title[i][0] = '\0';
                        } else {
                            IX[i] = newIx;
                        }
                    } else {
                        printf("Invalid index input.\n");
                        while (getchar() != '\n') {}
                    }
                } else {
                    printf("Invalid option.\n");
                }
                break;
            }
        }
        if (!found) {
            printf("ISBN not found.\n");
        }
    } else if (mode == 1) {
        int code;
        printf("Enter Index Position: ");
        if (scanf("%d", &code) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n') {}
            return;
        }
        int found = 0;
        for (int i = 0; i < 100; i++) {
            if (IX[i] == code) {
                found = 1;
                int y;
                printf("Enter the corresponding digit to change:\n");
                printf("1. Book Name\n2. ISBN\n3. Quantity\n4. Price\n5. Indexing (set to 0 to make empty)\n");
                if (scanf("%d", &y) != 1) {
                    printf("Invalid choice.\n");
                    while (getchar() != '\n') {}
                    break;
                }
                while (getchar() != '\n') {}

                if (y == 1) {
                    char new[50];
                    printf("Enter new book title: ");
                    if (fgets(new, sizeof(new), stdin) == NULL) new[0] = '\0';
                    new[strcspn(new, "\n")] = '\0';
                    strcpy(title[i], new);
                } else if (y == 2) {
                    int newIsbn;
                    printf("Enter new ISBN: ");
                    if (scanf("%d", &newIsbn) == 1) {
                        isbn[i] = newIsbn;
                    } else {
                        printf("Invalid ISBN input.\n");
                        while (getchar() != '\n') {}
                    }
                } else if (y == 3) {
                    int newQty;
                    printf("Enter new Quantity: ");
                    if (scanf("%d", &newQty) == 1) {
                        quantity[i] = newQty;
                    } else {
                        printf("Invalid quantity.\n");
                        while (getchar() != '\n') {}
                    }
                } else if (y == 4) {
                    float newPrice;
                    printf("Enter new price: ");
                    if (scanf("%f", &newPrice) == 1) {
                        price[i] = newPrice;
                    } else {
                        printf("Invalid price.\n");
                        while (getchar() != '\n') {}
                    }
                } else if (y == 5) {
                    int newIx;
                    printf("Enter new Index Number (enter 0 to mark empty): ");
                    if (scanf("%d", &newIx) == 1) {
                        if (newIx == 0) {
                            IX[i] = 0;
                            isbn[i] = 0;
                            quantity[i] = 0;
                            price[i] = 0.0f;
                            title[i][0] = '\0';
                        } else {
                            IX[i] = newIx;
                        }
                    } else {
                        printf("Invalid index input.\n");
                        while (getchar() != '\n') {}
                    }
                } else {
                    printf("Invalid option.\n");
                }
                break;
            }
        }
        if (!found) {
            printf("Index position not found.\n");
        }
    } else {
        printf("Invalid mode selected.\n");
    }
}

int main(void) {

    for (int i = 10; i < 100; i++) {
        IX[i] = 0;
        isbn[i] = 0;
        quantity[i] = 0;
        price[i] = 0.0f;
        title[i][0] = '\0';
    }

    while (flagg ==0) {
        int choice;

        printf("==== Bookstore Management System ====\n");
        printf("1. Add New Book\n");
        printf("2. Process Sale\n");
        printf("3. Low Stock Report\n");
        printf("4. View Inventory\n");
        printf("5. Edit Inventory\n");
        printf("0. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice (0-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n') {}
            continue;
        }
        while (getchar() != '\n' && getchar() != EOF) { }

        switch (choice) {
            case 1:
                AddNewBook();
                pause();
                system("cls");
                break;
            case 2:
                DisplayInventory();
                ProcessSale();
                pause();
                system("cls");
                break;
            case 3:
                StockReport();
                pause();
                system("cls");
                break;
            case 4:
                DisplayInventory();
                pause();
                system("cls");
                break;
            case 5:
                DisplayInventory();
                EditInventory();
                pause();
                system("cls");
                break;
            case 0:
                printf("Exiting\n");
                flagg = 1;
                return 0;
            default:
                printf("\nInvalid choice! Please enter a number between 0 and 5.\n");
                pause();
                system("cls");
        }
    }
    return 0;
}
