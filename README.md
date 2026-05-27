# ĐỒ ÁN HỆ THỐNG NHÚNG - NHÓM 4 - HỆ THỐNG BÁO CHÁY TẠI GARAGE CẢNH BÁO QUA ỨNG DỤNG ĐIỆN THOẠI 

## 1. Giới thiệu đề tài

Đây là repository lưu trữ toàn bộ nội dung đồ án môn Hệ thống nhúng của Nhóm 4.  
Repository bao gồm mã nguồn chương trình, báo cáo đồ án, hình ảnh mô hình thực tế và video demo quá trình hoạt động của hệ thống.

Mục tiêu của đồ án là xây dựng một hệ thống nhúng có khả năng thu thập dữ liệu từ các cảm biến, xử lý tín hiệu đầu vào và điều khiển thiết bị đầu ra theo yêu cầu của bài toán. Hệ thống được triển khai trên phần cứng thực tế và có thể giám sát hoặc điều khiển thông qua giao diện phần mềm/app nếu có.

---

## 2. Thành viên nhóm

| STT | Họ và tên | MSSV | Vai trò |
|-----|----------|------|--------|
| 1 | Nguyễn Ngọc Thuận | 24521742 | Trưởng nhóm / Code / Demo |
| 2 | Trương Đức Thịnh | 24521708 | Thiết kế mạch |
| 3 | Nguyễn Phương Nam | 24521742 | Viết báo cáo |
| 4 | Phan Như Thuần | 24521744 | Test hệ thống / Slide  |

---

## 3. Chức năng chính của hệ thống

Hệ thống trong đồ án thực hiện các chức năng chính sau:

- Đọc dữ liệu từ cảm biến hoặc thiết bị đầu vào.
- Xử lý dữ liệu bằng vi điều khiển.
- Điều khiển thiết bị đầu ra theo điều kiện đã lập trình.
- Hiển thị hoặc gửi dữ liệu lên giao diện giám sát nếu có.
- Kiểm tra hoạt động thực tế thông qua mô hình phần cứng.
- Ghi nhận kết quả hoạt động trong video demo.

---

## 4. Phần cứng sử dụng

Các linh kiện chính được sử dụng trong đồ án:

- Vi điều khiển: ESP32 / Arduino / Raspberry Pi / hoặc thiết bị nhóm sử dụng.
- Cảm biến: ...
- Module điều khiển: ...
- Thiết bị đầu ra: LED, relay, buzzer, motor hoặc thiết bị khác.
- Dây nối, breadboard, nguồn cấp và các linh kiện hỗ trợ khác.

---

## 5. Phần mềm và công cụ sử dụng

- Arduino IDE / PlatformIO / Python / công cụ lập trình khác.
- Thư viện hỗ trợ cho cảm biến và module.
- Blynk / Web Server / App giám sát nếu có.
- GitHub để lưu trữ mã nguồn và tài liệu.
- Công cụ quay video demo và soạn báo cáo.

---

## 6. Cấu trúc thư mục

```text
Project_Nhom4_HeThongNhung/
│
├── README.md
│
├── Source_Code/
│   └── Chứa mã nguồn chương trình của hệ thống
│
├── Report/
│   └── Chứa file báo cáo đồ án
│
├── Demo/
│   └── Chứa video demo hoặc link video demo
│
├── Images/
│   └── Chứa hình ảnh mô hình, sơ đồ mạch và kết quả thực tế
│
└── Documents/
    └── Chứa tài liệu phụ, datasheet hoặc hướng dẫn liên quan
