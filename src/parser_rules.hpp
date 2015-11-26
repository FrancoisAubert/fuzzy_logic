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
#include <stdlib.h> 
//déja définie dans parser faits
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";


// définition des types pour définir une règle

typedef std::string Obj;
typedef std::string Val;
typedef std::string Name;
typedef std::pair<Obj,Val> Premisse;
typedef std::vector<Premisse> Premisses;
typedef std::pair<Obj, Val> Concl;
typedef bool TypeFlou;
typedef double Certitude;

typedef std::tuple<Name, Premisses, Concl, TypeFlou, Certitude> Rule;












std::vector<Rule> Parser_rules(const char* filename)
{
  std::cout<<"je suis entré dans le parser rules"<<std::endl;
  // create a file-reading object
  ifstream fin;
  fin.open(filename); // open a file
  
  
  // read each line of the file

  Obj obj;
  Val val;
  Name name2 = "init";
  Premisse premisse;
  Premisses premisses;
  Concl concl;
  TypeFlou typeflou;
  Certitude certitude;
  std::vector<Rule> rules;


  std::vector<char*> parsed_line; 

    int num_ligne =0;

  while (!fin.eof())
  {
    //std::cout<<"nouvelle ligne"<<std::endl;

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
        if(token[n])

        if (!token[n]) break; // no more tokens
      }
    }




 // process (print) the tokens
    //for (int i = 0; i < n; i++){ // n = #of tokens for this line
      /*cout << "Token[" << i << "] = " << token[i] << endl;
    	cout << endl;
*/if(token[0]){
      //std::cout<<"sur cette ligne le token 0 vaut "<<token[0]<<std::endl;
      
      if(strcmp(token[0],"Regle")==0){

        name2=token[1];

      }
      else if(strcmp(token[0],"Si")==0){

        premisses.emplace_back(token[1],token[2]);
        //std::cout<<"les tokens suivant un SI sont "<< token[1] << "et" << token[2]<<std::endl;
      }

      else if(strcmp(token[0],"et")==0){

        premisses.emplace_back(token[1],token[2]);
      }

      else if(strcmp(token[0],"Alors")==0){

        if(token[2]){concl = std::make_pair(token[1],token[2]);
          typeflou = true;
        }

        else {concl = std::make_pair(token[1],"null");
        typeflou = false;
      }

    }
    else if(strcmp(token[0],"Certitude")==0){


      certitude = atof(token[1]); 

    }
  }else{
    rules.emplace_back(name2,premisses,concl,typeflou,certitude);
    //std::cout<<"premisses avant d'êter stocké vaut"<<premisses[0].first<<" et "<<premisses[0].second<<std::endl;
    premisses.clear();

   // std::cout<<"j'ai bien construit la regle pour ce bloc"<<std::endl;

    Rule current_rule;
    current_rule=rules.back();
     std::cout<<"la 1ere valeure de la regle est "<< std::get<0>(current_rule)<<std::endl;
    std::cout<<"la 2eme valeure de la regle est "<<std::endl;

        std::cout<<std::get<1>(current_rule)[0].first<<std::endl;
        std::cout<<std::get<1>(current_rule)[0].second<<std::endl;
        // std::cout<<std::get<1>(current_rule)[2].first<<std::endl;
        // std::cout<<std::get<1>(current_rule)[2].second<<std::endl;


    std::cout<<"la 3eme valeure de la regle est "<<std::endl;

      std::cout<<std::get<2>(current_rule).first<<std::endl;
        std::cout<<std::get<2>(current_rule).second<<std::endl;
     std::cout<<"la 4eme valeure de la regle est "<< std::get<3>(current_rule)<<std::endl;
     std::cout<<"la 5eme valeure de la regle est "<< std::get<4>(current_rule)<<std::endl;
          std::cout<<"*************************** "<< std::get<4>(current_rule)<<std::endl;
          std::cout<<"*************************** "<< std::get<4>(current_rule)<<std::endl;


  }






num_ligne++;
}
return rules;

}
