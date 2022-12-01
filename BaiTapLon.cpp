#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <graphics.h>
#include <math.h>
#include <windows.h>
using namespace std;

#define round(a) (a>=0) ? (int)(a+0.5) : (int)(a - 0.5)//neu a < 0.5 lam tron thanh a, a >= 0,5 lam tron thanh a+1
#define max_x 700
#define max_y 700
#define color 14//màu vàng yellow
#define PI 3.1415926536//sấp sỉ
#define sin_rad(x) sin(x * PI / 180)
#define cos_rad(x) cos(x * PI / 180)

struct TOADO{
    int x;
    int y;
};


//---------------------------------------HÀM TRUNG BÌNH CỘNG--------------------------------------
//trung bình cộng của x
int averageX(TOADO td[], int n){
    int tong = 0;
    for (int i = 0; i< n; i++){
        tong+= td[i].x;
    }
    return tong/n;
}

//trung bình cộng của y
int averageY(TOADO td[], int n){
    int tong = 0;
    for (int i = 0; i< n; i++){
        tong+= td[i].y;
    }
    return tong/n;
}

//---------------------------------------ĐỌC FILE--------------------------------------------------

//đọc file
void readFile(TOADO td[], int soDinh){
    //mở file
    FILE *fCin;
    char strNameFile[255] = "diemxy.txt";
    //printf("nhap ten file can xap sep: ");
    //gets(strNameFile);
    if ((fCin = fopen(strNameFile, "r")) == NULL){
        printf("error open file!!");
        exit(1);
    }
    int num;
    int n = 0;
    int i = 0;
    //đọc file
    while (fscanf(fCin, "%d", &num) != EOF){
        if (n % 2 == 0){
            td[i].x = num;
        }
        else{
            td[i].y = num;
            i++;
        }
        n++;
        if (i == soDinh){ //i bằng số đỉnh thì thoát
            break;
        }
    }
    fclose(fCin);
}

int soLuongPhanTu(){
    //mở file
    FILE *fCin;
    char strNameFile[255] = "diemxy.txt";
    //printf("nhap ten file can xap sep: ");
    //gets(strNameFile);
    if ((fCin = fopen(strNameFile, "r")) == NULL){
        printf("error open file!!");
        exit(1);
    }
    int num;
    int n = 0;
    //đọc file
    while (fscanf(fCin, "%d", &num) != EOF){
        n++;
    }
    return n;
}

//---------------------------------------VẼ ĐA GIÁC--------------------------------------
//vẽ đa giác
//n là số đỉnh của đa giác
void polygonDraw(TOADO td[], int n){
    if (n == 1){
        putpixel(td[0].x, td[0].y, color);
    }
    else if (n == 2){
        line(td[0].x, td[0].y, td[1].x, td[1].y);
    }
    else {
        for (int i = 0; i<n-1; i++){
            line(td[i].x, td[i].y, td[i+1].x, td[i+1].y);
        }
        line(td[0].x, td[0].y, td[n-1].x, td[n-1].y);
    }
}


//---------------------------------------CÁC PHÉP BIẾN HÌNH -----------------------------
//phép tịnh tiến có dộ dời x và độ dời y
void phepTinhTien(TOADO td[], int n, int doDoiX, int doDoiY){
    for (int i = 0; i<n; i++){
        td[i].x = td[i].x + doDoiX;
        td[i].y = td[i].y + doDoiY;
    }
}
//phép quay có góc quay vào điểm quay
void phepQuay(TOADO td[], int n, int gocQuay, int diemQuayX, int diemQuayY){
    double cosa = cos_rad(gocQuay);
    double sina = sin_rad(gocQuay);
    double indexX, indexY;
    //putpixel(diemQuayX, diemQuayY, color);//điểm quay
    //chuyển về gốc
    phepTinhTien(td, n, -diemQuayX, -diemQuayY);
    //thực hiện quay
    for (int i = 0; i<n; i++){
        indexX = (double) td[i].x * cosa - td[i].y * sina;
        indexY = (double) td[i].x * sina + td[i].y * cosa;
        td[i].x = round(indexX);
        td[i].y = round(indexY);
    }
    //tịnh tiến về chỗ cũ
    phepTinhTien(td, n, diemQuayX, diemQuayY);
}

