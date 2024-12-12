#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../order_page.h"

#define MAX_PRODUCTS 100

int ConfirmOrder(int quantity, const char* goodsName);

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

    while (1) {
        char goodsName[100];
        int quantity;

        // Prompt user for the product name
        printf("Enter Goods name: ");
        scanf("%s", goodsName);

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

            // Prompt for coupon code
            char couponCode[10];
            printf("Enter coupon code (or press Enter to skip): ");
            while (getchar() != '\n'); // Clear leftover newline from previous input
            fgets(couponCode, sizeof(couponCode), stdin);
            couponCode[strcspn(couponCode, "\n")] = '\0'; // Remove newline character

            // Apply discount and update coupon CSV if valid
            totalPrice = apply_coupon_discount_csv("back/user/1/coupon.csv", couponCode, totalPrice);
            printf("Total price after discount: %.2lf baht\n", totalPrice);

            grandTotal += totalPrice; // Add to grand total

            // Confirm the order
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
                return; // Exit the ordering process
            } else {
                printf("Invalid input. Please enter Y or N: ");
            }
        }
    }
}

// Confirm order (using your provided function)
int ConfirmOrder(int quantity, const char* goodsName) {
    char confirmation;
    printf("Confirm order for %d %s(s)? (Y/N): ", quantity, goodsName);
    while (1) {
        scanf(" %c", &confirmation);
        if (confirmation == 'Y' || confirmation == 'y') {
            return 1; // Order confirmed
        } else if (confirmation == 'N' || confirmation == 'n') {
            return 0; // Order canceled
        } else {
            printf("Invalid input. Please enter Y or N: ");
        }
    }
}
