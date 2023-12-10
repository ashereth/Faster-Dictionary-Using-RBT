/***
* Makes use of Dictionary ADT to quickly store and access key/value pairs
***/
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include"Dictionary.h"

using namespace std;

#define MAX_LEN 300

// Function to convert a string to lowercase
std::string toLowercase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main(int argc, char * argv[]){

   int line_count;
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

    Dictionary myDict;

   // read each line of input file, then count and print tokens 
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      len = line.length();
      
      // get tokens in this line

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token    
        token = toLowercase(token);     
        if(myDict.contains(token)){
            myDict.getValue(token)+=1;
        }else{
            myDict.setValue(token, 1);
        }

         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }
   }

    out << myDict << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
