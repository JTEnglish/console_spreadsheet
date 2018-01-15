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

  string make_vals_exp(string str, vector<string> &ref, bool &err, bool &not_num);
  string get_val(string pos, vector<string> &ref, bool &err, bool &not_num);
  string evaluate_str_exp(string expr);

};

#endif
