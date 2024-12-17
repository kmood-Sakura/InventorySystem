#ifndef AMAZON_AGLO_SERVICE_H
#define AMAZON_AGLO_SERVICE_H

#include <stdio.h>


// ประกาศฟังก์ชันสำหรับการคำนวณเปอร์เซ็นสินค้า
float calculate_stock_percentage(int current_stock, int max_capacity);

// ประกาศฟังก์ชันสำหรับคำนวณจำนวนสินค้าที่ต้องเติม
int calculate_refill_amount(int current_stock, int max_capacity);

// ประกาศฟังก์ชันสำหรับการบันทึกผลในไฟล์ CSV
void save_to_csv(const char *filename, const char *warehouse_name, int current_stock, int max_capacity, int to_refill);

// ประกาศฟังก์ชันสำหรับยืนยันการส่งสินค้า
void confirm_shipment(const char *filename);

// ประกาศฟังก์ชันสำหรับประมวลผลไฟล์ inventory
void process_inventory(const char *inventory_file, const char *output_file);

#endif // AMAZON_AGLO_SERVICE_H
