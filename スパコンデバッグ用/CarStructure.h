#ifndef CARSTRUCTURE_H
#define CARSTRUCTURE_H
#include <vector>

class Car {
private:
	struct CurrentPrevious {
		std::vector<int> current;
		std::vector<int> previous;
	};
	struct FrontRearCarID {
		int front;
		int rear;
	};
public:
	struct Mesurement {
		bool merured;
		double elapsed;
	};
	CurrentPrevious velocity;
	CurrentPrevious position;
	CurrentPrevious distance;
	std::vector<int> S;
	std::vector<int> canditateVelocity;
	std::vector<FrontRearCarID> arround;
	std::vector<Mesurement> mesure;
	void initialize(int N);
	void copyCurrentToPrevious();
};

#endif // !CARSTRUCTURE_H

