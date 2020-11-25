#ifndef INISIALIZESETTING_H
#define INISIALIZESETTING_H
#include <iostream>
#include <fstream>
#include "CarStructure.h"
#include "MapInformation.h"
#include "random.h"

class InisializeSetting {
private:
	struct ConstantValues {
		double per_cell;
		std::vector<int> Vmax;
		int G;
		int S;
		double r;
		double q;
		double p1;
		double p2;
		double p3;
		double p4;
	};

public:
	struct Statics {
		int CountNum;
		double AV;
	};
	int N;
	int L;
	int leadCar;
	Random *random;
	ConstantValues constants;
	Car car;
	MapInformation map;
	Statics results;
	void initialize();
private:
	void _setConstantValues();
	void _setInitializePosition();
};

#endif // !INISIALIZESETTING_H

