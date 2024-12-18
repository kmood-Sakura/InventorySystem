#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../order_page.h"
#include <time.h>

#define MAX_PRODUCTS 100
#define MAX_COUPONS 10
#define GOAL_PRICE 50.0

// Function prototypes
int is_coupon_expired(const char *expiryDate);
void update_inventory_csv(const char *filename, GOODS *products, int itemCount);
void update_coupon_csv(const char *filename, const char *usedCoupon);

// Function to check available coupons
int check_available_coupons(double totalPrice, char availableCoupons[MAX_COUPONS][100], int *couponCount) {
    *couponCount = 0;
    FILE *file = fopen("back/user/1/coupon.csv", "r");
    if (!file) {
        printf("Error opening coupon file.\n");
        return 0;
    }

    char line[200];
    double totalPricePercentage = (totalPrice / GOAL_PRICE) * 100;
    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file) && *couponCount < MAX_COUPONS) {
        char code[20], expiryDate[20], status[10];
        int percent, amount;

        sscanf(line, "%[^,],%d,%d,%[^,],%s", code, &percent, &amount, status, expiryDate);

        if (strcmp(status, "active") == 0 && !is_coupon_expired(expiryDate) && totalPricePercentage >= percent) {
            printf("Coupon available: %s - %d%% off\n", code, percent);
            strcpy(availableCoupons[*couponCount], code);
            (*couponCount)++;
        }
    }

    fclose(file);
    return *couponCount > 0;
}

// Function to process a single order
int process_order(GOODS *products, int itemCount, double *grandTotal) {
    char goodsName[100];
    int quantity = 0;

    // Step 1: Product Selection
    printf("Enter Goods name: ");
    scanf("%99s", goodsName);

    // Step 2: Find Product
    GOODS *foundProduct = NULL;
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(products[i].name, goodsName) == 0) {
            foundProduct = &products[i];
            break;
        }
    }

    if (!foundProduct) {
        printf("Product not found.\n");
        return 0;
    }

    // Step 3: Display Product Details
    printf("ID: %s\n", foundProduct->id);
    printf("Name: %s\n", foundProduct->name);
    printf("Description: %s\n", foundProduct->description);
    printf("Price: %.2f\n", foundProduct->price);
    printf("Quantity: %d\n", foundProduct->quantity);
    printf("------------------------\n");

    // Step 4: Quantity Validation
    do {
        printf("Enter the quantity you want to order (1-%d): ", foundProduct->quantity);
        if (scanf("%d", &quantity) != 1 || quantity <= 0 || quantity > foundProduct->quantity) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    } while (1);

    // Step 5: Price Calculation
    double totalPrice = foundProduct->price * quantity;
    printf("Total price for %d %s(s): %.2lf baht\n", quantity, foundProduct->name, totalPrice);

    // Step 6: Update Inventory
    foundProduct->quantity -= quantity;

    // Step 7: Confirm Order
    char confirmation;
    printf("Confirm order? (Y/N): ");
    while (1) {
        scanf(" %c", &confirmation);
        if (confirmation == 'Y' || confirmation == 'y') {
            *grandTotal += totalPrice;
            printf("Order confirmed.\n");
            return 1;
        } else if (confirmation == 'N' || confirmation == 'n') {
            printf("Order canceled.\n");
            return 0;
        } else {
            printf("Invalid input. Please enter Y or N: ");
        }
    }
}

// Update inventory CSV file
void update_inventory_csv(const char *filename, GOODS *products, int itemCount) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening inventory file for writing.\n");
        return;
    }

    fprintf(file, "id,name,description,price,quantity\n");
    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%s,%s,%s,%.2f,%d\n",
                products[i].id, products[i].name, products[i].description,
                products[i].price, products[i].quantity);
    }

    fclose(file);
}

// Update coupon status to "used" in the CSV
void update_coupon_csv(const char *filename, const char *usedCoupon) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening coupon file for updating.\n");
        return;
    }

    char tempFilename[] = "temp_coupon.csv";
    FILE *tempFile = fopen(tempFilename, "w");

    char line[200];
    fprintf(tempFile, "code,percent,amount,status,expiry_date\n"); // Rewrite header
    fgets(line, sizeof(line), file); // Skip original header

    while (fgets(line, sizeof(line), file)) {
        char code[20], status[10], expiryDate[20];
        int percent, amount;

        sscanf(line, "%[^,],%d,%d,%[^,],%s", code, &percent, &amount, status, expiryDate);

        if (strcmp(code, usedCoupon) == 0) {
            amount--; // Decrement amount
            if (amount <= 0) {
                // If amount is zero, set status to expired
                amount = 0;
                fprintf(tempFile, "%s,%d,%d,%s,%s\n", code, percent, amount, "expired", expiryDate);
            } else {
                fprintf(tempFile, "%s,%d,%d,%s,%s\n", code, percent, amount, status, expiryDate);
            }
        } else {
            fprintf(tempFile, "%s", line); // Write the line unchanged
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(filename);
    rename(tempFilename, filename);
}

// Main order page function
void Order_Page(AUTH *auth) {
    int itemCount;
    char inventory_path[MAX_MY_PATH];
    snprintf(inventory_path, MAX_MY_PATH, "%s%s%s.%s","back/user/", "1", "/inventory","csv");
    char coupon_path[MAX_MY_PATH];
    snprintf(inventory_path, MAX_MY_PATH, "%s%s%s.%s","back/user/", "1", "/coupon","csv");

    GOODS *products = getGOODSCSVpath(inventory_path, &itemCount);
    if (products == NULL) {
        printf("Error loading products from inventory.\n");
        return;
    }

    double grandTotal = 0.0;
    char availableCoupons[MAX_COUPONS][100];
    int couponCount = 0;

    char continueOrdering;
    do {
        process_order(products, itemCount, &grandTotal);
        printf("Do you want to order more products? (Y/N): ");
        scanf(" %c", &continueOrdering);
    } while (continueOrdering == 'Y' || continueOrdering == 'y');

    printf("Final total price: %.2lf baht\n", grandTotal);

    // Recheck coupons
    if (check_available_coupons(grandTotal, availableCoupons, &couponCount)) {
        printf("Available coupons:\n");
        for (int i = 0; i < couponCount; i++) {
            printf("%d. %s\n", i + 1, availableCoupons[i]);
        }

        int choice;
        printf("Choose a coupon to apply (1-%d) or (0-skip): ", couponCount);
        scanf("%d", &choice);

        if (choice > 0 && choice <= couponCount) {
            grandTotal = apply_coupon_discount_csv(coupon_path, availableCoupons[choice - 1], grandTotal);
            update_coupon_csv(coupon_path, availableCoupons[choice - 1]);
            printf("Total price after discount: %.2lf baht\n", grandTotal);
        }
    }

    update_inventory_csv(inventory_path, products, itemCount);
    printf("Thank you for your order!\n");
}