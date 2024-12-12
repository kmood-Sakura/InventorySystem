#ifndef COUPON_H
#define COUPON_H

// Coupon structure
typedef struct {
    char couponCode[10];
    int percentage;  // Discount percentage
    double amount;   // Additional discount or amount (e.g., cashback, fixed amount)
} Coupon;

// Function prototypes
int load_coupons_from_csv(const char* filePath, Coupon** coupons, int* couponCount);
double apply_coupon_discount(const char* couponCode, double totalPrice, Coupon* coupons, int couponCount);

#endif
