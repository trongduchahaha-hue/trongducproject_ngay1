#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NV 100
#define MAX_NGAY 31
#define PAGE_SIZE 3

typedef struct {
    int id;
    char ten[50];
    char chucVu[50];     
    double luongCoBan;     
    int chamCong[MAX_NGAY]; 
    int workDay;
} NhanVien;

NhanVien dsNV[MAX_NV];
int soLuongNV = 0;

void hienThiMenu();
int nhapSoNguyenDuong();
double nhapSoThucDuong();
int TrungLapId(int id);
void themNhanVien();
void capNhatNhanVien();
void xoaNhanVien();
void hienThiDanhSach();
void timKiemNhanVien();
void sapXepDanhSach();
int soNgayTrongThang(int thang, int nam);
void chamCongNgay();
void xemBangCong();

int main() {
    int choice;
    do {
        hienThiMenu();
        printf("Nhap lua chon: ");
        choice = nhapSoNguyenDuong();

        switch(choice) {
            case 1: themNhanVien(); break;
            case 2: capNhatNhanVien(); break;
            case 3: xoaNhanVien(); break;
            case 4: hienThiDanhSach(); break;
            case 5: timKiemNhanVien(); break;
            case 6: sapXepDanhSach(); break;
            case 7: chamCongNgay(); break;
            case 8: xemBangCong(); break;
            case 0: printf("Thoat chuong trinh...\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while(choice != 0);

    return 0;
}

void hienThiMenu() {
    printf("\n================= MENU =================\n");
    printf("1. Them nhan vien\n");
    printf("2. Cap nhat nhan vien\n");
    printf("3. Xoa nhan vien\n");
    printf("4. Hien thi danh sach\n");
    printf("5. Tim kiem nhan vien\n");
    printf("6. Sap xep danh sach theo ID\n");
    printf("7. Cham cong ngay\n");
    printf("8. Xem bang cong va cham cong\n");
    printf("0. Thoat\n");
    printf("========================================\n");
}

int nhapSoNguyenDuong() {
    char buffer[50];
    int value;
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) {
            printf("Khong duoc de trong! Nhap lai: ");
            continue;
        }
        int isNum = 1;
        for (int i = 0; i < strlen(buffer); i++) {
            if (buffer[i] < '0' || buffer[i] > '9') {
                isNum = 0;
                break;
            }
        }
        if (!isNum) {
            printf("Chi duoc nhap so! Nhap lai: ");
            continue;
        }
        value = atoi(buffer);
        return value;
    }
}

double nhapSoThucDuong() {
    char buffer[50];
    double value;
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) {
            printf("Khong duoc de trong! Nhap lai: ");
            continue;
        }
        char* endptr;
        value = strtod(buffer, &endptr);
        if (*endptr != '\0' || value < 0) { 
            printf("Nhap so thuc >=0! Nhap lai: "); 
            continue; 
        }
        return value;
    }
}

int TrungLapId(int id) {
    for (int i = 0; i < soLuongNV; i++)
        if (dsNV[i].id == id) return 1;
    return 0;
}

void themNhanVien() {
    if (soLuongNV >= MAX_NV) { 
        printf("Danh sach da day!\n"); 
        return; 
    }

    NhanVien nv;
    printf("Nhap ID (>0): ");
    while (1) {
        nv.id = nhapSoNguyenDuong();
        if (nv.id <= 0) {
            printf("ID phai > 0! Nhap lai: ");
        } else if (TrungLapId(nv.id)) {
            printf("ID da ton tai! Nhap lai: ");
        } else break;
    }

    do { 
        printf("Nhap ten: "); 
        fgets(nv.ten, sizeof(nv.ten), stdin); 
        nv.ten[strcspn(nv.ten, "\n")] = '\0'; 
    } while(strlen(nv.ten) == 0);

    do { 
        printf("Nhap chuc vu: "); 
        fgets(nv.chucVu, sizeof(nv.chucVu), stdin); 
        nv.chucVu[strcspn(nv.chucVu, "\n")] = '\0'; 
    } while(strlen(nv.chucVu) == 0);

    printf("Nhap luong co ban: ");
    nv.luongCoBan = nhapSoThucDuong();

    for (int i = 0; i < MAX_NGAY; i++) 
        nv.chamCong[i] = 0;
    nv.workDay = 0;

    dsNV[soLuongNV++] = nv;
    printf("Them nhan vien thanh cong!\n");
}

