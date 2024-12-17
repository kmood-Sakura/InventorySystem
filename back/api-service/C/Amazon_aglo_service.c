#include "Amazon_aglo_service.h"
#include <stdio.h>
#include <stdlib.h>

void process_inventory(const char *inventory_file, const char *output_file) {
    FILE *file = fopen(inventory_file, "r");
    if (file == NULL) {
        printf("Error: Cannot open inventory file %s\n", inventory_file);
        return;
    }

    char item_name[100];
    int current_stock, max_capacity, units_sold;

    printf("Processing inventory data...\n");

    while (fscanf(file, "%[^,],%d,%d,%d\n", item_name, &current_stock, &max_capacity, &units_sold) == 4) {
        float stock_percentage = calculate_stock_percentage(current_stock, max_capacity);
        float sales_percentage = ((float)units_sold / max_capacity) * 100.0f;
        int refill_amount = calculate_refill_amount(current_stock, max_capacity);

        printf("Item: %s\n", item_name);
        printf("  Stock Percentage: %.2f%%\n", stock_percentage);
        printf("  Sales Percentage: %.2f%%\n", sales_percentage);
        printf("  Refill Needed: %d units\n", refill_amount);

        printf("Confirm refill for %s? (y/n): ", item_name);
        char confirmation;
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'Y') {
            save_to_csv(output_file, item_name, current_stock, max_capacity, refill_amount);
        }
    }

    fclose(file);
    printf("Inventory processing completed.\n");
}

int main() {
    const char *inventory_file = "inventory.csv";
    const char *output_file = "algo.csv";

    process_inventory(inventory_file, output_file);

    return 0;
}
