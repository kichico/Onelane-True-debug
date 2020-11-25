#ifndef UPDATEPOSITION_H
#define UPDATEPOSITION_H
#include "DecideVelocityCanditate.h"

class UpdatePosition : public DecideVelocityCanditate {
public:
	UpdatePosition(int L, int N, int filenumber);
	~UpdatePosition();
	void updatePosition(bool DoMesure);
private:
	bool DoMesure;
	int nextLeadCar;
	int maximuDistance;
	int sumVelocity;
	std::vector<bool> existance;
	std::vector<int> CarID;
	std::vector<Car::Mesurement> next_mesurement;
	Statics next_statics;
	int _updatePosition();
	void _moveForward(int ID);
};

#endif // !UPDATEPOSITION_H

