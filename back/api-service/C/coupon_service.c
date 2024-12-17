#include <stdio.h>
#include <string.h>
#include "../coupon_service.h"

// Apply discount based on coupon
int apply_coupon_discount_csv(const char* couponCsvPath, const char* couponCode, double totalPrice) {
    FILE *file = fopen(couponCsvPath, "r");
    if (!file) {
        printf("Error opening coupon file.\n");
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char code[10];
        int percent, amount;
        char status[10];
        sscanf(line, "%[^,],%d,%d,%s", code, &percent, &amount, status);

        if (strcmp(code, couponCode) == 0 && strcmp(status, "active") == 0) {
            if (totalPrice >= percent) {
                double discount = totalPrice * (percent / 100.0);
                double finalPrice = totalPrice - discount;
                printf("Coupon %s applied: %.2f baht off\n", couponCode, discount);
                fclose(file);
                return finalPrice;
            } else {
                printf("Coupon %s is not valid for this total price.\n", couponCode);
                fclose(file);
                return totalPrice;
            }
        }
    }

    printf("Coupon not found or expired.\n");
    fclose(file);
    return totalPrice;  // No discount applied
}
