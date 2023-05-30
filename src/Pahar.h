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
#include "Point.h"
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include "Screen.h"
using namespace std;

double arie_triunghi(Point &A, Point &B, Point &C)
{
    return abs(A.getX() * B.getY() + B.getX() * C.getY() + C.getX() * A.getY() - C.getX() * B.getY() - B.getX() * A.getY() - A.getX() * C.getY()) / 2.0;
}
bool punct_in_triunghi(Point &A, Point &B, Point &C, Point &D)
{
    return abs(arie_triunghi(A, B, D) + arie_triunghi(A, C, D) + arie_triunghi(B, C, D) - arie_triunghi(A, B, C)) < 1;
}

bool punct_in_dreptunghi(Point &A, Point &B, Point &C, Point &D, Point &P)
{
    return punct_in_triunghi(A, B, C, P) || punct_in_triunghi(C, D, A, P);
}

class Pahar : public Object
{
public:
    Point centru;
    double jump_height;
    double jump_speed;
    double max_jump_speed;
    double x_speed;
    double fall_acceleration;
    int fill;

    Pahar(double x, double y, double z) : centru(x, y, z), jump_height(0), fill(3), max_jump_speed(0.0025),
                                jump_speed(0.0025), fall_acceleration(0.00001), x_speed(0) { ; }

    void draw()
    {
        glPushMatrix();

        glTranslated(centru.getX(), centru.getY() + jump_height, centru.getZ());
        glRotated(-90, 1.0f, 0.0f, 0.0f);

        // milk
        glDisable(GL_BLEND);
        glColor4f(1.0, 1.0, 1.0, 0.93);
        GLfloat culoare_lapte[] = {0.7, 0.7, 0.7, 0.1};
        GLfloat lapte_diffuse[] = { 1.0, 1.0, 1.0, 0.5 };
        GLfloat lapte_specular[] = { 1.0, 1.0, 1.0, 0.1 };

        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_lapte);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lapte_diffuse);

        glutSolidCylinder(0.27f, this->fill * 0.12f, 20, 1);

        // glass
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(208 / 255.0, 250 / 255.0, 249 / 255.0, 1.0);
        GLfloat culoare_pahar[] = { 208 / 255.0, 250 / 255.0, 249 / 255.0, 1 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_pahar);
        glutSolidCylinder(0.3f, 1.2f, 20, 1);

        glDisable(GL_BLEND);

        glPopMatrix();
    }

    void update()
    {
        if (jump_height <= 0)
        {
            jump_speed = max_jump_speed;
            jump_height = 0;
        }

        using namespace std::chrono;
        uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        uint64_t delta_time = current_time - last_update;
        last_update = current_time;

        jump_height += jump_speed * delta_time;
        jump_speed -= fall_acceleration * delta_time;

        double new_x = centru.getX() + x_speed * delta_time;
        new_x = clamp(new_x, (double) -2.0, (double) 2.0);
        centru.setX(new_x);

        Scene::camera_x_pos = centru.getX();
    }

    void mouse(int button, int state, int x, int y) { ; }

    void keyPress(int key, int x, int y)
    {
        switch (key)
        {
        case GLUT_KEY_LEFT:
            x_speed = -0.002 - 0.0002 * Scene::lvl;
            break;
        case GLUT_KEY_RIGHT:
            x_speed = 0.002 + 0.0002 * Scene::lvl;
              break;
        default:
            break;
        }
    };
    void keyUp(int key, int x, int y) { ; };

    bool contine_punct(Point punct)
    {
        Point A(0 + centru.getX(), 0 + centru.getY() + jump_height, 0);
        Point B(0 + centru.getX(), -150 + centru.getY() + jump_height, 0);
        Point C(-75 + centru.getX(), -150 + centru.getY() + jump_height, 0);
        Point D(-75 + centru.getX(), 0 + centru.getY() + jump_height, 0);
        return punct_in_dreptunghi(A, B, C, D, punct);
    }
};