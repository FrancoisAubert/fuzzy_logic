#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using std::ifstream;
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 10;
const char* const DELIMITER = " ";


inline std::vector<const char*> Parser(std::string filename){

  std::ifstream fin;
	fin.open(filename);
	if (!fin.good()) 
	return 1; // exit if file not found
	if(!fin.eof()){
	  char* line;
	fin.getline(line, MAX_CHARS_PER_LINE);

    // parse the line into blank-delimited tokens


    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
    // parse the line
    token[0] = strtok(line, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
    	for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
    	{
        token[n] = strtok(0, DELIMITER); // subsequent tokens
        if (!token[n]) break; // no more tokens
    }

for (int i = 0; i < n; i++) // n = #of tokens
    	cout << "Token[" << i << "] = " << token[i] << endl;
    cout << endl;
	  
	  


} 

int main()
{
  Parser('faits.txt');   

} 
