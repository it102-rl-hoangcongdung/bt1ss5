# Bài tập 01: Dò vết & Khắc phục Lỗi Vượt Biên Chỉ số Mảng (Buffer Overflow)

> 👤 **Học viên:** Hoàng Công Dũng | **Mã SV:** PTIT-HCM-009
> 🏫 **Môn học:** it102-rl-hoangcongdung

---

## 📊 Sơ đồ thiết kế hệ thống (Flowchart)

> 💡 *Sơ đồ dưới đây được render tự động trực tiếp trên GitHub bằng Mermaid. Bạn cũng có thể tải file **`bt1.drawio`** trong repository này để mở và chỉnh sửa trực tiếp trên [Draw.io (diagrams.net)](https://app.diagrams.net).* 

```mermaid
graph TD
  A[Bắt đầu] --> B[Khai báo mảng queue_numbers 4 phần tử]
  B --> C[Gán patient_position = 4]
  C --> D[Ghi đè queue_numbers[4] gây lỗi buffer overflow]
  D --> E[Kết thúc]
```

---

## Nhiệm vụ 1: Phân tích lỗi & Lập bảng Test Cases

Sau khi trace code chương trình quản lý đặt lịch khám bệnh CLINIC_APPOINTMENT, mình phát hiện nguyên nhân gốc rễ dẫn đến việc mã số thứ tự của bệnh nhân thứ 4 không được cập nhật là do sự nhầm lẫn giữa vị trí thực tế trên giao diện (1-based index) và chỉ số mảng trong lập trình C (0-based index).

Trong đoạn mã nguồn ban đầu, mảng queue_numbers có kích thước là 4, nghĩa là các chỉ số hợp lệ chỉ chạy từ 0 đến 3 (tương ứng với bệnh nhân 1 đến bệnh nhân 4). Khi lễ tân muốn cập nhật thông tin cho bệnh nhân ở vị trí thứ 4, biến patient_position lại được gán giá trị bằng 4. Lệnh queue_numbers[patient_position] = new_queue_number tương đương với queue_numbers[4] = 1099, dẫn đến lỗi ghi đè vùng nhớ ngoài phạm vi mảng (Buffer Overflow / Out-of-bounds access). Vùng nhớ bị ghi đè nằm ngoài mảng nên khi in ra màn hình ở chỉ số hợp lệ queue_numbers[3], giá trị cũ '1004' vẫn giữ nguyên và không xảy ra lỗi crash chương trình, gây ra hiểu nhầm là hệ thống vẫn chạy bình thường.

- Nguyên nhân kỹ thuật: Truy cập chỉ số mảng bằng 4 trong mảng khai báo kích thước 4 (vượt biên giới hạn 0-3).
- Hậu quả nghiệp vụ: Dữ liệu bị ghi đè vào vùng nhớ lân cận, không cập nhật được số thứ tự mới cho bệnh nhân số 4.
- Bài học rút ra: Luôn ghi nhớ quy tắc mảng trong C bắt đầu từ 0. Vị trí thứ n sẽ tương ứng với chỉ số n - 1.

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế | Kết quả đúng mong đợi |
| --- | --- | --- | --- |
| TC01: Cập nhật bệnh nhân thứ 4 | patient_position = 4, new_queue_number = 1099 | Mã số hiển thị vẫn là 1004, giá trị 1099 ghi đè lệch vùng nhớ | Mã số hiển thị phải được cập nhật thành 1099 ở vị trí thứ 4 |
| TC02: Truy xuất toàn bộ danh sách | queue_numbers[0] tới queue_numbers[3] | In ra thứ tự cũ do không sửa đúng ô nhớ chỉ số 3 | In ra danh sách chính xác với số thứ tự mới đã cập nhật |

## Nhiệm vụ 2: Sửa lỗi mã nguồn

Để khắc phục triệt để lỗi trên, mình đã điều chỉnh lại cách xác định chỉ số mảng sao cho khớp với vị trí thực tế của bệnh nhân. Cụ thể, vị trí thứ 4 sẽ tương ứng với chỉ số mảng là patient_position - 1 (tức là index 3).

Mã nguồn sau khi sửa đã được kiểm tra kỹ lưỡng, biên dịch thành công bằng trình biên dịch GCC mà không gặp bất kỳ cảnh báo hay lỗi nào, đồng thời xử lý chính xác 100% yêu cầu nghiệp vụ của phòng khám.

- Sửa câu lệnh truy cập mảng thành queue_numbers[patient_position - 1] = new_queue_number.
- Đảm bảo tuân thủ kiến thức nền tảng của buổi học, không sử dụng các cấu trúc nâng cao.

---

## 📁 Danh sách tệp tin nộp bài trong Repository
- 📝 `bt1.docx`: Báo cáo tài liệu phân tích nghiệp vụ hoàn chỉnh.
- 🎨 `bt1.drawio`: File thiết kế sơ đồ chuẩn theo quy định đề bài (mở trực tiếp bằng [Draw.io](https://app.diagrams.net) hoặc Lucidchart).
- 💻 `main.c`: Mã nguồn chương trình.
