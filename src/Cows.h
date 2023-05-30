#pragma once

#include <ctime>
#include <vector>
#include <random>

#include "Object.h"
#include "Cow.h"
#include "Healthbar.h"
#include "Pahar.h"
#include "Point.h"
#include "Scene.h"
#include "Screen.h"

using namespace std;

bool intersectie_drept_cerc(Point& centru_drept, double w_drept, double l_drept, Point& centru_cerc, double r_cerc) {
	return false;
}

class Cows : public Object {
public:
	vector<Cow> cows;
	uint64_t last_spawn, spawn_wait;
	Cows() : last_spawn(0), spawn_wait(3000) { srand(time(NULL)); }

	void draw() {
		for (auto& cow : cows) {
			cow.draw();
		}
	}

	void update() {
		spawn_cow();
		for (auto& cow : cows) {
			cow.update();
		}

		for (int i = cows.size() - 1; i >= 0; i--) {
			if (cows[i].get_pos().getZ() > 10) {
				cows.erase(cows.begin()+i);
				continue;
			}
			shared_ptr<Pahar> pahar = dynamic_pointer_cast<Pahar>(Scene::get_object("zahar"));
			if (intersectie_drept_cerc(cows[i].centru, 0.3, 1, pahar->centru, 0.3)) {
				shared_ptr<Healthbar> healthbar = dynamic_pointer_cast<Healthbar>(Scene::get_object("zzz"));
				if (cows[i].has_red_eyes()) {
					if (healthbar->hp.size() == 0) {
						return;
					}
					// radu-> todo: cum se termina jocul?
					// licu-> am facut dar foarte prost scuze
					healthbar->hp.pop_back();
					if (!healthbar->hp.size()) {
						Scene::playing = FALSE;
					}
				}
				else {
					if (pahar->fill == 10) {
						pahar->fill = 0;
						healthbar->scor += 25;
						Scene::lvl += 1;
						Scene::movement_speed += 0.001;
					}
					pahar->fill += 1;
					healthbar->scor += cows[i].marime;
				}
				cows.erase(cows.begin() + i);
				break;
			}
		}
	}

	void mouse(int button, int state, int x, int y) { ; }

	void spawn_cow() {
		using namespace std::chrono;
		uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		if (current_time < last_spawn + spawn_wait) {
			return;
		}

		double spawn_pos = (rand() % 101 - 50) / 25.0;

		spawn_wait = rand() % 3000 + 1000 - 90 * max(10, Scene::lvl);

		last_spawn = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

		cows.push_back(Cow(spawn_pos, 0.25, -50, 0,
			(rand() % 100) / 99.0, (rand() % 100) / 99.0, (rand() % 100) / 99.0,
			(rand() % 4 == 0 ? true : false), 1));
	}
};