void capNhatNhanVien() {
    if (soLuongNV == 0) { 
        printf("Danh sach rong.\n"); 
        return; 
    }

    printf("Nhap ID can cap nhat: ");
    int id = nhapSoNguyenDuong();

    for (int i = 0; i < soLuongNV; i++) {
        if (dsNV[i].id == id) {
            do { 
                printf("Nhap ten moi: "); 
                fgets(dsNV[i].ten, sizeof(dsNV[i].ten), stdin); 
                dsNV[i].ten[strcspn(dsNV[i].ten, "\n")] = '\0'; 
            } while(strlen(dsNV[i].ten) == 0);

            do { 
                printf("Nhap chuc vu moi: "); 
                fgets(dsNV[i].chucVu, sizeof(dsNV[i].chucVu), stdin); 
                dsNV[i].chucVu[strcspn(dsNV[i].chucVu, "\n")] = '\0'; 
            } while(strlen(dsNV[i].chucVu) == 0);

            printf("Nhap luong co ban moi: ");
            dsNV[i].luongCoBan = nhapSoThucDuong();
            printf("Cap nhat thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay ID!\n");
}

void xoaNhanVien() {
    if (soLuongNV == 0) {
        printf("Danh sach rong.\n");
        return;
    }
    printf("Nhap ID can xoa: ");
    int id = nhapSoNguyenDuong();
    int found = 0;
    for (int i = 0; i < soLuongNV; i++) {
        if (dsNV[i].id == id) {
            for (int j = i; j < soLuongNV - 1; j++)
                dsNV[j] = dsNV[j+1];
            soLuongNV--;
            found = 1;
            printf("Xoa nhan vien thanh cong!\n");
            break;
        }
    }
    if (!found) printf("Khong tim thay ID!\n");
}

void hienThiDanhSach() {
    if (soLuongNV == 0) { 
        printf("Danh sach rong.\n"); 
        return; 
    }

    int tongTrang = (soLuongNV + PAGE_SIZE - 1) / PAGE_SIZE;
    int trangHienTai = 1;
    char input[10];

    while (1) {
        system("cls");
        printf("\033[H\033[J");
        printf("-- DANH SACH NHAN VIEN (TRANG %d/%d) --\n", trangHienTai, tongTrang);
        printf("+-------+------------------------------+------------------+-----------+----------+\n");
        printf("|  ID   |            TEN               |    CHUC VU       | LUONG     | WorkDay  |\n");
        printf("+-------+------------------------------+------------------+-----------+----------+\n");

        int start = (trangHienTai - 1) * PAGE_SIZE;
        int end = start + PAGE_SIZE;
        if (end > soLuongNV) end = soLuongNV;

        for (int i = start; i < end; i++) {
            printf("| %-5d | %-28s | %-16s | %-9.2f | %-8d |\n",
                   dsNV[i].id, dsNV[i].ten, dsNV[i].chucVu, dsNV[i].luongCoBan, dsNV[i].workDay);
        }
        printf("+-------+------------------------------+------------------+-----------+----------+\n");

        printf("\n[Trang %d/%d] | Tong so nhan vien: %d\n", trangHienTai, tongTrang, soLuongNV);
        printf("Nhap: [ENTER] de xem trang tiep theo, [So Trang] de den trang cu the, [0] de ket thuc.\nLua chon cua ban: ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) { 
            trangHienTai++; 
            if (trangHienTai > tongTrang) trangHienTai = 1; 
        }
        else if (strcmp(input, "0") == 0) break;
        else {
            int trangNhap = atoi(input);
            if (trangNhap >= 1 && trangNhap <= tongTrang) trangHienTai = trangNhap;
            else { 
                printf("Trang khong hop le. Nhan Enter de tiep tuc...");
                getchar(); 
            }
        }
    }
}

void timKiemNhanVien() {
    if (soLuongNV == 0) { 
        printf("Danh sach rong.\n"); 
        return; 
    }
    printf("Nhap ID can tim: ");
    int id = nhapSoNguyenDuong();

    for (int i = 0; i < soLuongNV; i++) {
        if (dsNV[i].id == id) {
            printf("\n-- Thong tin nhan vien --\n");
            printf("ID: %d\nTen: %s\nChuc vu: %s\nLuong co ban: %.2f\nWorkDay: %d\n",
                dsNV[i].id, dsNV[i].ten, dsNV[i].chucVu, dsNV[i].luongCoBan, dsNV[i].workDay);
            return;
        }
    }
    printf("Khong tim thay!\n");
}

void sapXepDanhSach() {
    for (int i = 0; i < soLuongNV - 1; i++) {
        for (int j = i + 1; j < soLuongNV; j++) {
            if (dsNV[i].id > dsNV[j].id) {
                NhanVien temp = dsNV[i];
                dsNV[i] = dsNV[j];
                dsNV[j] = temp;
            }
        }
    }
    printf("Sap xep thanh cong!\n");
}

int soNgayTrongThang(int thang, int nam) {
    switch(thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) ? 29 : 28;
        default: return 0;
    }
}

void chamCongNgay() {
    if (soLuongNV == 0) { 
        printf("Danh sach rong.\n"); 
        return; 
    }

    int nam, thang, ngay, id;

    printf("Nhap nam: ");
    nam = nhapSoNguyenDuong();

    printf("Nhap thang (1-12): ");
    while (1) { 
        thang = nhapSoNguyenDuong(); 
        if (thang >=1 && thang <=12) break; 
        else printf("Thang khong hop le! Nhap lai: "); 
    }

    int maxNgay = soNgayTrongThang(thang, nam);
    printf("Nhap ngay (1-%d): ", maxNgay);
    while (1) { 
        ngay = nhapSoNguyenDuong();  
        if (ngay >=1 && ngay <= maxNgay) break; 
        else printf("Ngay khong hop le! Nhap lai: "); 
    }

    printf("Nhap ID cham cong: ");
    id = nhapSoNguyenDuong();

    int index = -1;
    for (int i = 0; i < soLuongNV; i++) { 
        if (dsNV[i].id == id) { 
            index = i; break; 
        } 
    }
    if (index == -1) { 
        printf("Ma nhan vien khong ton tai!\n"); 
        return; 
    }

    if (dsNV[index].chamCong[ngay-1]==1) { 
        printf("Nhan vien da cham cong di lam vao ngay %d!\n", ngay);
        return; 
    }

    char input[10];
    printf("Nhap 1 de cham cong di lam, bat ky phim nao de bo qua: ");
    fgets(input, sizeof(input), stdin);
    if (input[0]=='1') { 
        dsNV[index].chamCong[ngay-1]=1; 
        dsNV[index].workDay++; 
        printf("Cham cong di lam thanh cong! (Ngay %d/%d/%d)\n", ngay, thang, nam); 
    }
    else printf("Bo qua cham cong ngay %d/%d/%d.\n", ngay, thang, nam);
}

void xemBangCong() {
    if (soLuongNV == 0) { 
        printf("Danh sach rong.\n"); 
        return; 
    }

    int nam, thang;
    printf("Nhap nam: "); 
    nam = nhapSoNguyenDuong();
    printf("Nhap thang (1-12): ");
    while (1) { 
        thang = nhapSoNguyenDuong(); 
        if (thang >=1 && thang <=12) break; 
        else printf("Thang khong hop le! Nhap lai: "); 
    }

    int maxNgay = soNgayTrongThang(thang, nam);
    char input[10];

    while (1) {
        system("cls");
        printf("\033[H\033[J");
        printf("\n===================== BANG CHAM CONG THANG %d/%d =====================\n", thang, nam);
        printf("%-5s %-20s | ", "ID", "Ten");
        for (int d=1; d<=maxNgay; d++) printf("%2d ", d);
        printf("\n-----------------------------------------------------------------\n");

        for (int i=0; i<soLuongNV; i++) {
            printf("%-5d %-20s | ", dsNV[i].id, dsNV[i].ten);
            for (int d=0; d<maxNgay; d++) { 
                char symbol = dsNV[i].chamCong[d]==1?'X':'-'; 
                printf(" %c ", symbol); 
            }
            printf("\n");
        }
        printf("-----------------------------------------------------------------\n");

        printf("Nhap ID nhan vien de cham cong (0 de thoat): ");
        fgets(input, sizeof(input), stdin);
        int id = atoi(input);
        if (id == 0) break;

        int index = -1;
        for (int i = 0; i < soLuongNV; i++) {
            if (dsNV[i].id == id) { index = i; break; }
        }
        if (index == -1) {
            printf("Khong tim thay ID nhan vien! Nhan Enter de tiep tuc...");
            getchar();
            continue;
        }

        int ngay;
        while (1) {
            printf("Nhap ngay cham cong (1-%d): ", maxNgay);
            ngay = nhapSoNguyenDuong();
            if (ngay >= 1 && ngay <= maxNgay) break;
            else printf("Ngay khong hop le! Nhap lai.\n");
        }

        if (dsNV[index].chamCong[ngay-1]==1) {
            printf("Nhan vien da cham cong ngay %d!\n", ngay);
        } else {
            dsNV[index].chamCong[ngay-1] = 1;
            dsNV[index].workDay++;
            printf("Cham cong thanh cong ngay %d!\n", ngay);
        }

        printf("Nhan Enter de tiep tuc...");
        getchar();
    }
}

