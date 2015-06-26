#include "Extractor.hpp"
#include<iostream>
#include<cmath>

using namespace std;

Extractor::Extractor(Helper& helper, double alpha) : helper(helper), alpha(alpha) {
	helper.help();	
}

double Extractor::chi(string& term) {
	double res = 0;
	double nomg = helper.totalCooc[term];
	for(auto& fterm : helper.freqTerms) {
		double pg = helper.termsProb[fterm.first];
		double freq = helper.pairCooc[{fterm.first, term}];
		res += pow((freq - pg*nomg), 2)/(pg*nomg);
	}
	return sqrt(res);
}

// compute chi of frequent terms and sort them
void Extractor::computeAllChi() {
	for(auto& term : helper.freqTerms) {
		termChis.push_back({term.first, chi(term.first)});
	}
	sort(termChis.begin(), termChis.end(), [](const pair<string, int>& a, const pair<string, int>& b){
		return a.second > b.second;	
	});
}

void Extractor::extract() {
	computeAllChi();
	for(int i = 0; i < termChis.size(); ++i) {
		if(termChis[i].second < alpha) {
			termChis.resize(i+1);
			break;
		}
	}
}

void Extractor::printChi() {
	for(auto& term : termChis) {
		cout << term.first << " " << term.second <<"\n";
	}
}
