#include "Helper.hpp"

using namespace std;

class Extractor {
public:
	Extractor(Helper& helper, double alpha);
	void extract();
	void printChi();
private:
	vector<pair<string, double>> termChis;
	double chi(string& term);
	void computeAllChi();
	
	double alpha;
	Helper& helper;
};
