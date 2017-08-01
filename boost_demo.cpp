/*************************************************************************
	> File Name: test.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Tue 01 Aug 2017 06:45:16 PM DST
 ************************************************************************/

#include<iostream>
#include <vector>

#include "/usr/include/boost/algorithm/string.hpp"

using namespace std;

int main(){
	string str = "ab	12	35	";
	vector<string> vecs;
	boost::split(vecs, str, boost::is_any_of("\t"));
	int idx = 0;
	/*
	for(vector<string>::iterator iter = vecs.begin(); iter != vecs.end(); iter++){
		idx ++;
		cout << idx << " : " << *iter << endl;
	}
	*/

	for(string ele: vecs){
		idx ++;
		cout << idx << " : " << ele << endl;
	}

}

