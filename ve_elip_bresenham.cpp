//vẽ đường tròn bằng thuật toán midpoint
#include <stdio.h>
#include <graphics.h>

#define color 2
#define DELAY 10

//vẽ đường elip qua 4 điểm đối xứng
void put4pixel(int xc, int yc, int x, int y){
    putpixel(x + xc, y + yc, color);
    putpixel(-x + xc, y + yc, color);
    putpixel(x + xc, -y + yc, color);
    putpixel(-x + xc, -y + yc, color);
}

//vẽ hình elip
void drawElip(int xc, int yc, int a, int b){
    //vẽ phần b
    float x = 0, y = b;
    float z1 = (float)(b*b)/(a*a);
    float z2 = 1/z1;
    float p = 2*z1 - 2*b + 1;
    put4pixel(xc, yc, x, y);
    while (z1 * (x/y) <= 1){

        if (p < 0){
            p += 2*z1*(2*x+3);
        }
        else{
            p += 2*z1*(2*x+3) + 4*(1-y);
            y--;
        }
        x++;
        put4pixel(xc, yc, x, y);
    }
    //vẽ phần a
    x = a, y = 0;
    p = 2*z2 - 2*a +1;
    put4pixel(xc, yc, x, y);
    while (z2 * (y/x) < 1){

        if (p < 0){
            p += 2*z2*(2*y+3);
        }
        else{
            p += 2*z2*(2*y+3) + 4*(1-x);
            x--;
        }
        y++;
        put4pixel(xc, yc, x, y);
    }

}

//hàm chính
int main(){
    initwindow(700, 700);
    drawElip(350, 350, 100, 64);
    getch();
    closegraph();
    return 0;
}
