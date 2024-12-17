#ifndef COUPON_H
#define COUPON_H

#include <stdio.h>
#include <string.h>
#include <time.h>

// Function to check if a coupon is expired
int is_coupon_expired(const char* expiryDate);

// Function to apply discount based on coupon
double apply_coupon_discount_csv(const char* couponCsvPath, const char* couponCode, double totalPrice);

#endif
