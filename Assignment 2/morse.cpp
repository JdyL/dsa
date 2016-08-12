#include <iostream>
#include <fstream>
#include "morseconverter.h"

#define MORSECODE_FILE  "morsecodes.txt" 

int main (int argc, char* argv[]) 
{
   // Input handling
   if (argc == 4)
   {
         morseconverter Convert;
         if ('e' == argv[1][0])
         {
            Convert.Encode(argv[2], argv[3]); 
         }
         else if ('d' == argv[1][0]) 
         {
            Convert.Decode(argv[2], argv[3]); 
         }
         else 
         {
            cout << "Syntax: program e|d filein fileout" << endl;
            cout << "e for encoding english to morse, filein to fileout" << endl;
            cout << "d for decoding morse to english, filein to fileout" << endl;
            cout << "filein and fileout must be different files" << endl;
            return -1;
         }
      }
   
   else 
   {
      cout << "Syntax: program e|d filein fileout" << endl;
      cout << "e for encoding english to morse, filein to fileout" << endl;
      cout << "d for decoding morse to english, filein to fileout" << endl;
      cout << "filein and fileout must be different files" << endl;
      return -1;
   }

   // Read morsecode file
   ifstream morsecode(MORSECODE_FILE);

   // Unable to load/find morsecodes.txt
   if(morsecode.fail())
   {
      cout << "Program failed with the following error" << endl;
      cout << "Unable to open file " << MORSECODE_FILE << endl;
      return -1;
   }
   return 0;
}