#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char id[10];
    char name[30];
    double base_price; 
    double base_cost;  
} Product;

// Danh sách 3 khu vực
const char *regions[] = {"MienBac", "MienTrung", "MienNam"};

// Danh sách 5 sản phẩm mẫu
Product products[] = {
    {"L01", "Laptop Dell", 15000000, 12000000},
    {"P01", "Dien thoai", 8000000, 6000000},
    {"A01", "Tai nghe", 500000, 250000},
    {"M01", "Chuot quang", 200000, 100000},
    {"K01", "Ban phim", 800000, 500000}
};

double get_seasonal_factor(int month) {
    // Tháng 11, 12, 1, 2 là mùa cao điểm (Tết/Lễ) -> Bán gấp 1.5 đến 2 lần
    if (month == 11 || month == 12 || month == 1 || month == 2) {
        return 1.5 + ((rand() % 50) / 100.0); // 1.5 đến 2.0
    }
    // Tháng 6, 7 mùa hè -> Bán chậm hơn chút
    if (month == 6 || month == 7) {
        return 0.8 + ((rand() % 20) / 100.0); // 0.8 đến 1.0
    }
    // Các tháng còn lại bình thường
    return 1.0 + ((rand() % 20) / 100.0); // 1.0 đến 1.2
}

int main() {
    FILE *f = fopen("smart_sales_data.csv", "w");
    if (f == NULL) {
        printf("Khong the tao file!\n");
        return 1;
    }

    fprintf(f, "\xEF\xBB\xBF");

    fprintf(f, "TransID,Date,Month,Region,ProdName,Quantity,Price,Cost,Revenue,Profit\n");

    srand(time(NULL));

    printf("Dang sinh 10,000 dong du lieu co quy luat...\n");

    // Sinh 10,000 dòng dữ liệu
    for (int i = 1; i <= 10000; i++) {
        int month = rand() % 12 + 1;
        int day = rand() % 28 + 1;
        int p_idx = rand() % 5; 
        int r_idx = rand() % 3; 

        // A. Tính số lượng dựa trên Mùa vụ
        double seasonal_factor = get_seasonal_factor(month);
        int base_qty = rand() % 5 + 1; // Số lượng gốc 1-5
        int final_qty = (int)(base_qty * seasonal_factor); 
        if (final_qty < 1) final_qty = 1;

        // B. Biến động giá (Giá không cố định, chênh lệch 1 chút)
        double price_noise = 1.0 + ((rand() % 10 - 5) / 100.0); // +/- 5%
        double final_price = products[p_idx].base_price * price_noise;

        // C. Chi phí vận chuyển (Tác động vào Giá Vốn - Cost)
        // Giả sử Miền Trung chi phí vận chuyển cao hơn -> Giá vốn cao hơn -> Lợi nhuận thấp
        double shipping_cost = 0;
        if (strcmp(regions[r_idx], "MienTrung") == 0) {
            shipping_cost = products[p_idx].base_cost * 0.1; 
        }

        double final_cost = products[p_idx].base_cost + shipping_cost;

        double revenue = final_qty * final_price;     
        double total_cost = final_qty * final_cost;   
        double profit = revenue - total_cost;        

        // 5. Ghi vào file
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
    printf("Xong! Da tao file 'smart_sales_data.csv'.\n");
    
    return 0;
}