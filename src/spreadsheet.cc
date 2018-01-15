/****************************************
* spreadsheet.cc
*   source file for spreadsheet class
****************************************/
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>
#include <algorithm>
#include "spreadsheet.h"

using namespace std;

/****************************************
* ~Sheet
*   deconstructor
****************************************/
Sheet::~Sheet() {
  cells.clear();
}

/****************************************
* read
*   reads in cells to vector
****************************************/
void Sheet::read() {
  string line = "";

  while (getline(cin, line)) { //read each line
    vector<string> tmp; //string vector to hold tokens
    size_t pos = 0;
    string token;
    string delimiter = "\t";

    while ((pos = line.find(delimiter)) != string::npos) { //split on tabs
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        tmp.push_back(token);
    }
    if (line != "") { //get last one
      tmp.push_back(line);
    }

    cells.push_back(tmp); //add row to cell matrix
  }
}

/****************************************
* evaluate
*   iterates over each cell,
*   changes value to expression result
*   if present
****************************************/
void Sheet::evaluate() {
  for (int i = 0; i < cells.size(); ++i) {
    for (int j = 0; j < cells[i].size(); ++j) {
      //check if expression is found
      if (cells[i][j][0] == '=') {
        vector<string> ref;
        bool err = false;
        bool not_num = false;

        string expr = make_vals_exp(cells[i][j], ref, err, not_num);

        if (err) {
          cells[i][j] = "#ERROR";
        }
        else if (not_num) {
          cells[i][j] = "#NAN";
        }
        else {
          //evaluate string value expression using tinyexpr
          cells[i][j] = evaluate_str_exp(expr);
        }
      }
    }
  }
}

/****************************************
* make_vals_exp
*   changes expression variables to
*   literal value and returns the string
****************************************/
string Sheet::make_vals_exp(string str, vector<string> &ref, bool &err, bool &not_num) {
  string expr = "";

  if (!err && !not_num) {
    //find vars and build value expression string
    for (int i = 1; i < str.length(); ++i) {
      if (isalpha(str[i])) { //var was found
        int var_start = i;
        int var_end;

        //find end of var
        for (var_end = i; isdigit(str[var_end + 1]) && var_end < str.length(); ++var_end);
        string var = str.substr(var_start, var_end - var_start + 1);

        //if var is in ref vector -> error
        if(find(ref.begin(), ref.end(), var) != ref.end()) {
          err = true;
          return "";
        }

        ref.push_back(var);
        expr += get_val(var, ref, err, not_num);

        i = var_end;
      }
      else {
        expr += str[i];
      }
    }
  }
  return expr;
}

/****************************************
* get_val
*   gets the value for a referenced cell
****************************************/
string Sheet::get_val(string pos, vector<string> &ref, bool &err, bool &not_num) {
  string val = "";
  string row_pos = pos.substr(1, pos.length() - 1); //get row int

  //convert mapping
  int alpha_col = toupper(pos[0]) - 65; //get char and 0 index for ascii
  int num_row = stoi(row_pos) - 1; //adjust for 0 indexing

  //check bounds for vectors
  if ((alpha_col > cells.size()) || (num_row > cells[alpha_col].size()) || (alpha_col < 0) || (num_row < 0)) {
    err = true;
    return "";
  }

  //get data
  string data = cells[num_row][alpha_col];

  if (data == "") {
    not_num = true;
    return "";
  }
  else if (data[0] == '=') { //if expression, call vals expression function again
    val = make_vals_exp(data, ref, err, not_num);
  }
  else {
    val = data;
  }

  return val;
}

/****************************************
* evaluate_str_exp
*   takes a string expression with
*   literal values and returns the result
*   of the math done
****************************************/
string Sheet::evaluate_str_exp(string expr) {
  vector<int> params;
  vector<char> operators;

  //remove spaces
  string tmp = "";
  for (int i = 0; i < expr.length(); ++i) {
    if (expr[i] != ' ') {
      tmp += expr[i];
    }
  }
  expr = tmp;

  //populate param and operator vectors
  for (int i = 0; i < expr.length(); ++i) {
    string tmp_num = "";
    for (int j = i; isdigit(expr[j]); ++j) {
      tmp_num += expr[j];
      ++i;
    }
    params.push_back(atoi(tmp_num.c_str()));
    operators.push_back(expr[i]);
  }

  //do mult. and div. first
  for (int i = 0; i < operators.size(); ++i) {
    if ((operators[i] == '*') || (operators[i] == '/')) {
      for (int j = 0; j < params.size(); ++j) { //copy into resized vector
        if (j == i) { //do operation
          if (operators[i] == '*') {
            params[j] = params[j] * params[j + 1];
          }
          else { //operator == '/'
            params[j] = params[j] / params[j + 1];
          }
          params.erase(params.begin() + j + 1); //erase params[j + 1]
          ++j;
        }
      }
    }
  }

  //do ad. and sub.
  for (int i = 0; i < operators.size(); ++i) {
    if ((operators[i] == '+') || (operators[i] == '-')) {
      for (int j = 0; j < params.size(); ++j) { //copy into resized vector
        if (j == i) { //do operation
          if (operators[i] == '+') {
            params[j] = params[j] + params[j + 1];
          }
          else { //operator == '-'
            params[j] = params[j] - params[j + 1];
          }
          params.erase(params.begin() + j + 1); //erase params[j + 1]
          ++j;
        }
      }
    }
  }

  return to_string(params[0]);
}


/****************************************
* print
*   prints the values in the cells
****************************************/
void Sheet::print() {
  for (int i = 0; i < cells.size(); ++i) {
    for (int j = 0; j < cells[i].size(); ++j) {
      cout << cells[i][j] << "\t";
    }
    cout << endl;
  }
}
