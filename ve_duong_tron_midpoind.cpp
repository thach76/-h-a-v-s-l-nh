//vẽ đường tròn bằng thuật toán midpoint
#include <stdio.h>
#include <graphics.h>

#define color 2
#define DELAY 10

//vẽ 8 điểm đối xứng nhau
//xc, yc là tâm của đường tròn
void put8pixel(int xc, int yc, int x, int y){
    putpixel(x + xc, y + yc, color);
    putpixel(x + xc, -y + yc, color);
    putpixel(-x + xc, y + yc, color);
    putpixel(-x + xc, -y + yc, color);
    putpixel(y + xc, x + yc, color);
    putpixel(y + xc, -x + yc, color);
    putpixel(-y + xc, x + yc, color);
    putpixel(-y + xc, -x + yc, color);
}

//hàm vẽ đường tròn
//xc, yc là tâm của đường tròn
//r là bán kính của đường tròn
void drawCircleMidpoint(int xc, int yc, int r){
    //p tại điểm đầu và x, y tại điểm đầu
    int p = 1 - r; //nếu là float thì là 5/4 -r
    int x = 0, y = r;

    //in điểm đầu tiên
    put8pixel(xc, yc, x, y);

    //thoát khi x>=y
    while (x<y){
        delay(DELAY);
        //p < 0 tức là midpoint nằm trong đường tròn và do đó y gần
        //với đường tròn hơn nên ta lấy y(i+1) = y(i)
        if (p<0){
            p = p + 2*x + 3;
        }
        //ngược lại
        else{
            p = p + 2*(x-y) + 5;
            y--;
        }
        //tiếp tục tính điểm tiếp theo
        x++;
        //vẽ 8 điểm đối xứng
        put8pixel(xc, yc, x, y);
    }
}

//hàm chính
int main(){
    initwindow(700, 700);
    drawCircleMidpoint(350, 350, 300);
    getch();
    closegraph();
    return 0;
}
