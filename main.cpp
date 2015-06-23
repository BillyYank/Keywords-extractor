#include "Word.hpp"
#include<iostream>
#include "porter2_stemmer.h"

using namespace std;

int main() {

	string word;
	while(1) {
		cin >> word;
		Porter2Stemmer::stem(word);
		cout << word << "\n";		
	}
}
