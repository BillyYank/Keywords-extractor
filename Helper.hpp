#include"porter2_stemmer.h"
#include<fstream>
#include<vector>
#include<map>
#include<set>
/*
Steme, find phrases, extract frequent terms, create cooccurence matrix
*/
using namespace std;

struct freqInfo{
	set<int> sntses;
	int num = 0; //??
};

class Helper {
friend class Extractor;
public:
	Helper(ifstream& input);
	void help();
	void printPairCooc();

protected:
	map<string, double> termsProb;
	map<string, int> totalCooc;
	map<pair<string, string>, int> pairCooc;
	vector<pair<string, int>> freqTerms;
private:
	ifstream& input;
	map<string, freqInfo> sentWithTerm;
	vector<int> sentSize;
	int nTotal;

	void makeSentWithTerm();
	void chooseFreq();
	void makePairCooc();
	void makeTermsProbAndTotalCooc();
};
