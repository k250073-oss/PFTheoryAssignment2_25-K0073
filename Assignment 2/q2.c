#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int flagg =0; 

int productCode[10] = {110,111,112,113,114,115,116,117,118,119};
int quantityInStock[10] = {50, 10, 20, 8, 100, 3, 34, 21, 19, 2};
float pricePerProduct[10] = {100, 200, 300, 150, 12, 150, 100, 230, 130, 60};

char customerName[10][50];
char customerCNIC[10][20];
int customerID[10];
int Count = 0;
int curCustomer = -1;

int cartCode[10];
int cartQuantity[10];
int cartCount = 0;
float totalBill = 0;
float disBill = 0;
int disApplied = 0;

void pause(void) {
    int x;
    printf("\nPress ENTER to continue");
    while ((x = getchar()) != '\n' && x != EOF) { }
    getchar();
}


void regCustomer() {
    if (Count >= 10) {
        printf("\nCustomer limit reached!\n");
        return;
    }

    printf("\nEnter Customer Name: ");
    getchar();
    fgets(customerName[Count], sizeof(customerName[Count]), stdin);
    customerName[Count][strcspn(customerName[Count], "\n")] = '\0';

    printf("Enter Customer CNIC: ");
    fgets(customerCNIC[Count], sizeof(customerCNIC[Count]), stdin);
    customerCNIC[Count][strcspn(customerCNIC[Count], "\n")] = '\0';

    customerID[Count] = 1392 + Count;
    printf("\nYour Customer ID is: %d\n", customerID[Count]);

    curCustomer = Count;
    Count++;

    printf("Customer Registered succesfully\n");
}

int findID(int id) {
    for (int i = 0; i < Count; i++) {
        if (customerID[i] == id)
            return i;
    }
    return -1;
}

void checkRegisterCustomer() {
    char x;
    printf("\nDo you already have a Customer ID? \nPress y for YES and n for NO: ");
    getchar(); 
    scanf("%c", &x);

    if (x == 'y' || x == 'Y') {
        int id;
        printf("Enter your Customer ID: ");
        scanf("%d", &id);

        int ix = findID(id);
        if (ix != -1) {
            curCustomer = ix;
            printf("\nWelcome back, %s!\n", customerName[ix]);
        } else {
            printf("\nCustomer ID not found. Please register.\n");
            regCustomer();
        }
    } else {
        regCustomer();
    }
}


void displayInventory() {
    printf("\n----------------- INVENTORY -----------------\n");
    printf("%-15s %-20s %-15s\n", "Product Code", "Quantity in Stock", "Price");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < 10; i++) {
        printf("%-15d %-20d %-15.2f\n", productCode[i], quantityInStock[i], pricePerProduct[i]);
    }
}

void updateInventory(int code, int qty) {
    for (int i = 0; i < 10; i++) {
        if (productCode[i] == code) {
            if (quantityInStock[i] >= qty) {
                quantityInStock[i] -= qty;
            } else {
                printf("\nStock not available or Item out of Stock\n");
            }
            break;
        }
    }
}

void addCart() {
    int code, qty;
    displayInventory();
    printf("\nEnter Product Code to add to cart= ");
    scanf("%d", &code);
    printf("Enter Quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i <10; i++) {
        if (productCode[i] == code) {
            if (quantityInStock[i] >= qty) {
                cartCode[cartCount] = code;
                cartQuantity[cartCount] = qty;
                cartCount++;
                totalBill += pricePerProduct[i] * qty;
                updateInventory(code, qty);
                printf("\nItem addd to cart successfully\n");
            } else {
                printf("\nInsufficient stock\n");
            }
            return;
        }
    }

    printf("\nInvalid Productt Code\n");
}


void applyPromoCode() {
    char x, code[20];
    printf("\nDo you have a promo code? (y/n): ");
    getchar();
    scanf("%c", &x);

    if (x == 'y' || x == 'Y') {
        printf("Enter promo code: ");
        getchar();
        fgets(code, sizeof(code), stdin);
        code[strcspn(code, "\n")] = '\0';

        if (strcmp(code, "Eid2025") == 0) {
            disBill = totalBill * 0.75;
            disApplied = 1;
            printf("\nPromo code applied, 25%% discount granted\n");
        } else {
            printf("\nInvalid promo code. No discount applied.\n");
            disBill = totalBill;
        }
    } else {
        disBill = totalBill;
    }
}

void displayTotalBill() {
    if (cartCount == 0) {
        printf("\nCar empty. Add some items first\n");
        return;
    }

    printf("\nTotal Bill without discount: %.2f\n", totalBill);
    applyPromoCode();
    printf("Total Bill with discount if applied: %.2f\n", disBill);
}


void showInvoice() {
    if (curCustomer == -1) {
        printf("\nNo customer data found. Please register first.\n");
        return;
    }

    if (cartCount == 0) {
        printf("\nCart is empty\n");
        return;
    }

    printf("\n~~~~~~~~~~~~~~~~~~~~ Inovoice ~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Customer Name: %s\n", customerName[curCustomer]);
    printf("CNIC: %s\n", customerCNIC[curCustomer]);
    printf("Customer ID: %d\n", customerID[curCustomer]);
    printf("---------------------------------------------\n");
    printf("%-15s %-15s %-15s\n", "Product Code", "Quantity", "Price");
    printf("---------------------------------------------\n");

    for (int i = 0; i < cartCount; i++) {
        int code = cartCode[i];
        for (int j = 0; j <10; j++) {
            if (productCode[j] == code) {
                printf("%-15d %-15d %-15.2f\n", code, cartQuantity[i], pricePerProduct[j]);
            }
        }
    }

    printf("---------------------------------------------\n");
    printf("Bill without discount: %.2f\n", totalBill);

    if (disApplied)
        printf("Bill after 25%% discount: %.2f\n", disBill);
    else
        printf("No discount applied.\n");

    printf("---------------------------------------------\n");
}

int main() {
    int x;

    while (flagg == 0) {
        printf("\n~~~~~~~~~~~ SUPERMARKET MANAGEMENT SYSTEM ~~~~~~~~~~~~~~~\n");
        
        printf("1. Enter / Check Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf(".........................................................\n");
        printf("Enter your choice: ");
        scanf("%d", &x);

        switch (x) {
            case 1:
                checkRegisterCustomer();
                pause();
                system("cls");
            
                break;
            case 2:
                displayInventory();
                pause();
                system("cls");
                break;
            case 3:
                if (curCustomer == -1) {
                    printf("\nPlease enter or verify customer details first\n");
                } else {
                    addCart();
                }
                pause();
                system("cls");
                break;
            case 4:
                displayTotalBill();
                pause();
                system("cls");
                break;
            case 5:
                showInvoice();
                pause();
                system("cls");
                break;
            case 6:
                printf("\nThank you for visiting Us\n");
                flagg = 1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
    system("cls");
}
