#include "InisializeSetting.h"

void InisializeSetting::initialize() {
	car.initialize(N);
	map.initialize(L);
	results.AV = 0;
	results.CountNum = 0;
	_setConstantValues();
	_setInitializePosition();
}

void InisializeSetting::_setConstantValues() {
	constants.per_cell = 5.6;
	//constants.Vmax = 5;
	constants.G = 15;
	constants.S = 2;
	constants.r = 0.99;
	constants.q = 0.99;
	constants.p1 = 0.99;
	constants.p2 = 0.99;
	constants.p3 = 0.98;
	constants.p4 = 0.01;
}

void InisializeSetting::_setInitializePosition() {
	std::vector<int> rem(L);
	constants.Vmax = std::vector<int>(N, 0);
	std::vector<int> tempVmaxdist(N, 0);
	for (int i = 0; i < N; i++) {
		if (i % 3 == 0) tempVmaxdist[i] == 4;
		else if (i % 3 == 1) tempVmaxdist[i] == 5;
		else tempVmaxdist[i] == 6;
	}
	for (int i = 0; i < L; i++) rem[i] = i;
	for (int i = 0; i < N; i++) {
		int tempVmax_size = tempVmaxdist.size() - 1;
		int rem_size = rem.size() - 1;
		int xrem = random->random(rem_size);
		int pickup_Vmax = random->random(tempVmax_size);
		int assignedVmax = tempVmaxdist[pickup_Vmax];
		int p = rem[xrem];
		std::iter_swap(rem.begin() + xrem, rem.end() - 1);
		std::iter_swap(tempVmaxdist.begin() + pickup_Vmax, tempVmaxdist.end() - 1);
		rem.pop_back();
		tempVmaxdist.pop_back();
		map.existance[p] = true;
		constants.Vmax[i] = assignedVmax;
	}
	int maxDistance = -1;
	int frontPosition = map.existance.size();
	int distance;
	int ID = 0;
	for (int i = map.existance.size() - 1; i >= 0; i--) {
		if (map.existance[i]) {
			car.position.current[ID] = car.position.previous[ID] = i;
			if (ID > 0) {
				car.arround[ID].front = ID - 1;
			}
			else {
				car.arround[ID].front = N - 1;
			}
			if (ID < N - 1) {
				car.arround[ID].rear = ID + 1;
			}
			else {
				car.arround[ID].rear = 0;
			}
			map.CarID[i] = ID;
			distance = frontPosition - i - 1;
			frontPosition = i;
			car.distance.current[ID] = car.distance.previous[ID] = distance;
			if (maxDistance < distance) {
				maxDistance = distance;
				leadCar = ID;
			}
			if (ID == N - 1) break;
			ID++;
		}
	}
	distance = frontPosition - car.position.current[0] + L - 1;
	car.distance.current[0] = car.distance.previous[0] = distance;
	if (maxDistance < distance) {
		maxDistance = distance;
		leadCar = 0;
	}
}