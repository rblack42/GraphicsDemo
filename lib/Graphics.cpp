#include "Graphics.h"
#include <cmath>
#include <time.h>

const double PI = acos(-1.0);
const double ANGLE_STEP      = PI/180.0;

// stupid utility functions; safe to ignore
double square(double x);
double wrapAngle(double angleRadians);

void setColor(ColorName name) {
    switch(name) {
        case WHITE: glColor3d(1.0, 1.0, 1.0); break;
        case GREY: glColor3d(0.4, 0.4, 0.4); break;
        case BLACK: glColor3d(0.0, 0.0, 0.0); break;
        case RED: glColor3d(1.0, 0.0, 0.0); break;
        case ORANGE: glColor3d(1.0, 0.5, 0.0); break;
        case YELLOW: glColor3d(1.0, 1.0, 0.0); break;
        case GREEN: glColor3d(0.0, 1.0, 0.0); break;
        case FOREST_GREEN: glColor3d(0.0, 0.25, 0.0); break;
        case BLUE: glColor3d(0.0, 0.0, 1.0); break;
        case CYAN: glColor3d(0.0, 1.0, 1.0); break;
        case MIDNIGHT_BLUE: glColor3d(0.0, 0.0, 0.25); break;
        case PURPLE: glColor3d(0.5, 0.25, 0.0); break;
        case MAGENTA: glColor3d(1.0, 0.0, 1.0); break;
        case BROWN: glColor3d(0.36, 0.16, 0.1); break;
        default: cerr << "Trying to set invalid color. Color unchanged" << endl;
    }
}

void graphicsSetup(int argc, char **argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	 glutInitWindowPosition(WINDOW_X,WINDOW_Y);
	 glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	 glutCreateWindow("COSC1315 - Graphics Lab");
	 glClearColor(1.0,1.0,1.0,0.0);
	 gluOrtho2D(0,WINDOW_WIDTH, 0,WINDOW_HEIGHT);
}

void clearWindow() {
     glClear(GL_COLOR_BUFFER_BIT);
}

void pause_ms( int milliseconds ) {
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while( clock() < time_end ){}
}

// drawing routines follow ----------------------------------------------------
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
     glBegin(GL_LINE_STRIP);
     glVertex2i(x1,y1);
     glVertex2i(x2,y2);
     glVertex2i(x3,y3);
     glVertex2i(x1,y1);
     glEnd();
}

void drawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
     glBegin(GL_POLYGON);
     glVertex2i(x1,y1);
     glVertex2i(x2,y2);
     glVertex2i(x3,y3);
     glVertex2i(x1,y1);
     glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
     glBegin(GL_LINE_STRIP);
     glVertex2i(x1,y1);
     glVertex2i(x2,y2);
     glEnd();
}

void drawBox(int x1, int y1, int x2, int y2) {
     glBegin(GL_LINE_STRIP);
     glVertex2i(x1,y1);
     glVertex2i(x2,y1);
     glVertex2i(x2,y2);
     glVertex2i(x1,y2);
     glVertex2i(x1,y1);
     glEnd();
}

void drawFilledBox(int x1, int y1, int x2, int y2) {
     glBegin(GL_POLYGON);
     glVertex2i(x1,y1);
     glVertex2i(x2,y1);
     glVertex2i(x2,y2);
     glVertex2i(x1,y2);
     glVertex2i(x1,y1);
     glEnd();
}

void drawCircle(int x, int y, int radius) {
     double angle;
     int X, Y;
     glBegin(GL_LINE_STRIP);
     for (angle=0;angle< 2.0*PI + ANGLE_STEP; angle += ANGLE_STEP) {
         X = x + int(double(radius) * cos(angle));
         Y = y + int(double(radius) * sin(angle));
         glVertex2i(X,Y);
     }
     glEnd();
}         

void drawFilledCircle(int x, int y, int radius) {
     double angle;
     int X0, Y0, X1, Y1;
     glBegin(GL_TRIANGLES);
     X1 = x + radius;
     Y1 = y;
     for (angle=0;angle< 2.0*PI + ANGLE_STEP; angle += ANGLE_STEP) {
         X0 = X1;
         Y0 = Y1;
         X1 = x + int(double(radius) * cos(angle));
         Y1 = y + int(double(radius) * sin(angle));
         glVertex2i(x,y);
         glVertex2i(X0,Y0);
         glVertex2i(X1,Y1);
     }
     glEnd();
}         

void drawOval(int x, int y, int width, int height, int rotateAngle) {
    double angle, rotateAngleRad = PI*rotateAngle/180.0;
    int X, Y, radius;
    double a = width * 0.5, b = height * 0.5;
    glBegin(GL_LINE_STRIP);
    for (angle=0;angle< 2.0*PI + ANGLE_STEP; angle += ANGLE_STEP) {
        radius = static_cast<int>((a*b)/sqrt(square(b*cos(angle-rotateAngleRad)) + 
                                             square(a*sin(angle-rotateAngleRad))));
        X = x + int(double(radius) * cos(angle));
        Y = y + int(double(radius) * sin(angle));
        glVertex2i(X,Y);
    }
    glEnd();
}

void drawFilledOval(int x, int y, int width, int height, int rotateAngle) {
    double angle, rotateAngleRad = PI*rotateAngle/180.0;
    int X0, Y0, X1, Y1, radius;
    double a = width * 0.5, b = height * 0.5;
    radius = static_cast<int>((a*b)/(sqrt(square(b*cos(-rotateAngleRad)) + 
                                          square(a*sin(-rotateAngleRad)))));
    X1 = x + int(double(radius) * cos(angle));
    Y1 = y + int(double(radius) * sin(angle));
    glBegin(GL_TRIANGLES);
    for (angle=0;angle< 2.0*PI + ANGLE_STEP; angle += ANGLE_STEP) {
        radius = static_cast<int>((a*b)/sqrt(square(b*cos(angle-rotateAngleRad)) + 
                                             square(a*sin(angle-rotateAngleRad))));
        X0 = X1;
        Y0 = Y1;
        X1 = x + int(double(radius) * cos(angle));
        Y1 = y + int(double(radius) * sin(angle));
        glVertex2i(x, y);
        glVertex2i(X0,Y0);
        glVertex2i(X1,Y1);
    }
    glEnd();
}


double square(double x) {
    return x*x;
}

double wrapAngle(double angleRadians) {
    double rads = angleRadians;
    while(rads > 2 * PI)
        rads -= 2 * PI;
    while(rads < 0)
        rads += 2 * PI;
    return rads;
}

void drawArc(int x, int y, int radius, int startAngle, int endAngle) {
    int X0, Y0;
    double startRadians = startAngle * PI / 180.0;
    double endRadians = endAngle * PI / 180.0;
    glBegin(GL_LINE_STRIP);
    for (double angle = startRadians; 
            fabs(angle-endRadians) >= ANGLE_STEP ; 
            angle = wrapAngle(angle + ANGLE_STEP)) {
        X0 = x + int(double(radius) * cos(angle));
        Y0 = y + int(double(radius) * sin(angle));
        glVertex2i(X0,Y0);
    }
    glEnd();
}
