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

int pairwiseCooc(set<int>& a, set<int>& b) {
	auto it = a.begin();
	auto jt = b.begin();
	int res = 0;
	while(it != a.end() && jt != b.end()) {
		if(*it == *jt) {
			++it;
			++jt;
			++res;
			continue;
		} else if(*it < *jt) {
			++it;
			continue;
		} else {
			++jt;
			continue;
		}
	}
	return res;
}


Helper::Helper(ifstream& input) : input(input) {
	nTotal = 0;
}

// vector with sentences numbers with word occurence
void Helper::makeSentWithTerm() {
	int sentNum = 0;
	sentSize.push_back(0);
	string word;
	while(input >> word){
		bool endOfSent = endPoints.find(word.back()) != endPoints.end();

		Porter2Stemmer::stem(word);
		sentWithTerm[word].sntses.insert(sentNum);
		sentWithTerm[word].num++;
		sentSize[sentNum]++;
		nTotal++;

		if(endOfSent){
			 ++sentNum;
			 sentSize.push_back(0);
		}
	}
}

// choose frequents
void Helper::chooseFreq() {
	for(auto& word : sentWithTerm) {
		freqTerms.push_back({word.first, word.second.num});
	}

	sort(freqTerms.begin(), freqTerms.end(), [](const pair<string, int> &a, const pair<string, int> &b) -> bool {
			return a.second > b.second;	
			});

	int edge = 0.3*freqTerms.size();  // Number of frequent terms
	freqTerms.resize(edge);
}

// makes co-occurence matrix of frequent terms
void Helper::makePairCooc() {

	//making co_o matrix
	for(auto& term1 : freqTerms) {
		for(auto& term2 : freqTerms) {
			if(term1.first == term2.first) {
				pairCooc[{term1.first, term2.first}] = 0;
			} else {
				pairCooc[{term1.first, term2.first}] = pairwiseCooc(sentWithTerm[term1.first].sntses, sentWithTerm[term2.first].sntses);
			}
		}
	}

}

// probability for each frequent term and terms number in sent with term
void Helper::makeTermsProbAndTotalCooc() {
	for(auto& term : freqTerms){
		int count = 0;
		for(int num : sentWithTerm[term.first].sntses) {
			count += sentSize[num];			
		}
		termsProb[term.first] = (double)count/nTotal;
		totalCooc[term.first] = count;
	}
}

void Helper::help() {
	makeSentWithTerm();
	chooseFreq();
	makePairCooc();
	makeTermsProbAndTotalCooc();

}

void Helper::printPairCooc() {
	for(auto it = freqTerms.begin(); it != freqTerms.end(); ++it) {
		cout << it->first << " " << it->second << "\n";
	}
	cout << "\n" << "\n" << "\n" << "\n";

	for(auto it = pairCooc.begin(); it != pairCooc.end(); ++it) {
		cout << (it->first).first << " " << (it->first).second << " " << it->second << "\n";
	}
}
