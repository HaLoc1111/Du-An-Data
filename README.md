# Du-An-Data
Tên dự án: Hệ thống Phân tích & Báo cáo Tự động Doanh số Chuỗi Cửa hàng
(Sales Data Analysis & Automated Reporting System)

C: Dùng để sinh dữ liệu mẫu (Data Generation). Vì C chạy rất nhanh, bạn có thể viết chương trình sinh ra 1 file CSV chứa khoảng 10,000 - 50,000 dòng giao dịch bán hàng (ngày tháng, mã hàng, số lượng, giá, khách hàng...).

SQL (MySQL/SQLite): Import file CSV vào database. Dùng SQL để thực hiện các câu lệnh truy vấn cơ bản (tổng doanh thu theo tháng, lọc top 10 khách hàng VIP...).

Python (hoặc R): Kết nối vào SQL để lấy dữ liệu. Dùng thư viện (Pandas trong Python hoặc Dplyr trong R) để làm sạch dữ liệu (xử lý null, chuẩn hóa) và tính toán các chỉ số phức tạp hơn. Sau đó xuất ra một file Clean_Data.xlsx.

Excel & VBA: File Excel sẽ lấy dữ liệu từ Clean_Data.xlsx. Dùng VBA để viết macro: Click 1 nút là tự động refresh Pivot Table, vẽ biểu đồ và xuất ra file PDF báo cáo.

Dùng ML để phân tích tình hình thực tế của 3 Miền



