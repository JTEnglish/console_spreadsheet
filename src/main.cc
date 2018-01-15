/****************************************
* main.cc
*   source file for running the
*   spreadsheet application
****************************************/
#include <iostream>
#include <string>
#include "spreadsheet.h"

using namespace std;

int main() {
  Sheet s;
  s.read();
  s.print(); //print before evaluation
  cout << endl;
  s.evaluate();
  s.print(); //print result

  return 0;
}
