#include<string>

using namespace std;

class Word : string {
public:
	bool operator ==(Word &word);
	void toLowCase();
};
