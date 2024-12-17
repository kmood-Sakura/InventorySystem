#ifndef COUPON_H
#define COUPON_H

#include <stdio.h>
#include <string.h>

// Function to check if a coupon is valid for the total price
int apply_coupon_discount_csv(const char* couponCsvPath, const char* couponCode, double totalPrice);

#endif
