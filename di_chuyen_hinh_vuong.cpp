#include <stdio.h>
#include <graphics.h>

#define color 2

void drawHCN(int x1, int y1, int x2, int y2){
    int m = 23, n = 10;
    setcolor(color);
    setlinestyle(0, 0, 5);
    settextstyle(0, 0, 2);
    outtextxy(x1 - m, y1 - n, "A");
    outtextxy(x2 + n, y1 - n, "B");
    outtextxy(x2 + n, y2 - n, "C");
    outtextxy(x1 - m, y2 - n, "D");
    rectangle(x1, y1, x2, y2);
}

void diChuyenHCN(int x1, int y1, int x2, int y2){
    int i=0, j=0;
    char c;
    do{
        drawHCN(x1 + j, y1 + i, x2 + j, y2 + i);//vẽ hình vuông
        c = getch();
        if (c == 0){
            continue;
        }
        if (c == 72) i--;//lên
        else if(c == 80) i++;//xuống
        else if(c == 75) j--;//trái
        else if(c == 77) j++;//phải
        cleardevice();
    }
    while(c != 27);//27 = asc
}

int main(){
    initwindow(700, 700);
    diChuyenHCN(100, 100, 300, 300);
    getch();
    closegraph();
    return 0;
}
