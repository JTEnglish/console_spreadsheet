/********************
*
********************/
#include <iostream>
#include <string>
#include <vector>
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

}

/********************
*
********************/
void Sheet::print() {
  for (int i = 0; i < cells.size(); ++i) {
    for (int j = 0; j < cells[i].size(); ++j) {
      cout << cells[i][j] << "\t";
    }
    cout << endl;
  }
}
