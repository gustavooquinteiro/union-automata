#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include "union-automata.h"
using namespace std;

class FileManager{
private:
  string name;
  FILE * arquivo;
public:
  FileManager(char* name, char* mode);
  ~FileManager();
  void gerarArquivo(const UnionAutomata &automata);
};

#endif
