#include "system.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

const double z0 = 40;
const double width = 20;

double E_func(double t, double z) {
	if (abs(z - z0) < width) {
		return pow(cos(0.5 * M_PI * (t - z + z0)/width), 2) * cos(t - z);
	} else {
		return 0.0;
	}
}

double A_func(double t, double z) {
	if (abs(z - z0) < width) {
		return -pow(cos(0.5 * M_PI * (t - z + z0)/width), 2) * sin(t - z);
	} else {
		return 0.0;
	}
}

int main(int argc, char **argv) {
	CorrugatedSystem s(0.2, 0.2, 90);

	s.initialize_field(E_func, A_func, 0.0);

	for (int i = 0; i < 1000; i++) {
		auto E = s.get_field();
		char filename[100];
		sprintf(filename, "%03d.out", i);
		ofstream file(filename);
		for (auto el : E) {
			file << el << endl;
		}
		file.close();

		s.iterate();
	}
}
