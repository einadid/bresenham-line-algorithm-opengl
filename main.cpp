#include <GL/glut.h>
#include <cmath>
#include <cstdio>
#include <cstring>
// Global Variables
int x_start, y_start, x_end, y_end;
int limit;
// Text Drawing
void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
}
// Grid Drawing
void drawGrid() {
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    for (int i = 0; i <= limit; i++) {
        glVertex2f(i, 0); glVertex2f(i, limit);
        glVertex2f(0, i); glVertex2f(limit, i);
    }
    glEnd();
}
// Axis Drawing
void drawAxis() {
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);    // X-axis
    glVertex2f(0, 0); glVertex2f(limit, 0);
    glColor3f(0, 0, 1);    // Y-axis
    glVertex2f(0, 0); glVertex2f(0, limit);
    glEnd();
    glLineWidth(1);
    // Axis Labels
    glColor3f(0, 0, 0);
    for (int i = 0; i <= limit; i++) {
        char num[10];
        sprintf(num, "%d", i);
        drawText(i - 0.1, -0.5, num);
        if (i > 0) drawText(-0.5, i - 0.1, num);
    }
}
void fillCell(int x, int y) {       // Fill Cell
    glColor4f(0.5, 0.9, 1.0, 0.6);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}
void plotPoint(int x, int y) {      // Plot Point
    fillCell(x, y);
    glColor3f(0, 0, 0);
    glPointSize(6);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}
// Bresenham Algorithm
void drawBresenham() {
    int x = x_start, y = y_start;
    int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);
    int sx = (x_end > x_start) ? 1 : -1;
    int sy = (y_end > y_start) ? 1 : -1;
    if (dx > dy) {            // Case 1: Slope < 1
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            plotPoint(x, y);

            if (p >= 0) {
                y += sy;
                p = p + 2 * dy - 2 * dx;
            } else {
                p = p + 2 * dy;
            }
            x += sx;
        }
    }
    else {                    // Case 2: Slope >= 1
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            plotPoint(x, y);

            if (p >= 0) {
                x += sx;
                p = p + 2 * dx - 2 * dy;
            } else {
                p = p + 2 * dx;
            }
            y += sy;
        }
    }
    glColor3f(1, 0, 0);      // Draw actual line
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x_start, y_start);
    glVertex2f(x_end, y_end);
    glEnd();
    glLineWidth(1);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawAxis();
    drawBresenham();
    glFlush();
}
void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-1, limit + 1, -1, limit + 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
int main(int argc, char** argv) {
    printf("Enter x_start y_start: ");
    scanf("%d %d", &x_start, &y_start);
    printf("Enter x_end y_end: ");
    scanf("%d %d", &x_end, &y_end);
    // Calculate limit
    int maxVal = x_start;
    if (y_start > maxVal) maxVal = y_start;
    if (x_end > maxVal) maxVal = x_end;
    if (y_end > maxVal) maxVal = y_end;
    limit = maxVal + 2;

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bresenham Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
