#include "MapInformation.h"

void MapInformation::initialize(int L) {
	existance = std::vector<bool>(L, false);
	CarID = std::vector<int>(L);
}