#include <iostream>
#include <fstream>
#include "euro.h"

using namespace std;

int main(int argc, char*argv[]) {
   if (argc == 2) 
   {
      try
      {
         euro myEuro;
         myEuro.loadFile(argv[1]);
         myEuro.printList();
         myEuro.changeCase();
         myEuro.printList();
      }
      catch (exception &ex)
      {
         cout << "ERROR unable to read " << argv[1] << "\n";
      }
   }
   else
   {
      cout << "ERROR Syntax: " << argv[0] << ": file\n";
   }
   return 0;
}