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


class Hamburger : public Object
{
public:
    Point centru;
    double angle;

    Hamburger(double x, double y, double z) : centru(x, y, z), angle(0) { ; }

    void draw()
    {
        glPushMatrix();

        glTranslated(centru.getX(), centru.getY(), 0);
        // glScaled(0.3, 0.3, 1);
        glRotated(angle, 0, 0, 1);

        GLfloat culoare_hamburger[] = {1.0, 0, 0.0, 1.0};
        GLfloat culoare_hamburger_diffuse[] = { 1.0, 1, 1, 0.1 };
        glColor3f(1.0, 0.8, 0.0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_hamburger);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_hamburger_diffuse);
        glutSolidSphere(0.15, 20, 20);

        glPopMatrix();
    }

    void update()
    {
        using namespace std::chrono;
        uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        uint64_t delta_time = current_time - last_update;
        last_update = current_time;

        angle += 0.05 * delta_time;
        if (angle > 360)
        {
            angle = 0;
        }
        if (angle < 0)
        {
            angle = 360;
        }
        glutPostRedisplay();
    }
    void mouse(int button, int state, int x, int y) { ; }
};