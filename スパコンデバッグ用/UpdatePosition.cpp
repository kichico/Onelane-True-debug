#include "UpdatePosition.h"

UpdatePosition::UpdatePosition(int L, int N, int filenumber) {
	this->N = N;
	this->L = L;
	random = new Random();
}

UpdatePosition::~UpdatePosition() {
	delete random;
}

void UpdatePosition::updatePosition(bool DoMesure) {
	this->DoMesure = DoMesure;
	sumVelocity = 0;
	car.copyCurrentToPrevious();
	car.velocity.current = std::vector<int>(N, 0);
	int front = car.arround[leadCar].front;
	bool fg = true;
	int sumV = maximumSumV;
	while (fg) {
		existance = std::vector<bool>(L, false);
		CarID = std::vector<int>(L);
		if (DoMesure) {
			next_mesurement = car.mesure;
			next_statics = results;
		}
		existance[car.position.current[front]] = true;
		CarID[car.position.current[front]] = front;
		sumV = _updatePosition();
		if (sumVelocity == sumV) fg = false;
		else sumVelocity = sumV;
	}
	map.existance = existance;
	map.CarID = CarID;
	leadCar = nextLeadCar;
	if (DoMesure) {
		car.mesure = next_mesurement;
		results = next_statics;
	}
}

int UpdatePosition::_updatePosition() {
	int sumV = 0;
	int ID = leadCar;
	maximuDistance = -1;
	for (int i = 0; i < N; i++) {
		_moveForward(ID);
		if (DoMesure) {
			//以下，計測パート
			if (car.mesure[ID].merured) {
				if (car.position.previous[ID] < 28 && 28 <= car.position.current[ID]) {
					next_mesurement[ID].merured = false;
					double time = next_mesurement[ID].elapsed + 1.0 * (28 - car.position.previous[ID]) / car.velocity.current[ID];
					next_mesurement[ID].elapsed = 0;
					next_statics.CountNum++;
					next_statics.AV += 18 * constants.per_cell / time;
				}
				else {
					next_mesurement[ID].elapsed += 1;
				}
			}
			else {
				if (car.position.previous[ID] < 10 && 10 <= car.position.current[ID]) {
					next_mesurement[ID].merured = true;
					next_mesurement[ID].elapsed = 1.0 * (10 - car.position.previous[ID]) / car.velocity.current[ID];
				}
			}
		}
		sumV += car.velocity.current[ID];
		ID = car.arround[ID].rear;
	}
	return sumV;
}

void UpdatePosition::_moveForward(int ID) {
	if (car.velocity.current[ID] < car.canditateVelocity[ID]) {
		int front = car.arround[ID].front;
		int nextPosition = car.position.previous[ID];
		int v = 0;
		for (int i = 0; i < car.canditateVelocity[ID]; i++) {
			nextPosition++;
			if (nextPosition == L) nextPosition -= L;
			if (existance[nextPosition]) {
				if (CarID[nextPosition] == front) {
					nextPosition--;
					if (nextPosition < 0) nextPosition += L;
					break;
				}
			}
			v++;
		}
		car.velocity.current[ID] = v;
		car.position.current[ID] = nextPosition;
		existance[nextPosition] = true;
		CarID[nextPosition] = ID;
		int nextDistance;
		if (car.position.current[front] <= nextPosition) {
			nextDistance = car.position.current[front] - nextPosition + L - 1;
		}
		else {
			nextDistance = car.position.current[front] - nextPosition - 1;
		}
		car.distance.current[ID] = nextDistance;
		if (nextDistance > maximuDistance) {
			maximuDistance = nextDistance;
			nextLeadCar = ID;
		}
	}
	else {
		int position = car.position.current[ID];
		existance[position] = true;
		CarID[position] = ID;
	}
}
