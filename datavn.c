#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char id[10];
    char name[50]; // Tăng độ dài chuỗi để chứa đủ ký tự có dấu
    double base_price; 
    double base_cost;  
} Product;

// Danh sách 3 khu vực (Tiếng Việt có dấu)
const char *regions[] = {"Miền Bắc", "Miền Trung", "Miền Nam"};

// Danh sách 5 sản phẩm mẫu (Tiếng Việt có dấu)
Product products[] = {
    {"L01", "Laptop Dell", 15000000, 12000000},
    {"P01", "Điện thoại", 8000000, 6000000},
    {"A01", "Tai nghe", 500000, 250000},
    {"M01", "Chuột quang", 200000, 100000},
    {"K01", "Bàn phím", 800000, 500000}
};

double get_seasonal_factor(int month) {
    // Mùa cao điểm (Tết/Lễ)
    if (month == 11 || month == 12 || month == 1 || month == 2) {
        return 1.5 + ((rand() % 50) / 100.0); 
    }
    // Mùa hè (thấp điểm)
    if (month == 6 || month == 7) {
        return 0.8 + ((rand() % 20) / 100.0); 
    }
    // Bình thường
    return 1.0 + ((rand() % 20) / 100.0); 
}

int main() {
    // Tên file output
    FILE *f = fopen("smart_sales_data_vn.csv", "w");
    if (f == NULL) {
        printf("Khong the tao file!\n");
        return 1;
    }

    // 1. GHI BOM (BẮT BUỘC ĐỂ EXCEL HIỂU TIẾNG VIỆT)
    fprintf(f, "\xEF\xBB\xBF");

    // 2. Ghi tiêu đề cột bằng Tiếng Việt
    fprintf(f, "MaGiaoDich,Ngay,Thang,KhuVuc,TenSanPham,SoLuong,GiaBan,GiaVon,DoanhThu,LoiNhuan\n");

    srand(time(NULL));

    printf("Dang sinh 10,000 dong du lieu Tieng Viet...\n");

    for (int i = 1; i <= 10000; i++) {
        int month = rand() % 12 + 1;
        int day = rand() % 28 + 1;
        int p_idx = rand() % 5; 
        int r_idx = rand() % 3; 

        // Tính toán số lượng
        double seasonal_factor = get_seasonal_factor(month);
        int base_qty = rand() % 5 + 1;
        int final_qty = (int)(base_qty * seasonal_factor); 
        if (final_qty < 1) final_qty = 1;

        // Biến động giá
        double price_noise = 1.0 + ((rand() % 10 - 5) / 100.0); 
        double final_price = products[p_idx].base_price * price_noise;

        // Tính chi phí vận chuyển (Logic khu vực)
        // LƯU Ý: So sánh chuỗi phải chính xác từng ký tự có dấu
        double shipping_cost = 0;
        if (strcmp(regions[r_idx], "Miền Trung") == 0) {
            shipping_cost = products[p_idx].base_cost * 0.1; 
        }

        double final_cost = products[p_idx].base_cost + shipping_cost;

        double revenue = final_qty * final_price;     
        double total_cost = final_qty * final_cost;   
        double profit = revenue - total_cost;        

        // Ghi dữ liệu ra file
        fprintf(f, "%d,%02d/%02d/2023,%d,%s,%s,%d,%.0f,%.0f,%.0f,%.0f\n",
                i, day, month, month, 
                regions[r_idx], 
                products[p_idx].name, 
                final_qty, 
                final_price, 
                final_cost, 
                revenue, 
                profit);
    }

    fclose(f);
    printf("Xong! Kiem tra file 'smart_sales_data_vn.csv'.\n");
    
    return 0;
}