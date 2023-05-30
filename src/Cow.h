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
#include "Point.h"
#include "Scene.h"
using namespace std;

class Cow : public Object
{
public:
	Point centru;
	double unghi_rotatie;
	int marime;
	double culoareR, culoareG, culoareB;
	bool ochi_rosu;

	Cow(double centru_x, double centru_y, double centru_z, double unghi_rotatie, double culoareR, double culoareG, double culoareB, bool ochi_rosu, int marime)
	{
		this->centru.setX(centru_x);
		this->centru.setY(centru_y);
		this->centru.setZ(centru_z);
		this->unghi_rotatie = unghi_rotatie;
		this->culoareR = culoareR;
		this->culoareG = culoareG;
		this->culoareB = culoareB;
		this->marime = marime;
		this->ochi_rosu = ochi_rosu;
	}

	void draw()
	{

		GLfloat culoare_primita[] = { 1, 1, 1, 0.5 };
		GLfloat culoare_negru[] = { 0, 0, 0, 1 };
		GLfloat culoare_rosu[] = { 1.0, 0.0, 0.0, 0.1 };

		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_primita);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_primita);
		glColor3f(1, 1, 1);
		//body
		glTranslated(centru.getX(), centru.getY() + 0.4, centru.getZ());
		glScalef(0.3, 0.4, 1);
		glutSolidCube(marime);
		glPopMatrix();
		//head
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_negru);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_negru);
		glTranslated(centru.getX(), centru.getY() + 0.65, centru.getZ() + 0.6);
		glScalef(0.2, 0.2, 0.4);
		glutSolidCube(marime);

		glPopMatrix();
		
		//legs 1
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(centru.getX() - 0.1, centru.getY(), centru.getZ() - 0.4);
		glScalef(0.1, 0.4, 0.2);
		glutSolidCube(marime);

		glPopMatrix();
		//legs 2
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(centru.getX() - 0.1, centru.getY(), centru.getZ() + 0.4);
		glScalef(0.1, 0.4, 0.2);
		glutSolidCube(marime);

		glPopMatrix();

		glPopMatrix();
		//legs 3
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(centru.getX() + 0.1, centru.getY(), centru.getZ() + 0.4);
		glScalef(0.1, 0.4, 0.2);
		glutSolidCube(marime);

		glPopMatrix();

		glPopMatrix();
		//legs 4
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(centru.getX() + 0.1, centru.getY(), centru.getZ() - 0.4);
		glScalef(0.1, 0.4, 0.2);
		glutSolidCube(marime);

		glPopMatrix();

		//horns 1
		glPushMatrix();
		if (ochi_rosu) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_rosu);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_rosu);
		}
		else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoare_primita);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_primita);
		}
		glTranslated(centru.getX(), centru.getY() + 0.85, centru.getZ() + 0.6);
		glScalef(0.1, 0.1, 0.1);
		glutSolidCube(marime);

		glPopMatrix();
	}

	void update()
	{
		
		using namespace std::chrono;
		uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		uint64_t delta_time = current_time - last_update;
		last_update = current_time;

		double delta_y = Scene::get_movement_speed() * delta_time;
		centru.setZ(centru.getZ() + delta_y);
		
	}

	Point get_pos()
	{
		return centru;
	}

	bool has_red_eyes()
	{
		return ochi_rosu;
	}

	void mouse(int button, int state, int x, int y) { ; }
};
