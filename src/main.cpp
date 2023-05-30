#define _USE_MATH_DEFINES

#include <windows.h>
#include <queue>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath>
#include <fstream>
#include "Cow.h"
#include "Cows.h"
#include "Hamburger.h"
#include "Scene.h"
#include "Screen.h"
#include "Pahar.h"
#include "Strada.h"
#include "Healthbar.h"
using namespace std;

bool game_loop()
{
    Scene::get_object("cows");
    return true;
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    init();

    shared_ptr<Healthbar> hbar = make_shared<Healthbar>(Healthbar(-0.35, 2.5, 0));

    shared_ptr<Strada> strada = make_shared<Strada>(Strada(0));

    shared_ptr<Cows> cows = make_shared<Cows>(Cows());
    // // shared_ptr<Line> line1 = make_shared<Line>(Line(Screen::get_width() / 2, 0, Screen::get_width() / 2, Screen::get_height() / 2));

    shared_ptr<Pahar> pahar = make_shared<Pahar>(Pahar(0, 0, 2));
    // shared_ptr<Cow> cow1 = make_shared<Cow>(Cow(150, 150, 0, 1, 1, 1, false, 5));
    // shared_ptr<Cow> cow2 = make_shared<Cow>(Cow(450, 450, 0, 0, 0, 0, true, 10));
    shared_ptr<Cow> cow = make_shared<Cow>(Cow(-1, 0.5, 0, 0, 1, 1, 1, true, 1));

    Scene::add_object("strada", strada);
    // Scene::add_object("cow", cow);
    Scene::add_object("tcows", cows);
    Scene::add_object("zahar", pahar);
    // Scene::add_object("cow", cow);

    Scene::add_object("zzz", hbar);

    glutDisplayFunc(Scene::draw);
    glutIdleFunc(Scene::update);
    glutReshapeFunc(reshape);
    glutMouseFunc(Scene::mouse);
    glutSpecialFunc(Scene::keyPress);
    glutSpecialUpFunc(Scene::keyUp);

    glEnable(GL_DEPTH_TEST);

    Scene::background = SOIL_load_OGL_texture
    (
        "background.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MIPMAPS
    );

    glutMainLoop();
}