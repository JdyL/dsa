#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

class euro {
   public:
      list<char> myList;
      string item;

   void loadFile(const char* filename)
   {
      ifstream textfile;
      textfile.open(filename);
      if (!textfile)
      {
         throw runtime_error("Unable to open and load file");
      }

      // Read through a file until it reaches the end 
      if (textfile)
      {
         while (getline(textfile, item)) 
         {
            fillList(myList,item); // Load char into list
            myList.push_back('\n');
         }
         textfile.close();
      }
   }

   unsigned short getHash(const list<char> &charList)
   {
      unsigned short shift, hash = 0;
      list<char>::const_iterator itr;

      for (itr = charList.begin(); itr != charList.end(); itr++)
      {
         hash ^= *itr;
         shift = (hash & 15);
         hash = (hash << shift) | (hash >> (16 - shift));
      }
      return hash; 
   }

   void changeCase()
   {
      list<char>::iterator itr;
      list<char>::iterator itrNext;
      list<char>::iterator itrPrev;
      int counter;
      
      itrNext = myList.begin();
      itrPrev = myList.begin();
      counter = 0;

      for (itr = myList.begin(); itr != myList.end(); itr++ ) 
      {
         itrPrev = itr;
         --itrPrev;
         ++itrNext;
         
         // 2 w -> v
         if (*itr == 'w' || *itr == 'W')
         {
            if (*itr == 'w')
            {
               *itr = 'v';
            }
            else 
            {
               *itr = 'V';
            }
         }

         // 4 Erase doubles 
         if ((*itr == *itrPrev || *itr == toupper(*itrPrev) 
            || toupper(*itr) == *itrPrev) && *itr != ' ' && *itr != '\n' && isalpha(*itr))
         {
            if (*itrPrev == toupper(*itr)) 
            {
               *itr = toupper(*itr);
            }
            else {
               *itr = tolower(*itr);
            }
               itrPrev = myList.erase(itrPrev);
               --counter;
         }
         
         if (*itr == *itrNext && *itr != ' ' && *itr != '\n' && isalpha(*itr))
         {
            itrNext = myList.erase(itrNext);
         }
         
         // 3 ph > f
         else if ((*itr == 'p' || *itr == 'P') && (*itrNext == 'h' || *itrNext == 'H'))
         {
            if (*itr == toupper(*itr))
            {
               *itr = 'F';
            }
            else 
            {
               *itr = 'f';
            }
         itrNext = myList.erase(itrNext);
         --counter;
         }
         
         // 6 th > z
         else if ((*itr == 't' || *itr == 'T') && (*itrNext == 'h' || *itrNext == 'H'))
         {
            if (*itr == toupper(*itr)) 
            {
               *itr = 'Z';
            }
            else 
            {
               *itr = 'z';
            }
            itrNext = myList.erase(itrNext);
         }
         
      // 7 ou > u
         else if ((*itr == 'o' || *itr == 'O') && (*itrNext == 'u' || *itrNext == 'U'))
         {
            if (*itr == toupper(*itr))
            {
               *itr = 'U';
            }
            else 
            {
               *itr = 'u';
            }
            itrNext = myList.erase(itrNext);
         }
         
      // 8 ea > e
         else if ((*itr == 'e' || *itr == 'E') && (*itrNext == 'a' || *itrNext == 'A'))
         {
            itrNext = myList.erase(itrNext);
         }
         
         
      // 1 c+(e|i|y) > s else c > k
         else if ((*itr == 'c' || *itr == 'C' ) && ((*itrNext == 'e' 
                  || *itrNext == 'E' || *itrNext == 'i' || *itrNext == 'I'
                  || *itrNext == 'y' || *itrNext == 'Y')))
         {
            if (*itr == toupper(*itr))
            {
               *itr = 'S'; 
            }
            else {
               *itr = 's';
            }
         }
         
         else if (*itr == 'c' || *itr == 'C') 
         {
            if (*itr == toupper(*itr))
            {
               *itr = 'K'; 
            }
            else 
            {
               *itr = 'k';
            }
         }
         
         //5 3+ character word end with 'e' > delete
         else if (counter > 3 && (*itr == ' ' || *itr == '\n' || !isalnum(*itr))) 
         {
            if (*itrPrev == 'e' || *itrPrev == 'E') 
            {
               itrPrev = myList.erase(itrPrev);
               
            }
         }
         
      //9 ed > d
         else if ((*itrPrev == 'e' || *itrPrev == 'E') && (*itr == 'd' 
                  || *itr == 'D') && (*itrNext == ' ' || *itrNext == '\n' || !isalnum(*itrNext)))
         {
            itrPrev = myList.erase(itrPrev);
         }
         
         counter++;
         
         // Resets character counter once it reaches the end of a word
         if (*itr == ' ' || *itr == '\n')
         { 
            counter = 0;
         }
      }
   }

   void fillList(list<char> &myList, const string &letters)
      {
      for (int i = 0; i<letters.length(); i++) 
         {
            myList.push_back(letters[i]);
         }
      }

   void printList()
   {
      list<char>::const_iterator itr;
      for (itr = myList.begin(); itr != myList.end(); itr++ ) 
      {
         cout << *itr;
      }
      cout << endl;
      cout << "Hash = " << getHash(myList) << endl;
   }
};