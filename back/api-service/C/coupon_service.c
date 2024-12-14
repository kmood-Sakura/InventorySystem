#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double apply_coupon_discount_csv(const char* filepath, const char* coupon_code, double total_price) {
    if (coupon_code == NULL || strlen(coupon_code) == 0) {
        return total_price; // No coupon provided
    }

    FILE *file = fopen(filepath, "r+");
    if (file == NULL) {
        printf("Error opening coupon file.\n");
        return total_price; // Return the original price if file operation fails
    }

    char line[100];
    char *temp_filepath = "temp_coupon.csv";
    FILE *temp = fopen(temp_filepath, "w");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return total_price;
    }

    int updated = 0;
    fgets(line, sizeof(line), file); // Copy header
    fputs(line, temp);

    while (fgets(line, sizeof(line), file) != NULL) {
        char code[10];
        int percent, amount;
        char status[10]; // Add status field

        // Read code, percent, amount, and status from CSV
        sscanf(line, "%[^,],%d,%d,%s", code, &percent, &amount, status);

        // Check if coupon is found and handle amount
        if (strcmp(code, coupon_code) == 0) {
            if (amount > 0) {
                total_price *= (1 - (percent / 100.0)); // Apply discount
                amount--; // Decrease coupon amount
                updated = 1;
            } else {
                // Mark as expired if amount is 0
                strcpy(status, "expired");
            }
        }

        // Write the updated coupon information to the temporary file
        fprintf(temp, "%s,%d,%d,%s\n", code, percent, amount, status);
    }

    fclose(file);
    fclose(temp);

    // Replace the old coupon file with the updated file
    remove(filepath);
    rename(temp_filepath, filepath);

    if (!updated) {
        printf("Invalid or expired coupon code.\n");
    }

    return total_price;
}
