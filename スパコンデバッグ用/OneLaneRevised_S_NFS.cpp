#include "OneLaneRevised_S_NFS.h"

OneLaneRevised_S_NFS::OneLaneRevised_S_NFS(int filenumber, int L) {
	this->filenumber = filenumber;
	this->L = L;
}

void OneLaneRevised_S_NFS::calculate() {
	std::string f1 = "Result/Local" + std::to_string(filenumber) + ".dat";
	std::string f2 = "Result/Global" + std::to_string(filenumber) + ".dat";
	const char* F1 = f1.c_str();
	const char* F2 = f2.c_str();
	std::ifstream ifs(F2);
	std::vector<bool> NFinished(L, false);
	if (ifs) {
		std::string SLine, S;
		while (std::getline(ifs, SLine)) {
			std::stringstream SS;
			SS << SLine;
			std::getline(SS, S, ',');
			int Val = stoi(S) - 1;
			NFinished[Val] = true;
		}
	}
	ifs.close();
	std::ofstream ofs1(F1, std::ios::app);
	std::ofstream ofs2(F2, std::ios::app);
	std::vector<int> NLists;
	for (int i = 0; i < NFinished.size(); i++) if (!NFinished[i]) NLists.push_back(i + 1);
#ifdef _OPENMP
#pragma omp parallel for schedule(guided)
#endif
	for (int i = 0; i < NLists.size(); i++) {
		int N = NLists[i];
		double rho = 1.0 * N / L;
		UpdatePosition *DoCal = new UpdatePosition(L, N, filenumber);
		DoCal->initialize();
		for (int i = 0; i < 1800; i++) {
			DoCal->decideVelocity();
			DoCal->updatePosition(false);
		}
		for (int i = 0; i < 300; i++) {
			DoCal->decideVelocity();
			DoCal->updatePosition(true);
		}
		double av, k;
		int Q = DoCal->results.CountNum - 1;
		if (Q > 1) {
			av = DoCal->results.AV / DoCal->results.CountNum;
			if (av > 0)	k = 1000 / 300 * Q / av;
			else k = 0;
		}
		else {
			Q = 0;
			av = k = 0;
		}
		ofs1 << k << "," << Q << std::endl;
		ofs2 << N << "," << rho << "," << Q << std::endl;
#ifdef _OPENMP
#pragma omp critical
#endif
		{
			std::cout << rho << ", " << Q << std::endl;
		}
		delete DoCal;
	}
	ofs1.close();
	ofs2.close();
}
