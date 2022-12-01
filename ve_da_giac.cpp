#include <stdio.h>
#include <graphics.h>
#include <string.h>

#define MAX_POINT 20

struct TOADO{
    int x;
    int y;
};

struct TOADO p[MAX_POINT];

char alphabet[MAX_POINT][2] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "K", "L", "M", "N", "O", "P", "Q", "Y", "Z"
};

void nhapDaGiac(int n){
    int i;
    for(i=0;i<n; i++){
        printf("\nNhap toa do dinh %d : ", i+1);
        printf("\n\tx[%d] = ", i+1); scanf("%d", &p[i].x);
        printf("\n\ty[%d] = ", i+1); scanf("%d", &p[i].y);
    }
    p[i].x=p[0].x;
    p[i].y=p[0].y;
}

void drawDaGiac(int n){
    settextstyle(0, 0, 2);
    for (int i = 0; i<n; i++){
        setcolor(i%15+1);
        outtextxy(p[i].x, p[i].y, alphabet[i]);
    }

    for (int i = 0; i<n; i++){
        setcolor(i%15+1);
        setlinestyle(0, 0, i%10);
        //outtextxy(p[i+1].x, p[i+1].y, alphabet[i+1]);
        line(p[i].x, p[i].y, p[i+1].x, p[i+1].y);
    }
}

int main(){
    initwindow(600, 700);
    int n;
    do{
        printf("nhap so dinh cua da giac : "); scanf("%d", &n);
    }
    while(n<3);
    nhapDaGiac(n);
    drawDaGiac(n);
    //printf("%s", alphabet[5]);
    getch();
    closegraph();
    return 0;
}
