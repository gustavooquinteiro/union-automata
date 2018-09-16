#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <time.h>
#include <fstream>
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
  void logger(exception& error);
};

#endif
