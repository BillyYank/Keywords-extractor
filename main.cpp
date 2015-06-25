#include<iostream>
#include<tuple>
#include<fstream>
#include "Helper.hpp"
#include<map>
#include<algorithm>

using namespace std;

int main() {

	string nameIn, nameOut;
	cin >> nameIn;

	ifstream in;
	//ofstream out;
	in.open(nameIn);
	//out.open(nameOut);
	
	Helper helper(in);
	helper.help();
	helper.print_co_o();

}
