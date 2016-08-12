#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "bintree.h"

#define MORSECODE_FILE  "morsecodes.txt" 

using namespace std;
using namespace treespc;

struct Converter 
   {
      string letter;
      string data; 
      
      // Overload relational operator
      bool operator == (const Converter &other) const 
      { 
         return (this->letter == other.letter); 
      }
      
      bool operator != (const Converter &other) const 
      { 
         return (this->letter != other.letter); 
      } 

      bool operator < (const Converter &other) const 
      { 
         return (this->letter < other.letter); 
      } 

      bool operator > (const Converter &other) const 
      { 
         return (this->letter > other.letter); 
      } 
      
      bool operator <= (const Converter &other) const 
      { 
         return (this->letter <= other.letter); 
      } 

      bool operator >= (const Converter &other) const 
      { 
         return (this->letter >= other.letter); 
      }
   };

bool Encode(const char* in_file, const char* out_file); 
bool Decode(const char* in_file, const char* out_file); 

class morseconverter 
{
   public:
   bool Encode(const char* in_file, const char* out_file) 
   { 
      Converter code;
      vector<Converter> vectorCode; 
      vector<Converter>::iterator finder; 
      ifstream morseFile(MORSECODE_FILE);
      if( morseFile.fail() ) return false; 

      // Store morse code file data into vector
      while(!morseFile.eof()) 
      { 
         morseFile >> code.letter >> code.data; 
         vectorCode.push_back(code);  
      } 
      morseFile.close();
      ifstream inFile(in_file); 
      ofstream outFile(out_file);
      if(inFile.fail() || outFile.fail()) 
      {
         cout << "Program failed with the following error" << endl;
         cout << "Unable to open file " << in_file << endl;
         return false; 
      }
   // Convert text to morse
      while( !inFile.eof() ) 
      { 
         code.letter = inFile.get();
         if (inFile.fail())
         break;
         if (code.letter == "\r" ) continue; 
         finder = find(vectorCode.begin(), vectorCode.end(), code); 
         if(finder != vectorCode.end()) 
         outFile << (*finder).data << " ";	  
         else 
         outFile << code.letter; 
      } 
      inFile.close();
      outFile.close(); 
      morseFile.close();
      return true; 
   }

   bool Decode(const char* in_file, const char* out_file) 
   {
      Converter code;
      bintree<Converter> binTree;
      const_iterator<Converter> itr;
      ifstream codeFile(MORSECODE_FILE);
      for (int i = 0; i < 26; i++)
      {
         codeFile >> code.data >> code.letter;
         binTree.insert(code);
      }
      ifstream inFile(in_file);
      ofstream outFile(out_file);
      if (inFile.fail() || outFile.fail()) 
      {
         cout << "Program failed with the following error" << endl;
         cout << "Unable to open file " << in_file << endl;
         return false; 
      }
      // Convert morse to text
      char ch; 
      code.letter = "";
      while(inFile.good()) 
      { 
         ch = inFile.get();
         if ( inFile.fail() )
         break;
         if (code.letter == "\r" ) continue;
         if(ch == '*' || ch == '-') 
         { 
            code.letter += ch;
            
         }
         else 
         {
            itr = binTree.find(code);
            if(itr != binTree.end()) 
            {
               outFile << itr->data;
            }
            else
            {
               outFile << ch;
            }
            code.letter = ""; 
         }
         }
      
      inFile.close(); 
      outFile.close(); 
      codeFile.close();
      return true; 
   }
};