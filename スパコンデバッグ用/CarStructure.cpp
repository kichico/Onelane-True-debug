#include "CarStructure.h"

void Car::initialize(int N) {
	velocity.current = velocity.previous = std::vector<int>(N, 0);
	position.current = position.previous = std::vector<int>(N);
	distance.current = distance.previous = std::vector<int>(N);
	S = std::vector<int>(N);
	canditateVelocity = std::vector<int>(N);
	arround = std::vector<FrontRearCarID>(N);
	mesure = std::vector<Mesurement>(N);
}

void Car::copyCurrentToPrevious() {
	velocity.previous = velocity.current;
	position.previous = position.current;
	distance.previous = distance.current;
}