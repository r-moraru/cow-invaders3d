#pragma once
#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath>
#include <chrono>
#include <fstream>
#include "Object.h"
#include "Screen.h"
using namespace std;



class Strada : public Object {
private:
	// Punctul la care se imparte banda.
	// Banda e formata din doua linii care sunt translatate in jos.
	// Punctul de separare este initial la limita de sus a ecranului.
	// Cand punctul ajunge in limita de jos, liniile sunt resetate.
	// Poz banda este un procent din spatiul de pe ecran.
	double poz_banda;

public:
	Strada(double poz_banda) : poz_banda(poz_banda) { ; }

	void draw() {
		// asfalt
		GLfloat culoare_asfalt[] = { 0.06, 0.06, 0.06, 0.1 };
		glColor3f(0.1, 0.1, 0.1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_asfalt);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_asfalt);
		glBegin(GL_QUADS);
		glVertex3d(-2, 0, -100);
		glVertex3d(-2, 0, 5);
		glVertex3d(2, 0, 5);
		glVertex3d(2, 0, -100);
		glEnd();

		// iarba
		GLfloat culoare_iarba[] = { 0, 0.25, 0.0, 0.3 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_iarba);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_iarba);
		glColor3f(0, 1, 0);
		glBegin(GL_QUADS);
		glVertex3d(-2, 0, -100);
		glVertex3d(-2, 0, 5);
		glVertex3d(-100, 0, 5);
		glVertex3d(-100, 0, -100);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3d(2, 0, -100);
		glVertex3d(2, 0, 5);
		glVertex3d(100, 0, 5);
		glVertex3d(100, 0, -100);
		glEnd();
	}

	void update() {
		using namespace std::chrono;
		uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		uint64_t delta_time = current_time - last_update;
		last_update = current_time;

		double delta_y = Scene::get_movement_speed() * delta_time;

		poz_banda += delta_y;
		if (poz_banda >= 7 * 16) {
			poz_banda = 0;
		}
	}

	void mouse(int button, int state, int x, int y) { ; }
};