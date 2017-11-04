#include "system.h"
#include <iostream>

CorrugatedSystem::CorrugatedSystem(double dt0, double dx0, double length0) :
		dt { dt0 }, dz { dx0 }, length { length0 } {
	N = (unsigned) (length / dz) + 1;
	A = std::vector<double>(N);
	E = std::vector<double>(N);
}

void CorrugatedSystem::initialize_field(const std::function<double(double, double)> & E_function,
		const std::function<double(double, double)> & A_function, double t) {

	for (auto i = 0; i < N; i++) {
		E[i] = E_function(t, get_z(i));
		A[i] = A_function(t - 0.5 * dt, get_z(i));
	}
}

void CorrugatedSystem::advance_fields() {
	for (int i = 0; i < N; i++) {
		A[i] += -dt * E[i];
	}

	for (int i = 1; i < N-1; i++) {
		E[i] += dt * (2 * A[i] - A[i+1] - A[i-1]) / dz / dz;
	}

	E[0] = (A[0] - A[1]) / dz;
	E[N-1] = (A[N-1] - A[N-2]) / dz;
}

void CorrugatedSystem::iterate() {
	advance_fields();
}
