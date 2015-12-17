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

// MAJ d'une base de fait à partir d'une base de règle
void updateFaits(std::vector<Fait> faits, std::vector<Rule> rules){

  for(std::vector<Fait>::iterator it = faits.begin(); it!=faits.end(); ++it ){
    for(std::vector<Rule>::iterator itr = rules.begin();itr!=rules.end();itr++){
      //checker si le fait est dans les prémisse de cette règle

      //le vecteur des prémisse de la règle courante est:
      std::vector<Premisse> currentPremisses;
      currentPremisses = std::get<1>(itr*);

      //la conclusion de la règle courante est:
      Concl currentConcl = std::get<2>(itr*);

      //liste des règles ou le fait courant apparait dans la premisse
      std::vector<Rule> currentPremList = std::get<2>(it*);

      //liste des règles ou le fait courant apparait dans la conclusion
      std::vector <Rule> currentConclList = std::get<3>(it*);

      //boucle sur les prémisses de la règle courante
      for(std::vector<Premisse>::iterator itp = currentPremisses.begin();itp!=currentPremisses.end();++itp ){

        //si le nom du fait se trouve dans la liste de prémisses de la règle courante, alors on ajoute à currentPremList la règle courante
        if(std::get<0>(it*).compare(itp->first)){
          currentPremList.push_back(itr*);
        }
      }

      //si le nom du fait se trouve dans la conclusion de la règle courante, alors on ajoute à currentConclList la règle courante
      if(std::get<0>(it*).compare(currentConcl.first)){
        currentConclList.pushback(itr*);
      }

    }
  }
}

}

}

}
