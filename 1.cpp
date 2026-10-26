//Bresenham.cpp
int main()
{
    int x, y, x1, y1, x2, y2, p, dx, dy;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");
    cout << "\nEnter the x-coordinate of the first point :: ";
    cin >> x1;
    cout << "\nEnter the y-coordinate of the first point :: ";
    cin >> y1;
    cout << "\nEnter the x-coordinate of the second point :: ";
    cin >> x2;
    cout << "\nEnter the y-coordinate of the second point :: ";
    cin >> y2;
    x = x1;
    y = y1;
    dx = x2 - x1;
    dy = y2 - y1;
    putpixel(x, y, 2);
    p = (2 * dy) - dx;
    while (x <= x2)
    {
        if (p < 0)
        {
            x = x + 1;
            p = p + (2 * dy);
        }
        else
        {
            x = x + 1;
            y = y + 1;
            p = p + (2 * dy) - (2 * dx);
        }
        putpixel(x, y, 7);
    }
    getch();
    closegraph();
    return 0;
}
Input: 
Enter the x-coordinate of the first point  :: 90
Enter the y-coordinate of the first point  ::120
Enter the x-coordinate of the second point ::200
Enter the y-coordinate of the second point ::220




    
//DDA.cpp
float myround(float a);
int main(){
    int gd = DETECT, gm;
    int x1, y1, x2, y2, steps, k;
    float xincr, yincr, x, y, dx, dy;
    cout << "enter x1,y1: ";
    cin >> x1 >> y1;
    cout << "enter x2,y2: ";
    cin >> x2 >> y2;
    initgraph(&gd, &gm, "");
    dx = x2 - x1; 
    dy = y2 - y1;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    xincr = dx / steps;
    yincr = dy / steps;
    x = x1;
    y = y1;
    for (k = 1; k <= steps; k++){
        delay(100);
        x += xincr;
        y += yincr;
        putpixel(myround(x), myround(y), WHITE);
    }
    outtextxy(200, 20, "DDA");
    outtextxy(x1 + 5, y1 - 5, "(x1,y1)");
    outtextxy(x2 + 5, y2 + 5, "(x2,y2)");
    getch();
    closegraph();
    return 0;
}
float myround(float a){
    int b = a + 0.5;
    return b;
}
Input: x1,y1:100 200; x2,y2:300 350

    
//Midpoint_circle.cpp
#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
using namespace std;
void draw_circle(int, int, int);
void symmetry(int, int, int, int);
int main()
{
    int xc, yc, R;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");
    cout << "Enter the center of the circle:\n";
    cout << "Xc = ";
    cin >> xc;
    cout << "Yc = ";
    cin >> yc;
    cout << "Enter the radius of the circle : ";
    cin >> R;
    draw_circle(xc, yc, R);
    getch();
    closegraph();
    return 0;
}
void draw_circle(int xc, int yc, int rad)
{
    int x = 0;
    int y = rad;
    int p = 1 - rad;
    symmetry(x, y, xc, yc);
    for (x = 0; y > x; x++)
    {
        if (p < 0)
            p += 2 * x + 3;
        else
        {
            p += 2 * (x - y) + 5;
            y--;
        }
        symmetry(x, y, xc, yc);
        delay(50);
    }
}
void symmetry(int x, int y, int xc, int yc)
{
    putpixel(xc + x, yc - y, GREEN);   // For pixel (x, y)
    delay(50);
    putpixel(xc + y, yc - x, GREEN);   // For pixel (y, x)
    delay(50);
    putpixel(xc + y, yc + x, GREEN);   // For pixel (y, -x)
    delay(50);
    putpixel(xc + x, yc + y, GREEN);   // For pixel (x, -y)
    delay(50);
    putpixel(xc - x, yc + y, GREEN);   // For pixel (-x, -y)
    delay(50);
    putpixel(xc - y, yc + x, GREEN);   // For pixel (-y, -x)
    delay(50);
    putpixel(xc - y, yc - x, GREEN);   // For pixel (-y, x)
    delay(50);
    putpixel(xc - x, yc - y, GREEN);   // For pixel (-x, y)
    delay(50);
}




// Midpoint_Ellipse.cpp
#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <math.h>
using namespace std;
void disp();
float x, y; int xc, yc;
int main()
{
    int gd = DETECT, gm;
    int rx, ry; float p1, p2; float dx, dy;
    initgraph(&gd, &gm, "");   
    cout << "Enter the center point (xc yc): ";
    cin >> xc >> yc;
    cout << "Enter the value for Rx and Ry: ";
    cin >> rx >> ry;
    x = 0; y = ry;
    disp();
    p1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;
    while (dx < dy){
        x++;
        dx = dx + (2 * ry * ry);
        if (p1 < 0){
            p1 = p1 + dx + (ry * ry);
        }
        else{
            y--;
            dy = dy - (2 * rx * rx);
            p1 = p1 + dx - dy + (ry * ry);
        }
        disp();
    }
    p2 = (ry * ry) * ((x + 0.5) * (x + 0.5)) + 
         (rx * rx) * ((y - 1) * (y - 1)) - 
         (rx * rx * ry * ry);
    while (y > 0){
        y--;
        dy = dy - (2 * rx * rx);
        if (p2 > 0){
            p2 = p2 - dy + (rx * rx);
        }
        else{
            x++;
            dx = dx + (2 * ry * ry);
            p2 = p2 + dx - dy + (rx * rx);
        }
        disp();
    }
    getch();
    closegraph();
}
void disp(){
    delay(30);
    putpixel(xc + x, yc + y, 10);
    putpixel(xc - x, yc + y, 10);
    putpixel(xc + x, yc - y, 10);
    putpixel(xc - x, yc - y, 10);
}

// TextFonts.cpp
#include <iostream>
#include <conio.h>
#include <graphics.h>
using namespace std;
int main()
{
    int gd = DETECT, gm;
    int x = 25, y = 25, font;
    initgraph(&gd, &gm, "");   
    for (font = 0; font <= 4; font++)
    {
        settextstyle(font, HORIZ_DIR, font + 1);  
        setcolor(font + 1);                      
        outtextxy(x, y, "text with different fonts");
        y = y + 25;
    }
    for (font = 0; font <= 2; font++)
    {
        settextstyle(font, VERT_DIR, font + 2);
        setcolor(font + 1);
        x = 250;
        y = 100;
        outtextxy(x, y, "text in vertical direction");
        y = y + 25;
    }
    getch();
    closegraph();
    return 0;
}


