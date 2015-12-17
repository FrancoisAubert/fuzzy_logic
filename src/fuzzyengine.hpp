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

typedef std::pair<Concl, double> EvalConcl;


// MAJ d'une base de fait à partir d'une base de règle
std::vector<Fait> updateFaits(std::vector<Fait> faits, std::vector<Rule> rules){

  for(std::vector<Fait>::iterator it = faits.begin(); it!=faits.end(); ++it ){
    for(std::vector<Rule>::iterator itr = rules.begin();itr!=rules.end(); ++itr){
      //checker si le fait est dans les prémisse de cette règle

      //le vecteur des prémisse de la règle courante est:
      std::vector<Premisse> currentPremisses;
      currentPremisses = std::get<1>(*itr);

      //la conclusion de la règle courante est:
      Concl currentConcl = std::get<2>(*itr);

      //liste des règles ou le fait courant apparait dans la premisse
      std::vector<Rule> currentPremList = std::get<2>(*it);

      //liste des règles ou le fait courant apparait dans la conclusion
      std::vector <Rule> currentConclList = std::get<3>(*it);


      //boucle sur les prémisses de la règle courante
      for(std::vector<Premisse>::iterator itp = currentPremisses.begin();itp!=currentPremisses.end();++itp ){
        //si le nom du fait se trouve dans la liste de prémisses de la règle courante, alors on ajoute à currentPremList la règle courante
        if(std::get<0>(*it).compare(itp->first)==0){
          std::get<2>(*it).push_back(*itr);
        }
      }

      //si le nom du fait se trouve dans la conclusion de la règle courante, alors on ajoute à currentConclList la règle courante
      if(std::get<0>(*it).compare(currentConcl.first)==0){
        std::get<3>(*it).push_back(*itr);
      }

    }
  }
  return faits;
}




//fonction d'évaluation de nos conclusions prenant en argument la liste de conclustion à évaluer, le bulletin, les regles et une matrice de transition
std::vector<EvalConcl> EvalFunction(std::vector<Fait> faits, std::vector<Rule> rules, std::vector<std::vector<double>> transmatrix){
//on créé notre liste de conclusions évaluées;

  std::vector<EvalConcl> EvalConcls;

//on parcours la base de regles
  for(std::vector<Rule>::iterator itr=rules.begin(); itr!=rules.end();++itr){
    //le coeff vaut déjà la certitude de la regle
    double coeff = std::get<4>(*itr);
//liste de premisses de la regle courante
    std::vector<Premisse> currentPremList = std::get<1>(*itr);

//on parcours les premisses
    for(std::vector<Premisse>::iterator itp=currentPremList.begin();itp!=currentPremList.end();++itp){
        //on parcours les faits pour trouver les faits correspondant à la premisse courante
        for(std::vector<Fait>::iterator itf=faits.begin();itf!=faits.end();++itf){
          if(itp->first.compare(std::get<0>(*itf))==0){
            //on multiplie le coeff par le coeff du fait
              coeff *= std::get<7>(*itf);

                //on multiplie le coeff par la valeur de la matrice de transition si besoin est
              if((std::get<6>(*itf).compare("AB"))&&(itp->second.compare("B"))){
                coeff *= transmatrix[1][0];
              }
              if((std::get<6>(*itf).compare("AB"))&&(itp->second.compare("TB"))){
                coeff *= transmatrix[2][0];
              }
              if((std::get<6>(*itf).compare("B"))&&(itp->second.compare("TB"))){
                coeff *= transmatrix[2][1];
              }
          }
          //les autres cas le ceoff est multipilé par 1 d'après la matrice donc inutile de les faire
        }


    }

    //ici le coeff est bon pour cette règle
EvalConcls.emplace_back(std::get<2>(*itr),coeff);


  }
return EvalConcls;
}
