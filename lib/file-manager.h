#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <utility>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include "union-automata.h"
using namespace std;

class FileManager{
private:
  string name;
  ofstream arquivo;
public:
  FileManager(string name);
  ~FileManager();
  void gerarArquivo(const UnionAutomata &automata);
};

#endif
