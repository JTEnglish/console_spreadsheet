/********************
*
********************/
#ifndef SHEET
#define SHEET

#include <string>
#include <vector>

using namespace std;

class Sheet {
public:
  Sheet() {}
  ~Sheet();

  void read();
  void evaluate();
  void print();

private:
  vector<vector <string>> cells;
};

#endif
