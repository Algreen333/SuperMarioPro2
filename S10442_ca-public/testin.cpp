#include <map>
#include <set>
#include <iostream>
#include "geometry.hh"

using namespace std;

int main() {
    map<int, set<int> *> potingue;

    set<int> test = {123,345};
    potingue[10] = &test;
    cout << potingue[10] << endl;
    potingue.erase(10);
    cout << potingue[10] << endl;
    cout << nullptr;
}