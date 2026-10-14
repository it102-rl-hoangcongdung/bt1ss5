#include <stdio.h>

int main() {
    // Khoi tao danh sach 4 ma so thu tu kham ban dau
    int queue_numbers[4] = {1001, 1002, 1003, 1004};
    
    // Le tan muon cap nhat lai ma so uu tien cho Benh nhan vi tri thu 4
    // Su dung index dung chuan C (0-based index): vi tri thu 4 tuong ung voi index 3
    int patient_position = 4; 
    int new_queue_number = 1099;
    
    // Thao tac cap nhat chinh xac vao chi so index 3 (patient_position - 1)
    queue_numbers[patient_position - 1] = new_queue_number;
    
    // In ra danh sach 4 benh nhan ca sang
    printf("--- DANH SACH SO THU TU KHAM BENH ---\n");
    printf("Benh nhan 1 (Index 0): %d\n", queue_numbers[0]);
    printf("Benh nhan 2 (Index 1): %d\n", queue_numbers[1]);
    printf("Benh nhan 3 (Index 2): %d\n", queue_numbers[2]);
    printf("Benh nhan 4 (Index 3): %d\n", queue_numbers[3]);
    
    return 0;
}