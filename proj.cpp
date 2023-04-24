#include "./freeglut-MinGW-3.0.0-1.mp/freeglut.h"

#include <stdio.h>
#include <bits/stdc++.h>
#include <GL/glut.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

#include <string.h>

#define AMMO 100
#define AMMO2 100
#define MOVEACCELERATION 0.02
#define FIRESPEED 0.06
#define REFRESH 20
#define COMPRANGE 1
#define DAMAGE 0.01

double speed = 0, speed2 = 0, xbat = -0.1, ybat = -0.8, xfire[AMMO], powercom = 0.4, powercom2 = 0.4, yfire[AMMO], xdist = 0.008, ydist = 0.007, x, y,
       x1 = -0.98, xtwoplayer = 0.71, xcomfire[AMMO2], ycomfire[AMMO2], firespeed = 100;
int i, j, numoffire = 0, fireVisible[AMMO], numofcomfire = 0,
          comfirevisible[AMMO2], REFRESH2 = 0, gameOver = 10;
char xd = 'r', yd = 'u';
void printString(char print[], int Stringlenght, double stringX, double stringY, int size)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(stringX, stringY, 0);
    glScaled(0.00001 * size, 0.00001 * size, 0.00001 * size);
    for (i = 0; i < Stringlenght; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, print[i]);
}

void Timer(int Value)
{

    for (i = 0; i < AMMO; i++)
    {
        yfire[i] += FIRESPEED;
    }
    for (i = 0; i < AMMO2; i++)
    {
        ycomfire[i] -= FIRESPEED;
    }
    if (xbat < -0.96)
    {
        xbat = -0.96;
        speed = 0;
    }
    if (xbat > 0.69)
    {
        xbat = 0.69;
        speed = 0;
    }
    if (ybat > -0.2)
    {
        ybat = -0.2;
        speed2 = 0;
    }
    if (ybat < -1.0)
    {
        ybat = -1.0;
        speed2 = 0;
    }
    xbat = xbat + speed;
    ybat = ybat + speed2;
    if (speed >= 0.0004)
    {
        speed = speed - 0.002;
    }
    else if (speed <= (-0.0004))
    {
        speed = speed + 0.002;
    }
    else
        speed = 0;
    if (speed2 >= 0.0004)
    {
        speed2 = speed2 - 0.002;
    }
    else if (speed2 <= (-0.0004))
    {
        speed2 = speed2 + 0.002;
    }
    else
        speed2 = 0;
    glutPostRedisplay();
    if (gameOver == 0)
        glutTimerFunc(REFRESH, Timer, 0);
    REFRESH2 += REFRESH;
    if (xbat + COMPRANGE >= x && xbat - COMPRANGE <= x)
    {
        if (REFRESH2 >= firespeed)
        {
            xcomfire[numofcomfire % AMMO2] = x;
            ycomfire[numofcomfire % AMMO2] = y;
            comfirevisible[numofcomfire % AMMO2] = 1;
            numofcomfire++;
            REFRESH2 = 0;
        }
    }
}

void keyboard(unsigned char Key, int x, int y)
{
    switch (Key)
    {
    case 13:
        gameOver = 0;
        glutTimerFunc(REFRESH, Timer, 0);
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
    case 'd':
        speed = speed + MOVEACCELERATION;
        x1 = -0.95;
        xtwoplayer = 0.60;
        break;
    case 'a':
        speed = speed - MOVEACCELERATION;
        x1 = -0.72;
        xtwoplayer = 0.38;
        break;
    case 'w':
        speed2 = speed2 + MOVEACCELERATION;
        x1 = -0.58;
        xtwoplayer = 0.22;
        break;
    case 's':
        speed2 = speed2 - MOVEACCELERATION;
        x1 = -0.42;
        xtwoplayer = 0.14;
        break;
    case 32:
        xfire[numoffire % AMMO] = xbat;
        yfire[numoffire % AMMO] = ybat;
        fireVisible[numoffire % AMMO] = 1;
        x1 = -0.19;
        numoffire++;
        xtwoplayer = 0.1;
        break;
    }
}

