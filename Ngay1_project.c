#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NV 100
#define MAX_BC 1000

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

int main() {
    int choice;

    do {
        hienThiMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                themNhanVien();
                break;
            case 2:
                capNhatNhanVien();
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
    printf("Thoat chuong trinh\n");
    printf("=======================================\n");
    printf("Nhap lua chon: ");
}

void themNhanVien() {
    if(soLuongNV >= MAX_NV) {
        printf("Danh sach nhan vien da day.\n");
        return;
    }

    NhanVien nv;
    printf("Nhap ID nhan vien: ");
    scanf("%d", &nv.id);
    getchar();
    printf("Nhap ten nhan vien: ");
    fgets(nv.ten, sizeof(nv.ten), stdin);
    nv.ten[strcspn(nv.ten, "\n")] = '\0'; 
    printf("Nhap tuoi nhan vien: ");
    scanf("%d", &nv.tuoi);
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
    scanf("%d", &id);

    for(int i = 0; i < soLuongNV; i++) {
        if(dsNV[i].id == id) {
            getchar(); 
            printf("Nhap ten moi: ");
            fgets(dsNV[i].ten, sizeof(dsNV[i].ten), stdin);
            dsNV[i].ten[strcspn(dsNV[i].ten, "\n")] = '\0';
            printf("Nhap tuoi moi: ");
            scanf("%d", &dsNV[i].tuoi);
            printf("Cap nhat nhan vien thanh cong!\n");
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Khong tim thay nhan vien co ID %d.\n", id);
    }
}