//phép tỉ lệ có hệ số tỉ lệ x, y//nếu x = y thì là phép đồng dạng//nếu x = y = 1 thì là phép căng
void phepTiLe(TOADO td[], int n, double heSoTiLeX, double heSoTiLeY, int diemTiLeX, int diemTiLeY){
    //điểm tỉ lệ là điểm được giữ nguyên khi biến đổi tỉ lệ
    double indexX, indexY; //biến trung gian
    putpixel(diemTiLeX, diemTiLeY, color);//in điểm tỉ lệ
    //thực hiện tỉ lệ
    for (int i = 0; i<n; i++){ //chạy từ 0 đến n-2
        indexX = (double) (td[i].x - diemTiLeX) * heSoTiLeX;//tính khoảng cách của điểm x và tâm tỉ lệ sau đó nhân với hệ số tỉ lệ
        indexX = (double) diemTiLeX + indexX; //tính x
        td[i].x = round(indexX); //cập nhật lại điểm x

        indexY = (double) (td[i].y - diemTiLeY) * heSoTiLeY;//tính khoảng cách của điểm y và tâm tỉ lệ sau đó nhân với hệ số tỉ lệ
        indexY = (double) diemTiLeY + indexY; //tính y
        td[i].y = round(indexY); //cập nhật lại điểm y
    }
}

//phép đối xứng qua điểm x,y//là phép quay 180 độ
void phepDoiXungDiem(TOADO td[], int n, int diemDoiXungX, int diemDoiXungY){
    phepQuay(td, n, 180, diemDoiXungX, diemDoiXungY);
}


//---------------------------------------MENU--------------------------------------

void menu()
{
    printf("menu chuong trinh\n");
    printf("\t1.ve chuong trinh tinh tien\n");
    printf("\t2.ve chuong trinh phep quay\n");
    printf("\t3.ve chuong trinh co dan\n");
    printf("\t4.ve chuong trinh doi xung\n");
    printf("\t5 thoat menu \n");
}

// menu
void display()
{
    outtextxy(max_x - 650, max_y - 50,"CODE BUY DUONG VA THACH");
}
//---------------------------------------HÀM CHÍNH--------------------------------------
int main()
{
    initwindow(max_x, max_y);
    setcolor(color);
    setlinestyle(0,0,2);
    display();
    int n,x,y,a;
    int choose;
    TOADO td[10];
    int leng = soLuongPhanTu();
    do {
        printf("nhap so luong dinh: "); scanf("%d", &n);
        if (n<=0){
            printf("so luong dinh phai la so duong\n");
        }
        if (n>leng/2){
            printf("so luong dinh nhap lon hon so dinh trong file\n");
        }
        if (n > 0 && n<= leng/2){
            break;
        }
    }
    while (69);
    readFile(td, n);
    do
    {
        system("cls");
        menu();
        cleardevice();
        display();
        polygonDraw(td, n);
        printf("vui long chon: "); scanf("%d",&choose);
        switch (choose)
        {
        case 1:
            outtextxy(max_x - 200, 50,"chuong trinh tinh tien");
            display();
            printf("\nchuong trinh tinh tien\n");
            printf("nhap do roi cua x:");scanf("%d",&x);
            printf("nhap do roi cua y:");scanf("%d",&y);
            phepTinhTien(td, n, x, y);
            break;
        case 2:
            outtextxy(max_x - 200, 50,"chuong trinh phep quay");
            display();
            printf("\nchuong trinh phep quay\n");
            printf("nhap goc quay:");scanf("%d",&a);
            printf("nhap diem quay x: ");scanf("%d",&x);
            printf("nhap diem quay y: ");scanf("%d",&y);
            phepQuay(td, n, a, x, y); //quay tại điểm 0
            break;
        case 3:
            outtextxy(max_x - 200, 50,"chuong trinh phep co dan");
            display();
            float x1, y1;
            printf("\nchuong trinh phep co dan\n");
            printf("he so ti le x:");scanf("%f",&x1);
            printf("he so ti le y:");scanf("%f",&y1);
            phepTiLe(td, n, x1, y1, averageX(td, n), averageY(td, n));
            break;
        case 4:
            outtextxy(max_x - 200, 50,"chuong trinh phep doi xung");
            display();
            printf("\nchuong trinh phep doi xung\n");
            printf("\nnhap diem doi xung x: ");scanf("%d",&x);
            printf("\nnhap diem doi xung y: ");scanf("%d",&y);
            phepDoiXungDiem(td, n, x, y);
            outtextxy(max_x - 200, 50,"chuong trinh phep doi xung");
            display();
            break;
        case 5:
            break;
        default:
            printf("ko co trong menu\n");
        }
    }
    while(choose!=5);
    getch();
    closegraph();
    return 0;
}
