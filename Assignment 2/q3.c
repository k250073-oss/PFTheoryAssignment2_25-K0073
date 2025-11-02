#include <stdio.h>
#include <stdlib.h>
int flagg =0;

void pause(void) {
    int x;
    printf("\nPress ENTER to continue");
    while ((x = getchar()) != '\n' && x != EOF) { }
    getchar();
}

void Menu() {
    printf("\n~~~~~~~~~~~~~~~~IESCO POWER GRID MONITORING~~~~~~~~~~~~~~~~~~~\n");
    printf("\nEnter:\n");
    printf("\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n");
    printf("3. Run System Diagnostic\n");
    printf("4. Exit\n");
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Enter your choice: ");
}

void updateSector(int grid[3][3]) {
    int r, c, i, j;

    printf("\nEnter sector coordinates (row col), one at a time: ");
    scanf("%d %d", &r, &c);

    if (r < 0 || r >= 3 || c < 0 || c >= 3) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\nSelect status flag to modify:\n");
    printf("1. Power Status\n");
    printf("2. Overload Warning\n");
    printf("3. Maintenance Required\n");
    printf("Enter choice: ");
    scanf("%d", &i);

    printf("Enter action (1 = Set, 0 = Clear): ");
    scanf("%d", &j);

    int Bit;
    switch (i) {
        case 1: Bit = 1; 
            break;
        case 2: Bit = 2; 
            break;
        case 3: Bit = 4; 
            break;
        default:
            printf("Invalid flag choice!\n");
            return;
    }

    if (j == 1)
        grid[r][c] |= Bit;
    else
        grid[r][c] &= ~Bit;

    printf("\nSector (%d, %d) updated successfully\n", r, c);
}

void SectorStatus(int grid[3][3]) {
    int r, c;
    printf("\nEnter sector coordinates (row col), one at a time: ");
    scanf("%d %d", &r, &c);

    if (r < 0 || r >= 3 || c < 0 || c >= 3) {
        printf("Invalid coordinates!\n");
        return;
    }

    int status = grid[r][c];
    printf("\n Sector (%d, %d) Status Report \n", r, c);

    if (status & 1)
        printf("Power Status: ON\n");
    else
        printf("Power Status: OFF\n");

    if (status & 2)
        printf("Overload Warning: YES\n");
    else
        printf("Overload Warning: NO\n");

    if (status & 4)
        printf("Maintenance Required: YES\n");
    else
        printf("Maintenance Required: NO\n");

    printf("Encoded Value: %d\n", status);
}

void SystemDiagnostic(int grid[3][3]) {
    int ovrloadCnt = 0, maintenCount = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] & 2)
                ovrloadCnt++;
            if (grid[i][j] & 4)
                maintenCount++;
        }
    }

    printf("\nSYSTEM DIAGNOSTIC REPORT\n");
    printf("Total Overloaded Sectors: %d\n", ovrloadCnt);
    printf("Total Requiring Maintenance: %d\n", maintenCount);
    printf(".............................................\n");
}

int main() {
    int grid[3][3] = {0};
    int x;

    while (flagg == 0) {
        Menu();
        scanf("%d", &x);

        switch (x) {
            case 1:
                updateSector(grid);
                pause();
                system("cls");
                break;
            case 2:
                SectorStatus(grid);
                pause();
                system("cls");
                break;
            case 3:
                SystemDiagnostic(grid);
                pause();
                system("cls");
                break;
            case 4:
                printf("\nExiting system\n");
                flagg = 1;
                return 0;
            default:
                printf("Invalid choice entered, try again\n");
        }
    }

    return 0;
    system("cls");
}