#include<iostream>
#include<tuple>
#include<fstream>
#include "Extractor.hpp"
#include<map>
#include<algorithm>

using namespace std;

int main() {

	string nameIn;
	cin >> nameIn;

	double alpha;
	cin >> alpha;

	ifstream in;
	in.open(nameIn);
	
	Helper helper(in);
	Extractor extractor(helper, alpha);
	extractor.extract();
	extractor.printChi();

}
