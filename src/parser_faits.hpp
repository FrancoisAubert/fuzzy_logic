#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>
#include <utility>
#include <vector>
#include <tuple>
//déja définie dans parser rules
//const int MAX_CHARS_PER_LINE = 512;
//const int MAX_TOKENS_PER_LINE = 20;
//const char* const DELIMITER = " ";

// typedef std::string Name;
// typedef bool TypeFlou;
typedef std::vector<Rule> PremList; //liste de toutes les regles ou le fait apparait en premisse
typedef std::vector<Rule> ConclList;//liste de toutes les regles ou le fait apparait en conclusion
typedef std::vector<Rule> MetaPremList; //liste de toutes les meta regles ou le fait apparait en premisse
typedef bool Eval; //est ce que le fait a déjà été évalué ou pas
// typedef std::string Val;
//typedef double Certitude;
typedef std::string Texte;

typedef std::tuple<Name, TypeFlou, PremList, ConclList, MetaPremList, Eval, Val, Certitude,Texte> Fait;



std::vector<Fait> Parser_faits(const char* filename)
{
  // create a file-reading object
  ifstream fin;
  fin.open(filename); // open a file
  
  
  // read each line of the file


std::vector<Fait> parsed_file; 


  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
    
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    
    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
    // parse the line
    token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
        if (!token[n]) break; // no more tokens
      }
    }

 // process (print) the tokens
    for (int i = 0; i < n; i++){ // n = #of tokens
      /*cout << "Token[" << i << "] = " << token[i] << endl;
    	cout << endl;
*/
	if (i%3==0){	
    Name name = token[i];
    Val val = token [i+1];
    Certitude certitude = std::stod (token [i+2]);
    TypeFlou type = true;
    PremList premlist;
    ConclList concllist;
    MetaPremList metapremlist;
    Eval eval = false;
    Texte texte = "résultat du bulletin";
		parsed_file.emplace_back(name, val, certitude, type, premlist, concllist, metapremlist, eval, texte);
		   }	
	}

  }

for(auto it:parsed_file)
//std::cout<< std::get<0>(it) << " "<< std::get<1>(it) << " "<< std::get<2>(it) << " "<< std::get<3>(it) <<" "<< std::get<4>(it)[0] <<" "<< std::get<7>(it) <<" "<< std::get<8>(it) << std::endl ;

return parsed_file;

}
