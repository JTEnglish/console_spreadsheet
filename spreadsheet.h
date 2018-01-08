/********************
*
********************/
#ifndef SHEET
#define SHEET

#include <string>
#include <vector>

class Sheet {
public:
  Sheet();
  ~Sheet();

  bool read();
  void evaluate();
  void print();

private:
  vector<vector <string>> cells;
};

#endif
