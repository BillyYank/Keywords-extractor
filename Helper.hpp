#include"porter2_stemmer.h"
#include<fstream>
#include<vector>
#include<map>
/*
Steme, find phrases, extract frequent terms, create cooccurence matrix
*/
using namespace std;

class Helper {
public:
	Helper(ifstream& _input);
	void help();
	void print_co_o();
private:
	ifstream& input;
	map<string, vector<int> > freq;
	map<pair<string, string>, int> co_o;

	void makeFreqVect();
	void chooseFreq();
	void makeCoocMatrix();
};
