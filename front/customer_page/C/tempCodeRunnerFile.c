#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../order_page.h"

#define MAX_PRODUCTS 100
#define MAX_COUPONS 5  // Maximum number of coupons

// Function to simulate retrieving a list of available coupons
void printCoupons() {
    printf("Coupon available: PAMLORTAE - 5%% off\n");
}

// Function to apply a coupon discount
double applyCouponDiscount(double totalPrice, int couponIndex) {
    double discount = 0.0;
    if (couponIndex == 1) {
        discount = 0.05;  // 5% discount
    }
    return totalPrice * (1 - discount);
}

// Function to process a single order
int process_order(GOODS* products, int itemCount, double* finalTotalPrice) {
    char goodsName[100];
    int quantity = 0;
    double orderTotalPrice = 0.0;
    
    // Step 1: Product Selection
    printf("Enter Goods name: ");
    scanf("%99s", goodsName);
    
    // Step 2: Find Product
    GOODS* foundProduct = NULL;
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
    
    // Step 3: Detailed Product Display
    printGOODS(foundProduct);
    printf("------------------------\n");
    
    // Step 4: Quantity Validation with Robust Input Checking
    do {
        printf("Enter the quantity you want to order (1-%d): ", foundProduct->quantity);
        
        // Clear any previous input errors
        if (scanf("%d", &quantity) != 1) {
            printf("Invalid input. Please enter a numeric value.\n");
            while (getchar() != '\n'); // Clear input buffer
            quantity = 0;
            continue;
        }
        
        // Check quantity bounds
        if (quantity <= 0) {
            printf("Quantity must be positive.\n");
            continue;
        }
        
        if (quantity > foundProduct->quantity) {
            printf("Requested quantity exceeds available stock.\n");
            continue;
        }
        
        break; // Valid input
    } while (1);
    
    // Step 5: Price Calculation
    orderTotalPrice = foundProduct->price * quantity;
    printf("Total price for %d %s(s): %.2lf baht\n", quantity, foundProduct->name, orderTotalPrice);
    
    // Add to the final total price
    *finalTotalPrice += orderTotalPrice;
    
    // Step 6: Coupon Display
    printCoupons();
    
    // Step 7: Return whether user wants to order more
    return 1; // This assumes the user will always want to order more unless they specify to stop.
}

// Function to process the entire order page
void Order_Page(void) {
    int itemCount;
    GOODS *products = getGOODSCSVpath("back/user/1/inventory.csv", &itemCount);
    if (products == NULL) {
        printf("Error loading products from inventory.\n");
        return;
    }

    double finalTotalPrice = 0.0;
    char continueOrdering;
    
    // Process multiple orders
    do {
        int orderSuccess = process_order(products, itemCount, &finalTotalPrice);
        if (!orderSuccess) {
            break;  // Stop ordering if process fails
        }
        
        // Ask to continue ordering
        printf("Do you want to order more products? (Y/N): ");
        scanf(" %c", &continueOrdering);
        
    } while (continueOrdering == 'Y' || continueOrdering == 'y');  // If 'Y' or 'y', continue ordering

    // Final order summary
    printf("\nFinal total price for all products: %.2lf baht\n", finalTotalPrice);

    // Step 8: Coupon selection based on total price
    if (finalTotalPrice > 0) {
        printf("Available coupons based on your total price:\n");
        printf("1. Coupon: PAMLORTAE\n");
        
        int couponChoice = 0;
        printf("Choose a coupon to apply (1-1): ");
        scanf("%d", &couponChoice);

        if (couponChoice == 1) {
            finalTotalPrice = applyCouponDiscount(finalTotalPrice, couponChoice);
            printf("Total price after coupon discount: %.2lf baht\n", finalTotalPrice);
        }
    }

    // Final message
    printf("Thank you for your order!\n");
}
