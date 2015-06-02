#include<stringi>
#include<regex>

using namespace std;

class Steamer {
public:
	Steamer();
	string steam(string& word);
private:
	regex regexConsnant;
	regex regexVovel;

};
