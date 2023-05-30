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

	static void init() {

	}

	void draw()
	{
		glPushMatrix();
		glColor3f(culoareR, culoareG, culoareB);

		glTranslated(centru.getX(), centru.getY(), centru.getZ());
		glScalef(0.25, 0.5, 1);
		glutSolidCube(marime);
		glPopMatrix();

		glPushMatrix();
		glColor3f(culoareR, 0, culoareB);
		glTranslated(centru.getX(), centru.getY()+0.25, centru.getZ()+0.6);
		glScalef(0.1, 0.1, 0.2);
		glutSolidCube(marime);


		glPopMatrix();
	}

	void update() {
		/*
		using namespace std::chrono;
		uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		uint64_t delta_time = current_time - last_update;
		last_update = current_time;

		double delta_y = Scene::get_movement_speed() * delta_time;
		centru.setY(centru.getY() - delta_y);
		*/
	}

	Point get_pos() {
		return centru;
	}

	bool has_red_eyes() {
		return ochi_rosu;
	}


	void mouse(int button, int state, int x, int y) { ; }
};

