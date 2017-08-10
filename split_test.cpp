#include <iostream>
#include "/usr/include/boost/algorithm/string.hpp"
#include "/usr/include/boost/algorithm/string/trim.hpp"
#include <regex>
#include <iterator>
#include <vector>
#include <string>


using namespace std;

int main(){
    string a = "a   12 ";
    string b = "b  c";

    vector<string> tokens;
    boost::algorithm::trim(a);
    boost::split(tokens, a, boost::is_any_of(" "));
    for(string s:tokens){
        cout << s << "\t";
    }
    cout << endl;

    vector<string> tokens_vec;
    boost::split(tokens_vec, b, boost::is_any_of(" "));
    for(string s:tokens_vec){
        cout << s << "\t";
    }
    cout << endl;

    cout << "retex_token_iterator usage" << endl;
    regex re("\\s+");
    regex_token_iterator<string::iterator> end;
    regex_token_iterator<string::iterator> begin(a.begin(), a.end(), re, -1);
    while(begin != end){
        cout <<"[" << *begin++ << "]" << '\t';
    }
    cout << endl;


    return 0;
}
