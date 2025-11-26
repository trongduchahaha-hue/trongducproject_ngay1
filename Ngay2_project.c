#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NV 100
#define MAX_BC 500

typedef struct {
    int id;
    char ten[50];
    int tuoi;
} NhanVien;

NhanVien dsNV[MAX_NV];
int soLuongNV = 0;

void hienThiMenu();
void themNhanVien();
void capNhatNhanVien();
void xoaNhanVien();
void hienThiDanhSach();
int nhapSoNguyenDuong();

int main() {
    int choice;

    do {
        hienThiMenu();
        choice = nhapSoNguyenDuong();

        switch(choice) {
            case 1:
                themNhanVien();
                break;
            case 2:
                capNhatNhanVien();
                break;
            case 3:
                xoaNhanVien();
                break;
            case 4:
                hienThiDanhSach();
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }

    } while(choice != 0);

    return 0;
}

void hienThiMenu() {
    printf("\n============ Hien Thi Menu ============\n");
    printf("1. Them nhan vien moi\n");
    printf("2. Cap nhat ho so nhan vien\n");
    printf("3. Xoa nhan vien\n");
    printf("4. Hien thi danh sach\n");
    printf("5. Tim kiem nhan vien\n");
    printf("6. Sap xep danh sach\n");
    printf("7. Cham cong ngay\n");
    printf("8. Xem bang cong\n");
    printf("0. Thoat chuong trinh\n");
    printf("=======================================\n");
    printf("Nhap lua chon: ");
    fflush(stdin); 
        fgets(buffer, sizeof(buffer), stdin);
        removeNewline(buffer);

        if(strlen(buffer) == 0) {
             choice = -1; 
        } else {
             choice = atoi(buffer);
             // Kiem tra ky hon: neu nhap chu thi atoi tra ve 0 -> Check xem user co nhap so 0 that khong
             if (choice == 0 && strcmp(buffer, "0") != 0) {
                 choice = -1;
             }
        }
}

int nhapSoNguyenDuong() {
    int x;
    while(scanf("%d", &x) != 1 || x < 0) {
        printf("Gia tri khong hop le! Vui long nhap so nguyen >= 0: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');
    return x;
}

int isDuplicateId(int id) {
    for(int i = 0; i < soLuongNV; i++) {
        if(dsNV[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void themNhanVien() {
    if(soLuongNV >= MAX_NV) {
        printf("Danh sach nhan vien da day.\n");
        return;
    }

    NhanVien nv;
    int validId = 0;

    do {
        printf("Nhap ID nhan vien : ");
        nv.id = nhapSoNguyenDuong();
        if(nv.id == 0) {
            printf("ID phai lon hon 0. Vui long nhap lai.\n");
            continue;
        }
        if(isDuplicateId(nv.id)) {
            printf("ID da ton tai. Vui long nhap ID khac.\n");
        } else {
            validId = 1;
        }
    } while(!validId);

    do {
        printf("Nhap ten nhan vien: ");
        fgets(nv.ten, sizeof(nv.ten), stdin);
        nv.ten[strcspn(nv.ten, "\n")] = '\0';
        if(strlen(nv.ten) == 0) {
            printf("Ten nhan vien khong duoc de trong. Vui long nhap lai.\n");
        }
    } while(strlen(nv.ten) == 0);

    do {
        printf("Nhap tuoi nhan vien: ");
        nv.tuoi = nhapSoNguyenDuong();
        if(nv.tuoi == 0) {
            printf("Tuoi phai lon hon 0. Vui long nhap lai.\n");
        }
    } while(nv.tuoi == 0);

    dsNV[soLuongNV++] = nv;
    printf("Them nhan vien thanh cong!\n");
}

void capNhatNhanVien() {
    if(soLuongNV == 0) {
        printf("Danh sach nhan vien rong.\n");
        return;
    }
    
    int id, found = 0;
    printf("Nhap ID nhan vien can cap nhat: ");
    id = nhapSoNguyenDuong();

    for(int i = 0; i < soLuongNV; i++) {
        if(dsNV[i].id == id) {
            found = 1;

            do {
                printf("Nhap ten moi: ");
                fgets(dsNV[i].ten, sizeof(dsNV[i].ten), stdin);
                dsNV[i].ten[strcspn(dsNV[i].ten, "\n")] = '\0';
                if(strlen(dsNV[i].ten) == 0) {
                    printf("Ten nhan vien khong duoc de trong. Vui long nhap lai.\n");
                }
            } while(strlen(dsNV[i].ten) == 0);

            do {
                printf("Nhap tuoi moi: ");
                dsNV[i].tuoi = nhapSoNguyenDuong();
                if(dsNV[i].tuoi == 0) {
                    printf("Tuoi phai lon hon 0. Vui long nhap lai.\n");
                }
            } while(dsNV[i].tuoi == 0);

            printf("Cap nhat nhan vien thanh cong!\n");
            break;
        }
    }

    if(!found) {
        printf("Khong tim thay nhan vien co ID %d.\n", id);
    }
}

void xoaNhanVien() {
    if(soLuongNV == 0) {
        printf("Danh sach nhan vien rong.\n");
        return;
    }

    int id, found = 0;
    printf("Nhap ID nhan vien can xoa: ");
    id = nhapSoNguyenDuong();

    for(int i = 0; i < soLuongNV; i++) {
        if(dsNV[i].id == id) {
            found = 1;
            for(int j = i; j < soLuongNV - 1; j++) {
                dsNV[j] = dsNV[j + 1];
            }
            soLuongNV--;
            printf("Xoa nhan vien thanh cong!\n");
            break;
        }
    }

    if(!found) {
        printf("Khong tim thay nhan vien co ID %d.\n", id);
    }
}

void hienThiDanhSach() {
    if(soLuongNV == 0) {
        printf("Danh sach nhan vien rong.\n");
        return;
    }

    printf("+-----+----------------------+-------+\n");
    printf("| %-3s | %-20s | %-5s |\n", "ID", "Ten", "Tuoi");
    printf("+-----+----------------------+-------+\n");
    for(int i = 0; i < soLuongNV; i++) {
        printf("| %-3d | %-20s | %-5d |\n", dsNV[i].id, dsNV[i].ten, dsNV[i].tuoi);
    }
    printf("+-----+----------------------+-------+\n");
}

