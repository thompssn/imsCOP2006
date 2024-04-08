#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// structure for inventory items
typedef struct {
    char name[50];
    int quantity;
    float price;
} Item;

void addItem(Item inventory[], int *numItems);
void displayInventory(Item inventory[], int numItems);
bool isValidPriceFormat(const char *input);

int main() {
    Item inventory[100];
    int numItems = 0;
    int choice;

    do {
        printf("Inventory Management System\n");
        printf("1. Add Item\n");
        printf("2. Display Inventory\n");
        printf("3. Exit\n");
        printf("Enter your choice:");

        // read choice
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear invalid input
            printf("Invalid.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addItem(inventory, &numItems);
                break;
            case 2:
                displayInventory(inventory, numItems);
                break;
            case 3:
                printf("Exiting.");
                break;
            default:
                printf("Invalid. Please enter 1, 2, or 3.\n");
        }
    } while (choice != 3);

    return 0;
}

// add item
void addItem(Item inventory[], int *numItems) {
    printf("Enter item name:");
    scanf("%s", inventory[*numItems].name);

    // read quantity
    while (true) {
        printf("Enter quantity:");
        if (scanf("%d", &inventory[*numItems].quantity) != 1) {
            while (getchar() != '\n'); // clear invalid input
            printf("Invalid quantity. Please enter an integer.\n");
        } else {
            break;
        }
    }

    // read price
    char priceInput[10];
    bool validPrice = false;
    do {
        printf("Enter price (in $X.XX format):");
        scanf("%s", priceInput);

        // check price format
        validPrice = isValidPriceFormat(priceInput);
        if (!validPrice) {
            printf("Invalid price. Please enter the price in $X.XX format.\n");
        } else {
            // convert string to float, +1 to ignore dollar sign
            inventory[*numItems].price = atof(priceInput + 1);
        }
    } while (!validPrice);

    (*numItems)++;
    printf("Item added.\n");
}

// display inventory
void displayInventory(Item inventory[], int numItems) {
    if (numItems == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("Inventory:\n");
    printf("%-20s %-10s %-10s\n", "Name", "Quantity", "Price");
    for (int i = 0; i < numItems; i++) {
        printf("%-20s %-10d $%-10.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

// valid price format function

bool isValidPriceFormat(const char *input) {

    // check for dollar sign
    if (input[0] != '$') {
        return false;
    }

    input++; // move past dollar sign

    // check digits before decimal point
    if (!isdigit(input[0])) {
        return false;
    }

    // check for decimal point
    while (isdigit(input[0])) {
        input++;
    }

    if (input[0] != '.') {
        return false;
    }


    input++; // move past decimal point

    // check for two digits after decimal point
    if (!isdigit(input[0]) || !isdigit(input[1])) {
        return false;
    }

    // make sure there are no extra characters at the end
    if (input[2] != '\0') {
        return false;
    }

    return true;
}