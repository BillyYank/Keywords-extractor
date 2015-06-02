#include "Word.hpp"
#include<iostream>
#include<locale>

using namespace std;

void Word::toLowCase() {
	locale loc;
	for (auto it = this->begin(); it != this->end(); ++it) {
		*it = tolower(*it, loc); 
	}
}

bool Word::operator ==(Word &word) {
	//TODO
	return (string)(*this) == (string)word;
}
