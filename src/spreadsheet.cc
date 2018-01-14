/********************
*
********************/
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>
#include <algorithm>
#include "spreadsheet.h"

using namespace std;

/********************
*
********************/
Sheet::~Sheet() {
  cells.clear();
}

/********************
*
********************/
void Sheet::read() {
  cout << "READ" << endl;
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

/********************
*
********************/
void Sheet::evaluate() {
  cout << "EVALUATE" << endl;
  for (int i = 0; i < cells.size(); ++i) {
    for (int j = 0; j < cells[i].size(); ++j) {
      //check if expression is found
      if (cells[i][j][0] == '=') {
        vector<string> ref;
        bool err = false;

        string expr = make_vals_exp(cells[i][j], ref, err);

        if (err) {
          cells[i][j] = "#ERROR";
        }
        else {
          //evaluate string value expression
          cells[i][j] = expr;
        }
      }
    }
  }
}

/********************
*
********************/
string Sheet::make_vals_exp(string str, vector<string> &ref, bool &err) {
  cout << "MAKE_VALS_EXP" << endl;
  string expr = "";

  if (!err) {
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
        expr += get_val(var, ref, err);

        i = var_end;
      }
      else {
        expr += str[i];
      }
    }
  }
  return expr;
}

/********************
*
********************/
string Sheet::get_val(string pos, vector<string> &ref, bool &err) {
  cout << "GET_VAL" << endl;
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

  cout << pos << " : " << data << endl;

  //if expression, call vals expression function again
  if (data[0] == '=') {
    val = make_vals_exp(data, ref, err);
  }
  else {
    val = data;
  }

  return val;
}

/********************
*
********************/
void Sheet::print() {
  cout << "PRINT" << endl;
  for (int i = 0; i < cells.size(); ++i) {
    for (int j = 0; j < cells[i].size(); ++j) {
      cout << cells[i][j] << "\t";
    }
    cout << endl;
  }
}
