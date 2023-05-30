#pragma once
#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath>
#include <fstream>
using namespace std;


class Screen
{
private:
    static int w, h;

public:
    static int get_width()
    {
        return w;
    }

    static int get_height()
    {
        return h;
    }

    static void set_width(int new_w)
    {
        w = new_w;
    }

    static void set_height(int new_h)
    {
        h = new_h;
    }
};

int Screen::w, Screen::h;

void init(void)
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 200);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cow Invaders 2000");
    Screen::set_width(800);
    Screen::set_height(600);

    glClearColor(0.0, 0.0, 0.0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}