#include<string>

using namespace std;

class Word : public string {
public:
	bool operator ==(Word &word);
	void toLowCase();
};
