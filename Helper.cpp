#include "Helper.hpp"
#include<set>
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

set<string> nonTerms = {"a","the","and","for","to","in","from","out","are","is","was","have","has","were","would","will","if","then","of","off","after","over","into","up"}; 
set<char> endPoints = {'.','!','?'};

bool notTerm(string& word) {
	return word.length() < 3 || nonTerms.find(word) != nonTerms.end();
}

int pairwiseCooc(vector<int>& a, vector<int>& b) {
	int i = 0, j = 0, res = 0;
	while(i < a.size() && j < b.size()) {
		if(i+1 < a.size()){
			if(a[i] == a[i+1]){
				++i;
				continue;
			}
		}

		if(j+1 < b.size()){
			if(b[j] == b[j+1]) {
				++j;
				continue;
			}
		}

		if(a[i] == b[j]) {
			++i;
			++j;
			++res;
			continue;
		} else if(a[i] < b[j]) {
			++i;
			continue;
		} else {
			++j;
			continue;
		}
	}
	return res;
}


Helper::Helper(ifstream& _input) : input(_input) {

}

// vector with sentences numbers with word occurence
void Helper::makeFreqVect() {
	int sentNum = 0;
	while(!input.eof()){
		bool endOfSent = false;
		string word;
		input >> word;

		if(endPoints.find(word.back()) != endPoints.end()) {
			endOfSent = true;
		}
		
		Porter2Stemmer::stem(word);
		if(!notTerm(word))
			freq[word].push_back(sentNum);

		if(endOfSent) 
			++sentNum;
	}
}

void Helper::makeCoocMatrix() {

	//choosing frequent terms
	vector<pair<string, int> > tmpFreq;
	for(auto it = freq.begin(); it != freq.end(); ++it) {
		if(it->second.size() > 3) {
			tmpFreq.push_back(pair<string, int>(it->first, it->second.size() ) );
		}
	}
	sort(tmpFreq.begin(), tmpFreq.end(), [](const pair<string, int> &a, const pair<string, int> &b) -> bool {
		return a.second > b.second;	
	});

	int edge = 0.3*tmpFreq.size();  // Number of frequent terms

	//making co_o matrix
	for(int i = 0; i < edge; ++i) {
		for(int j = 0; j < edge; ++j) {
			string term1 = tmpFreq[i].first;
			string term2 = tmpFreq[j].first;
			if(i == j) {
				co_o[{term1, term2}] = 0;
			} else {
				co_o[{term1, term2}] = pairwiseCooc(freq[term1], freq[term2]);
			}
		}
	}

}

void Helper::help() {
	makeFreqVect();
	makeCoocMatrix();
}

void Helper::print_co_o() {
	for(auto it = freq.begin(); it != freq.end(); ++it) {
		cout << it->first << " " << it->first.length() << " ";
		for(int i = 0; i < (it->second).size(); ++i) 
			cout << it->second[i] << " ";
		cout << "\n";
	}
	cout << "\n" << "\n" << "\n" << "\n";

	for(auto it = co_o.begin(); it != co_o.end(); ++it) {
		cout << (it->first).first << " " << (it->first).second << " " << it->second << "\n";
	}
}
