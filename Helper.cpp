#include "Helper.hpp"
#include<set>
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

set<string> nonTerms = {"a","the","to","in","from","out","was","have","has","were","would","will","if","then","of","off","after","over","into","up"}; 
set<char> endPoints = {'.','!','?'};

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

void Helper::makeFreqVect() {
	vector<int> termsInSent;
	int sentNum = 0;
	while(!input.eof()){
		bool endOfSent = false;
		string word;
		input >> word;

		if(endPoints.find(word.back()) != endPoints.end()) {
			endOfSent = true;
		}
		
		if(nonTerms.find(word) == nonTerms.end()){
			Porter2Stemmer::stem(word);
			freq[word].push_back(sentNum);
		}

		if(endOfSent) 
			++sentNum;
	}
}

void Helper::makeCoocMatrix() {

	//choosing frequent terms
	vector<pair<string, int> > tmpFreq;
	for(auto it = freq.begin(); it != freq.end(); ++it) {
		tmpFreq.push_back(pair<string, int>(it->first, (it->second).size() ) );
	}
	sort(tmpFreq.begin(), tmpFreq.end(), [](const pair<string, int> &a, const pair<string, int> &b) -> bool {
		return a.second > b.second;	
	});

	int edge = 10;//= min(1000, 0.3*freq.size());

	//making co_o matrix
	for(int i = 0; i < edge; ++i) {
		for(int j = 0; j < edge; ++j) {
			string term1 = tmpFreq[i].first;
			string term2 = tmpFreq[j].first;
			if(i == j) {
				co_o[pair<string, string>(term1, term2)] = 0;
			} else {
				co_o[pair<string, string>(term1, term2)] = pairwiseCooc(freq[term1], freq[term2]);
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
		cout << it->first << " ";
		for(int i = 0; i < (it->second).size(); ++i) 
			cout << it->second[i] << " ";
		cout << "\n";
	}
	cout << "\n" << "\n" << "\n" << "\n";

	for(auto it = co_o.begin(); it != co_o.end(); ++it) {
		cout << (it->first).first << " " << (it->first).second << " " << it->second << "\n";
	}
}
