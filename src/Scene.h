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
#include "Object.h"
#include "Healthbar.h"
#include "Screen.h"
using namespace std;

void LoadTexture(void)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height;
    unsigned char* image = SOIL_load_image("nt.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // SOIL_free_image_data(image);
    // glBindTexture(GL_TEXTURE_2D, 0);

}

class Scene
{
private:
    static map<string, shared_ptr<Object>> objects;
public:
    static double movement_speed;
    static int lvl;
    static bool playing;

    static double camera_x_pos;
    static GLuint background;

    static void add_object(const string name, shared_ptr<Object> obj)
    {
        objects[name] = obj;
    }

    static void update(void) {
        for (auto& object : objects) {
            object.second->update();
        }
        glutPostRedisplay();
    }

    static void mouse(int button, int state, int x, int y)
    {
        for (auto& object : objects)
        {
            object.second->mouse(button, state, x, y);
        }
    }

    static void drawSky(void) {
        
        double skyboxSize = -70.0;
        
        glPushMatrix();
        glRotated(180, 1, 0, 0);
        glColor3f(0, 0, 0);
        GLfloat culoare_bg[] = { 1.0, 1.0, 1.0, 1 };

        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_bg);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_bg);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-skyboxSize + Scene::camera_x_pos, 0, -skyboxSize);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyboxSize + Scene::camera_x_pos, skyboxSize/3, -skyboxSize);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(skyboxSize + Scene::camera_x_pos, skyboxSize/3, -skyboxSize);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(skyboxSize + Scene::camera_x_pos, 0, -skyboxSize);
        glEnd();

        glPopMatrix();
        glFlush();
    }

    static void draw(void)
    {
        float lx = 0.0f, lz = -1.0f;
        // XZ position of the camera
        float x = 0.0f, z = 5.0f;

        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        gluLookAt(camera_x_pos, 2.0f, z,
            camera_x_pos + lx, 1.75f, z + lz,
            0.0f, 1.0f, 0.0f);

        drawSky();
        if (playing) {

            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            GLfloat light_position[] = { 0.0, 100.0, 100.0, 0.0 };
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);

            for (auto& object : objects)
            {
                object.second->draw();
            }

            // super urat, imi cer scuze la domnul programator
            shared_ptr<Healthbar> healthbar = dynamic_pointer_cast<Healthbar>(Scene::get_object("zzz"));
            char str[20];
            glColor3f(1.0, 1.0, 1.0);
            snprintf(str, sizeof(str), "SCORE: %d", healthbar->scor);
            Scene::displayText(10, Screen::get_height()-32, str);

            snprintf(str, sizeof(str), "LEVEL: %d", lvl);
            Scene::displayText(10, Screen::get_height() - 64, str);
        }
        else {
            glClearColor(0, 0, 0, 1);
            glColor3f(1.0, 0.1, 0.1);
            Scene::displayText(Screen::get_width() / 2 - 50, Screen::get_height() / 2, "YOU DIED");
            shared_ptr<Healthbar> healthbar = dynamic_pointer_cast<Healthbar>(Scene::get_object("zzz"));
            char str[20];
            snprintf(str, sizeof(str), "SCORE: %d", healthbar->scor);
            Scene::displayText(0, 0, str);
        }

        glutSwapBuffers();
        glFlush();
    }

    static shared_ptr<Object> get_object(const string name)
    {
        if (objects.find(name) == objects.end())
        {
            return nullptr;
        }

        return objects[name];
    }

    static void keyPress(int key, int x, int y) {
        for (auto& object : objects)
        {
            object.second->keyPress(key, x, y);
        }
        glutPostRedisplay();
    }

    static void keyUp(int key, int x, int y) {
        for (auto& object : objects)
        {
            object.second->keyUp( key, x, y);
        }
    }

    static int get_objects_len(void)
    {
        return objects.size();
    }

    static double get_movement_speed(void) {
        return movement_speed;
    }


    static void displayText(float x, float y, const char* text) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glRasterPos2f(x, y);

        for (int i = 0; i < strlen(text); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

};



map<string, shared_ptr<Object>> Scene::objects;
double Scene::movement_speed = 0.005;
bool Scene::playing = TRUE;
int Scene::lvl = 1;
double Scene::camera_x_pos = 0;
GLuint Scene::background = 0;