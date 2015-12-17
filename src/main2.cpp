#include "parser_main.hpp"
#include "fuzzyengine.hpp"
#include <unistd.h>



//#include <Matrix>



int main(){

std::cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "<<std::endl;
std::cout<<"Ce programme permettra de réaliser des opérations floues sur une base de faits et une base de règles à l'aide d'un fuzzifier"<<std::endl;
std::cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "<<std::endl;
std::cout<<"                                                                                                                            "<<std::endl;


char* filename;
//std::cout<<"Entrer le nom d'un fichier texte à analyser pour créer la base de faits"<<std::endl;
//std::cin>>filename;
//std::cout<<"Génération de la base de faits à base du fichier texte spécifié ... "<<std::endl;

//on parse les fichiers texte
std::vector<Fait> Faits = Parser_faits("faits.txt");

//on parse les regeles
std::vector<Rule> Rules = Parser_rules("rules.txt");

//update de la base de faits en prenant en compte la base de rules (MAJ de l'énoncé)

Faits = updateFaits(Faits, Rules);


//fonction MAJ1 de l'énoncé: créé la liste des métarègles et update les faits avec la
// std::vector<Rule> MetaRules = updateMeta(Faits, Rules);
// on verra plus tard pour les metaregles




//check à l'écran la base de faits

printFaits(Faits);
sleep(5);


printRules(Rules);
sleep(5);



//on créé notre matrice de transition entre les valeurs :
//     AB   B   TB
// AB  1    1   1
// B   0.7  1   1
// TB  0.3  0.8 1

std::vector<std::vector<double>> TransMatrix = {{1.,1.,1.},{0.7,1.,1.},{0.3,0.8,1.}};

// Créer la liste de conclusion à évaluer

std::vector<EvalConcl> EvalConcls = EvalFunction(Faits, Rules, TransMatrix);

std::cout << "Travail de fuzzification en cours ..." << std::endl;
sleep(5);

std::cout<< "Affiche des conclusions et de leur évaluations: "<<std::endl;
std::cout<< "************************************************" << std::endl;

//Affichage des conclusions évaluées
for(std::vector<EvalConcl>::iterator ite=EvalConcls.begin();ite!=EvalConcls.end();++ite){
	std::cout<<"Conclusion :"<<std::get<0>(ite->first)<<std::endl;
	std::cout<<"Et l'évaluation pour cette conclusion est : " << ite->second << std::endl;
	std::cout<< "                                      " << std::endl;


}




//on créé nos vecteurs de valeur de fait
double listB[] = {0.001,0.005,0.005,0.01,0.1,0.3,0.4,0.6,0.8,0.9,1.0};
std::vector<double> uB (11);
std::vector<double> uTB(11);

uB[0]=0.001;
uB[1]=0.005;
uB[2]=0.005;
uB[3]=0.01;
uB[4]=0.1;
uB[5]=0.3;
uB[6]=0.4;
uB[7]=0.6;
uB[8]=0.8;
uB[9]=0.9;
uB[10]=1.0;


//it=uTB.begin(;)
for( std::vector<double>::iterator it = uB.begin() ; it != uB.end(); ++it){
	double value = *it;
	uTB.push_back(value*value);
	//std::cout<<uTB.back()<<std::endl;
}

/*
std::tuple<std::string, std::string, double> line;
std::vector<std::tuple<std::string, std::string, double>> parsed_file;
 parsed_file.emplace_back("test","test",0);
std::cout<< std::get<0>(parsed_file[0]) << std::get<1>(parsed_file[0]) << std::get<2>(parsed_file[0]) << std::endl ;
*/


return 0;
}
