#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getSpec(string& storage, ifstream& fin) {
  char cursor;
  fin >> cursor;
  while (true) {
    if (cursor != ' ' && cursor != '\r' && cursor != '\n') {
      storage.push_back(cursor);
      cursor = fin.get();
    } else {
      break;
    }
  }
}

void readTouchLine(ifstream& fin, vector<double>& GHZ, vector<double>& S11,
                   vector<double>& S21, vector<double>& S12,
                   vector<double>& S22) {
  string cursor;
  fin >> cursor;
  while (cursor.at(0) != '!') {
    GHZ.push_back(stod(cursor));
  }
}

int main() {
  ifstream fin;
  fin.open("../data/example.S2P");

  if (fin.fail()) {
    return -1;
  }

  char cursor;
  string freqUnits;
  string type;
  string format;
  string r;
  string n;

  while (fin >> cursor) {
    if (cursor != '#') {
      continue;
    } else {
      break;
    }
  }

  getSpec(freqUnits, fin);
  getSpec(type, fin);
  getSpec(format, fin);
  getSpec(r, fin);
  getSpec(n, fin);

  return 0;
}