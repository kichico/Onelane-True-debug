#ifndef MAPINFORMATION_H
#define MAPINFORMATION_H
#include <vector>

class MapInformation {
public:
	std::vector<bool> existance;
	std::vector<int> CarID;
	void initialize(int L);
};

#endif // !MAPINFORMATION_H

