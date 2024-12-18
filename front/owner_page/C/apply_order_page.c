#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../apply_order_page.h"

typedef struct {
    char id[10];
    char goodsid[10];
    char userid[10];
    double price;
    int quantity;
} Order;


void showAllData(const char* filepath);
void sortOrders(Order orders[], int count, int sortOption);
int comparePriceHighLow(const void* a, const void* b);
int comparePriceLowHigh(const void* a, const void* b);
int compareQuantityHighLow(const void* a, const void* b);
int compareQuantityLowHigh(const void* a, const void* b);
void displayOrders(Order orders[], int count);

void Apply_Order_Page(AUTH *auth) {
    char* filepath = "back/warehouse/1/order.csv";
    int choice;

    while (1) {  // menu
        printf("\nSelect an option:\n");
        printf("1. Show all data\n");
        printf("2. Sort data\n");
        printf("3. Return\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            showAllData(filepath);
        } else if (choice == 2) {
            FILE *file = fopen(filepath, "r");
            if (file == NULL) {
                perror("Error opening order file");
                return;
            }

            char line[256];
            Order orders[100]; // Assuming a maximum of 100 orders
            int count = 0;

            // header
            if (fgets(line, sizeof(line), file) == NULL) {
                perror("Error reading header line");
                fclose(file);
                return;
            }

            // Read and store 
            while (fgets(line, sizeof(line), file)) {
                if (sscanf(line, "%9[^,],%9[^,],%9[^,],%lf,%d",
                           orders[count].id,
                           orders[count].goodsid,
                           orders[count].userid,
                           &orders[count].price,
                           &orders[count].quantity) == 5) {
                    count++;
                } else {
                    fprintf(stderr, "Error parsing line: %s", line);
                }
            }
            fclose(file);

            int sortOption;
            printf("\nSelect a sorting option:\n");
            printf("1. Sort by Price (High to Low)\n");
            printf("2. Sort by Price (Low to High)\n");
            printf("3. Sort by Quantity (High to Low)\n");
            printf("4. Sort by Quantity (Low to High)\n");
            printf("Enter your choice: ");
            scanf("%d", &sortOption);

            sortOrders(orders, count, sortOption);
            displayOrders(orders, count);
        } else if (choice == 3) {
            printf("\n");
            break; 
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void showAllData(const char* filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening order file");
        return;
    }

    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        perror("Error reading header line");
        fclose(file);
        return;
    }

    printf("\n%-10s %-10s %-10s %-10s %-10s\n", "ID", "GoodsID", "UserID", "Price", "Quantity");
    printf("---------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        char id[10], goodsid[10], userid[10], price[10], quantity[10];

        if (sscanf(line, "%9[^,],%9[^,],%9[^,],%9[^,],%9[^\n]", id, goodsid, userid, price, quantity) == 5) {
            printf("%-10s %-10s %-10s %-10s %-10s\n", id, goodsid, userid, price, quantity);
        } else {
            fprintf(stderr, "Error parsing line: %s", line);
        }
    }
    fclose(file);
}

void sortOrders(Order orders[], int count, int sortOption) {
    switch (sortOption) {
        case 1:
            qsort(orders, count, sizeof(Order), comparePriceHighLow);
            break;
        case 2:
            qsort(orders, count, sizeof(Order), comparePriceLowHigh);
            break;
        case 3:
            qsort(orders, count, sizeof(Order), compareQuantityHighLow);
            break;
        case 4:
            qsort(orders, count, sizeof(Order), compareQuantityLowHigh);
            break;
        default:
            printf("Invalid option. No sorting applied.\n");
            break;
    }
}

int comparePriceHighLow(const void* a, const void* b) {
    float priceA = ((Order*)a)->price;
    float priceB = ((Order*)b)->price;
    return (priceB > priceA) - (priceB < priceA); // Descending
}

int comparePriceLowHigh(const void* a, const void* b) {
    float priceA = ((Order*)a)->price;
    float priceB = ((Order*)b)->price;
    return (priceA > priceB) - (priceA < priceB); // Ascending
}

int compareQuantityHighLow(const void* a, const void* b) {
    int quantityA = ((Order*)a)->quantity;
    int quantityB = ((Order*)b)->quantity;
    return (quantityB > quantityA) - (quantityB < quantityA); // Descending
}

int compareQuantityLowHigh(const void* a, const void* b) {
    int quantityA = ((Order*)a)->quantity;
    int quantityB = ((Order*)b)->quantity;
    return (quantityA > quantityB) - (quantityA < quantityB); // Ascending
}

void displayOrders(Order orders[], int count) {
    printf("\n%-10s %-10s %-10s %-10s %-10s\n", "ID", "GoodsID", "UserID", "Price", "Quantity");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10s %-10s %-10s %-10.2f %-10d\n",
               orders[i].id, orders[i].goodsid, orders[i].userid, orders[i].price, orders[i].quantity);
    }
}
