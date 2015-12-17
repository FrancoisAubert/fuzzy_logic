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










std::vector<Rule> Parser_rules(const char* filename)
{
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
  //std::cout<<"la 1ere valeure de la regle est "<< std::get<0>(current_rule)<<std::endl;
  //std::cout<<"la 2eme valeure de la regle est "<<std::endl;

  //std::cout<<std::get<1>(current_rule)[0].first<<std::endl;
  //std::cout<<std::get<1>(current_rule)[0].second<<std::endl;
  // std::cout<<std::get<1>(current_rule)[2].first<<std::endl;
  // std::cout<<std::get<1>(current_rule)[2].second<<std::endl;


  //std::cout<<"la 3eme valeure de la regle est "<<std::endl;

  //std::cout<<std::get<2>(current_rule).first<<std::endl;
  //  std::cout<<std::get<2>(current_rule).second<<std::endl;
  /*std::cout<<"la 4eme valeure de la regle est "<< std::get<3>(current_rule)<<std::endl;
  std::cout<<"la 5eme valeure de la regle est "<< std::get<4>(current_rule)<<std::endl;
  std::cout<<"*************************** "<< std::get<4>(current_rule)<<std::endl;
  std::cout<<"*************************** "<< std::get<4>(current_rule)<<std::endl;*/
}

num_ligne++;
}
return rules;

}






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

        Fait fait = std::make_tuple(name, type, premlist, concllist, metapremlist, eval, val, certitude, texte);
        //std::cout<< std::get<0>(fait) << " "<< std::get<1>(fait) << " "<< std::get<2>(fait) << " "<< std::get<3>(fait) <<" "/*<< std::get<4>(it)[0] <<" "<< */std::get<7>(fait) <<" "<< std::get<8>(fait) << std::endl ;

        parsed_file.push_back(fait);

      }
    }

  }

  //for(auto it:parsed_file)
  //std::cout<< std::get<0>(it) << " "<< std::get<1>(it) << " "<< std::get<2>(it) << " "<< std::get<3>(it) <<" "/*<< std::get<4>(it)[0] <<" "<< */std::get<7>(it) <<" "<< std::get<8>(it) << std::endl ;

  return parsed_file;

}


void printFaits(std::vector<Fait> faits){
  int i = 0;
  for(std::vector<Fait>::iterator it = faits.begin(); it!=faits.end(); ++it ){

    //la liste des règles dans lequel le fait courant apparait dans les prémisses:
    std::vector<Rule> currentPremList = std::get<2>(*it);

    //la liste des règles dans lequel le fait courant apparait dans les conclusions:
    std::vector<Rule> currentConclList = std::get<3>(*it);

    //la liste des metarègles dans lequel le fait courant apparait dans les premisses:
    std::vector<Rule> currentMetaPremList = std::get<4>(*it);


    std::cout<<"Regardons ensemble le fait numéro " << i << std::endl;
    std::cout<<"***********************************" << std::endl;

    std::cout<<"Le nom du fait est: " <<std::get<0>(*it)<<std::endl;
    if(std::get<1>(*it)){std::cout<<"Ce fait est flou " << std::endl;}else{std::cout<<"Ce fait est non flou " << std::endl;}

    std::cout<<"la liste des règles dans lequel ce fait apparait en prémisse a une taille de : "<<currentPremList.size()<< " et contient: "<<std::endl;

    for(std::vector<Rule>::iterator itp = currentPremList.begin();itp!=currentPremList.end();++itp ){
      std::cout <<"("<< std::get<0>(*itp) <<")"<<std::endl;
}

std::cout<<"la liste des règles dans lequel ce fait apparait en conclusion a une taille de : "<<currentConclList.size()<< " et contient: "<<std::endl;

for(std::vector<Rule>::iterator itc = currentConclList.begin();itc!=currentConclList.end();++itc ){
  std::cout <<"("<< std::get<0>(*itc) <<")"<<std::endl;
}

std::cout<<"la liste des metarègles dans lequel ce fait apparait en prémisses a une taille de : "<<currentMetaPremList.size()<< " et contient: "<<std::endl;

for(std::vector<Rule>::iterator itm = currentMetaPremList.begin();itm!=currentMetaPremList.end();++itm ){
  std::cout <<"("<< std::get<0>(*itm) <<")"<<std::endl;
}


if(std::get<5>(*it)){std::cout<<"Ce fait a déjà été évalué"<<std::endl;}else{std::cout<<"Ce fait n'a pas encore été évalué"<<std::endl;}

std::cout<<"La valeur de ce fait est "<<std::get<6>(*it)<<std::endl;

std::cout<<"Le coeff de certitude de ce fait est "<<std::get<7>(*it)<<std::endl;

std::cout<<"Le texte associé de ce fait est "<<std::get<8>(*it)<<std::endl;



    std::cout<<"                                    " << std::endl;
    i++;
  }

}





void printRules(std::vector<Rule> rules){
  int i = 0;

  for(std::vector<Rule>::iterator itr=rules.begin();itr!=rules.end();++itr){
//liste des prémisses de la règle courante:
std::vector<Premisse> currentPremisses = std::get<1>(*itr);

    std::cout<<"Regardons ensemble la règle numéro :" << i <<std::endl;
    std::cout<<"***********************************" << std::endl;

//on regarde le nom
    std::cout<<"Cette règle est la règle: " << std::get<0>(*itr)<<std::endl;

//on regarde les prémisses
    std::cout<<"Cette règle contient " <<std::get<1>(*itr).size() << " prémisses qui sont: " <<std::endl;
    for(std::vector<Premisse>::iterator itp = currentPremisses.begin();itp!=currentPremisses.end();++itp ){
     std::cout<< itp->first<< "avec un coeff de "<< itp->second<<std::endl;
    }

//on regarde la conclusion
    std::cout<<"Cette règle contient la conclusion suivante: "<<std::get<2>(*itr).first <<" avec un coeff de " <<std::get<2>(*itr).second<<std::endl;

//on regarde le type de la règle
    if(std::get<3>(*itr)){std::cout<<"Cette règle est de type flou"<<std::endl;}else{std::cout<<"Cette règle n'est pas de type flou"<<std::endl;}

//on regarde la certitude de la règle
    std::cout<<"Cette règle a une certitude de " << std::get<4>(*itr)<<std::endl;

    std::cout<<"                                    " << std::endl;
    i++;
  }


}
