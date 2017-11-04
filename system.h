#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <memory>
#include <vector>

class CorrugatedSystem {
private:
	double dt;
	double dz;
	double length;
	int N;

	std::vector<double> E;
	std::vector<double> A;
	double inline get_z(int i) {
		return dz * i;
	}

	void advance_fields();

public:
	CorrugatedSystem(double dt0, double dx0, double length0);
	void initialize_field(const std::function<double(double, double)> & E_function,
			const std::function<double(double, double)> & E_der_function, double t);

	std::vector<double> get_field() {
		return E;
	}

	void iterate();
};

#endif /* SYSTEM_H_ */
