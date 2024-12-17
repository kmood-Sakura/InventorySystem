#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../order_page.h"

#define MAX_PRODUCTS 100

int ConfirmOrder(int quan, const char* goodsName) {
    printf("[DEBUG] Inside ConfirmOrder - Quantity: %d\n", quan); // Add this line
    char confirmation;
    printf("You are about to order %d %s(s). Do you confirm this order? (Y/N): ", quan, goodsName);
    while (1) {
        scanf(" %c", &confirmation); // The space before %c is to skip any leftover newline characters
        if (confirmation == 'Y' || confirmation == 'y') {
            return 1;  // Confirmed
        } else if (confirmation == 'N' || confirmation == 'n') {
            return 0;  // Canceled
        } else {
            printf("Invalid input. Please enter Y or N: ");
        }
    }
}

void Order_Page(void) {
    printf("customer_Order\n");

    // Get all products from CSV using the existing function
    int itemCount;
    GOODS *products = getGOODSCSVpath("back/user/1/inventory.csv", &itemCount);
    if (products == NULL) {
        printf("Error loading products from inventory.\n");
        return;
    }

    double grandTotal = 0.0; // Variable to store the total price of all products ordered
    char availableCoupons[10][100]; // Store available coupon codes
    int couponCount = 0; // Store count of available coupons

    while (1) {
        char goodsName[100];
        int quantity;

        // Prompt user for the product name
        printf("Enter Goods name: ");
        scanf("%99s", goodsName);

        // Search for the product in the inventory
        GOODS* foundProduct = NULL;
        for (int i = 0; i < itemCount; i++) {
            if (strcmp(products[i].name, goodsName) == 0) {
                foundProduct = &products[i];
                break;
            }
        }

        if (foundProduct) {
            // Display product details
            printGOODS(foundProduct);

            // Get a valid quantity input
            printf("Enter the quantity you want to order: ");
            while (scanf("%d", &quantity) != 1 || quantity <= 0 || quantity > foundProduct->quantity) {
                printf("Invalid input. Please enter a valid quantity (1-%d): ", foundProduct->quantity);
                while (getchar() != '\n'); // Clear input buffer
            }

            double totalPrice = foundProduct->price * quantity;
            printf("Total price for %d %s(s): %.2lf baht\n", quantity, foundProduct->name, totalPrice);
            printf("quantity: %d\n",quantity);
            // Add available coupons to the list
            FILE *file = fopen("back/user/1/coupon.csv", "r");
            if (file) {
                char line[100];
                while (fgets(line, sizeof(line), file)) {
                    char code[10];
                    int percent, amount;
                    char status[10];
                    sscanf(line, "%[^,],%d,%d,%s", code, &percent, &amount, status);

                    if (strcmp(status, "active") == 0 && totalPrice >= percent) {
                        printf("Coupon available: %s - %d%% off\n", code, percent);
                        strcpy(availableCoupons[couponCount], code);
                        couponCount++;
                    }
                }
                fclose(file);
            }

            // Confirm the order
            printf("quantity: %d\n",quantity);
            if (ConfirmOrder(quantity, goodsName)) {
                printf("Order confirmed for %d %s(s) for %.2f baht\n", quantity, goodsName, totalPrice);

                // Update inventory
                int updated = update_item_quantity("back/user/1/", "inventory", foundProduct->id, -quantity);
                if (updated) {
                    printf("Inventory updated. The new quantity of %s is now %d.\n", foundProduct->name, foundProduct->quantity - quantity);
                } else {
                    printf("Failed to update inventory.\n");
                }
            } else {
                printf("Order canceled.\n");
            }
        } else {
            printf("Product not found.\n");
        }

        // Ask if the user wants to order more
        char more;
        printf("Do you want to order more products? (Y/N): ");
        while (1) {
            scanf(" %c", &more);
            if (more == 'Y' || more == 'y') {
                break; // Continue ordering
            } else if (more == 'N' || more == 'n') {
                printf("Final total price for all products: %.2lf baht\n", grandTotal);
                printf("Thank you for your order!\n");

                if (couponCount > 0) {
                    printf("Available coupons based on your total price:\n");
                    for (int i = 0; i < couponCount; i++) {
                        printf("%d. Coupon: %s\n", i + 1, availableCoupons[i]);
                    }

                    // Choose coupon to apply
                    int choice;
                    printf("Choose a coupon to apply (1-%d): ", couponCount);
                    scanf("%d", &choice);
                    if (choice > 0 && choice <= couponCount) {
                        double finalPrice = apply_coupon_discount_csv("back/user/1/coupon.csv", availableCoupons[choice - 1], grandTotal);
                        printf("Total price after coupon discount: %.2lf baht\n", finalPrice);
                    }
                }
                return; // Exit the ordering process
            } else {
                printf("Invalid input. Please enter Y or N: ");
            }
        }
    }
}