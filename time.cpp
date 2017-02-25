/*************************************************************************
	> File Name: time.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 13 Feb 2017 11:55:17 AM UTC
 ************************************************************************/

#include<iostream>
#include <ctime>

using namespace std;

int main(){
	time_t now = time(0);
	cout << "line number " << __LINE__ << endl;
	char *dt = ctime(&now);
	cout << "file name " << __FILE__ << endl;
	cout << dt <<endl;

	return 0;
}
