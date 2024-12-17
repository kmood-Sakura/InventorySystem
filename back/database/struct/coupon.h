#ifndef COUPON_H
#define COUPON_H

#include "../define/id.h"
// Coupon structure
typedef struct {
    char couponCode[MAX_ID_LEN];
    int percentage;  // Discount percentage
    double amount;   // Additional discount or amount (e.g., cashback, fixed amount)
} Coupon;

#endif
