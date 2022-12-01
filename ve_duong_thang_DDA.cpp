#include <stdio.h>
#include <winbgim.h>
#define Round(a) (int)(a+0.5)   // lam tron so
#define DELAY 10
int color = 15;

void lineDDA(int x1, int y1, int x2, int y2){       // thuat toan DDA
    int x_unit = 1, Dx = x2 - x1, Dy = y2 - y1;     // Khoi tao cac gia tri ban dau
    int x = x1;
    float y = y1;
    float m = (float)Dy/Dx;     // he so goc m
    putpixel(x, Round(y), color);

    while(x < x2){
        delay(DELAY);  // thoi gian tre khi ve 1 diem anh
        x += x_unit;
        y += m;
        putpixel(x,Round(y), color);
    }
}
int main(){
    initwindow(700, 700);
    setcolor(5);
    //settextstyle(5,0,4);
    //outtextxy(250,20,"dieuninh1997");
    lineDDA(50,150, 300, 200);      // ve duong thang
//    line(50,150,400,400);
    delay(50000);
    return 0;
}