void Display()
{
    if (gameOver == 0)
    {
        if (xd == 'r')
            x = x + xdist;
        else if (xd == 'l')
            x = x - xdist;
        if (yd == 'd')
            y = y - ydist;
        else if (yd == 'u')
            y = y + ydist;
        if (x < x1)
            xd = 'r';
        else if (x > xtwoplayer)
        {
            xd = 'l';
        }
        if (y > 0.2)
            yd = 'd';
        else if (y < -0.5)
            yd = 'u';
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT);
        glTranslated(xbat, ybat, 0);
        glColor3d(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2d(-0.04, 0.025);
        glVertex2d(-0.04, -0.025);
        glVertex2d(0.09, -0.025);
        glVertex2d(0.09, 0.025);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2d(0.02, 0.20);
        glVertex2d(-0.01, 0.0);
        glVertex2d(0.06, 0.0);
        glEnd();
        glLoadIdentity();
        glTranslated(x, y, 0);
        glBegin(GL_POLYGON);
        glColor3d(1.0f, 0.0f, 0.0f);
        glVertex2d(-0.04, 0.8);
        glVertex2d(-0.04, 0.75);
        glVertex2d(0.09, 0.75);
        glVertex2d(0.09, 0.8);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2d(0.02, 0.55);
        glVertex2d(-0.01, 0.8);
        glVertex2d(0.06, 0.8);
        glEnd();
        glLoadIdentity();
        glColor3d(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex2d(0.8, -1.0);
        glVertex2d(0.8, 1.0);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(-1.0, 0.0);
        glVertex2d(1.0, 0.0);
        glEnd();
        glLoadIdentity();
        glTranslated(0.9, 0.5, 0);
        glColor3d(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2d(-0.08, powercom);
        glVertex2d(-0.08, -0.4);
        glVertex2d(0.08, -0.4);
        glVertex2d(0.08, powercom);
        glEnd();
        glLoadIdentity();
        glTranslated(0.9, 0.5, 0);
        glColor3d(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2d(-0.08, 0.4);
        glVertex2d(-0.08, -0.4);
        glVertex2d(0.08, -0.4);
        glVertex2d(0.08, 0.4);
        glEnd();
        glLoadIdentity();
        glTranslated(0.9, -0.5, 0);
        glColor3d(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2d(-0.08, powercom2);
        glVertex2d(-0.08, -0.4);
        glVertex2d(0.08, -0.4);
        glVertex2d(0.08, powercom2);
        glEnd();
        glLoadIdentity();
        glTranslated(0.9, -0.5, 0);
        glColor3d(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2d(-0.08, 0.4);
        glVertex2d(-0.08, -0.4);
        glVertex2d(0.08, -0.4);
        glVertex2d(0.08, 0.4);
        glEnd();
        for (i = 0; i < AMMO; i++)
        {
            if (fireVisible[i] == 1)
            {
                glLoadIdentity();
                glColor3d((double)91 / 255, (double)226 / 255,
                          (double)255 / 255);
                glTranslated(xfire[i] + 0.02, yfire[i] + 0.09, 0);
                glutSolidSphere(0.01, 10, 10);
            }
        }
        for (i = 0; i < AMMO2; i++)
        {
            if (comfirevisible[i] == 1)
            {
                glLoadIdentity();
                glColor3d((double)91 / 255, (double)226 / 255,
                          (double)255 / 255);
                glTranslated(xcomfire[i] + 0.025, ycomfire[i] + 0.55, 0);
                glutSolidSphere(0.01, 10, 10);
            }
        }
        for (i = 0; i < AMMO; i++)
        {
            if (fireVisible[i] == 1 && (x < xfire[i] + 0.09 && x > xfire[i] - 0.09) && y + 0.7 > yfire[i] && y + 0.5 < yfire[i])
            {
                if (powercom > -0.4)
                {
                    powercom = powercom - DAMAGE;
                    fireVisible[i] = 0;
                }
                else if (powercom <= 0.4)
                {
                    gameOver = 2;
                }
            }
        }
        for (i = 0; i < AMMO2; i++)
        {
            if (comfirevisible[i] == 1 && xbat < xcomfire[i] + 0.09 && xbat > xcomfire[i] - 0.09 && ybat - 0.3 > ycomfire[i] && ybat - 0.5 < ycomfire[i])
            {
                if (powercom2 > -0.4)
                {
                    powercom2 = powercom2 - DAMAGE - 0.05;
                    comfirevisible[i] = 0;
                }
                else if (powercom2 <= -0.4)
                {
                    gameOver = 3;
                    printf("Computer %d", gameOver);
                }
            }
        }
    }
    glColor3d(1.0f, 1.0f, 1.0f);
    printString(" POWER", 6, 0.79, 0.04, 32);
    printString(" POWER", 6, 0.79, -0.96, 32);
    printString("COMPUTER", 8, 0.812, 0.94, 26);
    printString(" YOU", 4, 0.816, -0.06, 32);
    if (gameOver == 2)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3d(0.0f, 1.0f, 0.0f);
        printString("YOU WON", 7, -0.25, 0, 80);
    }
    else if (gameOver == 3)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3d(0.0f, 1.0f, 0.0f);
        printf("Computer %d string", gameOver);
        printString("COMPUTER WON", 12, -0.45, 0, 80);
    }
    else if (gameOver == 10)
    {
        glColor3d((double)0 / 255, (double)217 / 255, (double)11 / 255);
        glClear(GL_COLOR_BUFFER_BIT);
        printString("SPACESHOOTER", 12, -0.7, 0.8, 150);
		printString("Developer : Ritik Puri, Abhinav Singh,",strlen("Developer : Ritik Puri, Abhinav Singh,"), -1.0, 0.6, 60);
    printString("        Manav Singh Kainth",strlen("        Manav Singh Kainth"), -1.0, 0.48, 60);
		printString("Submitted to : Amrita Kaur",
                    strlen("Submitted to : Amrita Kaur"), -1.0, 0.35, 60);        printString("Controls : ", strlen("Controls : "), -1.0, 0.2, 60);
        printString("1) w : Front", strlen("1) w : Front"), -0.63, 0.1, 60);
        printString("2) s : Back", strlen("2) s : Back"), -0.63, 0.0, 60);
        printString("3) a : Left", strlen("3) a : Left"), -0.63, -0.1, 60);
        printString("4) d : Right", strlen("4) d : Right"), -0.63, -0.2, 60);
        printString("5) Space : Fire", strlen("5) Space : Fire"), -0.63, -0.3,
                    60);
        printString("6) Esc : Exit", strlen("6) Esc : Exit"), -0.63, -0.4, 60);
        printString("Game : Kill the Computer Ship.",
                    strlen("Game : Kill the Computer Ship."), -1.0, -0.6, 60);
        printString("Press Enter to play game.",
                    strlen("Press Enter to play game."), -1.0, -0.8, 60);
    }
    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    for (j = 0; j < AMMO; j++)
    {
        fireVisible[j] = 0;
    }
    for (j = 0; j < AMMO2; j++)
    {
        comfirevisible[j] = 0;
    }
    gameOver = 10;
    glutInit(&argc, argv);
    glutInitWindowSize(1440, 920);
    glutInitWindowPosition(200, 300);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("Space Shooter ");
    glutFullScreen();
    glutDisplayFunc(Display);
    glutTimerFunc(0, Timer, 0);
    glutKeyboardFunc(keyboard);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
    return 0;
}
}

