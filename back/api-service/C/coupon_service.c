#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../coupon_service.h"

// Check if the coupon is expired
int is_coupon_expired(const char* expiryDate) {
    struct tm couponTime = {0};
    time_t currentTime;
    time(&currentTime);

    // Parse expiry date string in the format YYYY-MM-DD
    sscanf(expiryDate, "%d-%d-%d", &couponTime.tm_year, &couponTime.tm_mon, &couponTime.tm_mday);
    couponTime.tm_year -= 1900; // Adjust year
    couponTime.tm_mon -= 1;     // Adjust month

    time_t couponExpiryTime = mktime(&couponTime);
    return difftime(currentTime, couponExpiryTime) > 0; // Expired if currentTime > couponExpiryTime
}

// Apply discount based on coupon
double apply_coupon_discount_csv(const char* couponCsvPath, const char* couponCode, double totalPrice) {
    FILE *file = fopen(couponCsvPath, "r");
    if (!file) {
        printf("Error opening coupon file.\n");
        return totalPrice; // No discount applied
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char code[10];
        int percent, amount;
        char expiryDate[20];
        char status[10];
        sscanf(line, "%[^,],%d,%d,%[^,],%s", code, &percent, &amount, expiryDate, status);

        if (strcmp(code, couponCode) == 0 && strcmp(status, "active") == 0) {
            if (!is_coupon_expired(expiryDate)) {
                if (totalPrice >= amount) {
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
            } else {
                printf("Coupon %s is expired.\n", couponCode);
            }
        }
    }

    printf("Coupon not found or invalid.\n");
    fclose(file);
    return totalPrice; // No discount applied
}
